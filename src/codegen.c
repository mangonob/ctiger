#include <assert.h>
#include <stdbool.h>
#include <stdarg.h>
#include "codegen.h"
#include "tiles.h"
#define L(...) mkTempList(__VA_ARGS__, NULL)

static AS_instrList iList = NULL;
static AS_instrList last = NULL;
static bool lastIsLabel = false;
static void emit(AS_instr i)
{
  lastIsLabel = (i->kind == I_LABEL);
  if (!last)
    last = iList = AS_InstrList(i, NULL);
  else
    last = last->tail = AS_InstrList(i, NULL);
}

bool tileExp(T_exp exp, T_exp match);
/** match statement tile */
bool tileStm(T_stm stm, T_stm match)
{
  if (match == NULL)
    return true;
  else if (match != NULL && stm == NULL)
    return false;
  // else match != NULL && stm != NULL

  if (stm->kind != match->kind)
    return false;

  switch (match->kind)
  {
  case T_LABEL:
    return true;
  case T_JUMP:
    return tileExp(stm->JUMP.exp, match->JUMP.exp);
  case T_CJUMP:
    return stm->CJUMP.op == match->CJUMP.op &&
           tileExp(stm->CJUMP.lhs, stm->CJUMP.lhs) &&
           tileExp(stm->CJUMP.rhs, stm->CJUMP.rhs);
  case T_MOVE:
    return tileExp(stm->MOVE.dst, match->MOVE.dst) &&
           tileExp(stm->MOVE.src, match->MOVE.src);
  case T_EXP:
    return tileExp(stm->EXP, match->EXP);
  default:
    assert(0);
  }
}

/** match expression tile */
bool tileExp(T_exp exp, T_exp match)
{
  if (match == NULL)
    return true;
  else if (match != NULL && exp == NULL)
    return false;
  // else match != NULL && stm != NULL

  if (exp->kind != match->kind)
    return false;

  switch (match->kind)
  {
  case T_BINOP:
    return match_enum(exp->BINOP.op, match->BINOP.op) &&
           tileExp(exp->BINOP.left, match->BINOP.left) &&
           tileExp(exp->BINOP.right, match->BINOP.right);
  case T_MEM:
    return tileExp(exp->MEM, match->MEM);
  case T_TEMP:
  case T_NAME:
  case T_CONST:
    return true;
  default:
    assert(0);
  }

  return false;
}

static Temp_temp munchExp(T_exp exp);
static Temp_temp munchCall(T_exp call, bool returned)
{
  assert(call->kind == T_CALL);
  assert(call->CALL.fun->kind == T_NAME);

  Temp_temp maybeReturn = NULL;
  Temp_tempList saved = NULL;
  Temp_tempList reversed = NULL;

  // 保存寄存器
  for (Temp_tempList callees = F_callersaves(); callees; callees = callees->tail)
  {
    Temp_temp r = callees->head;
    Temp_temp t = Temp_newtemp();
    saved = Temp_TempList(t, saved);
    reversed = Temp_TempList(callees->head, reversed);
    emit(AS_Move("mov `d0, `s0", L(t), L(r)));
  }

  int i = 0;
  for (T_expList params = call->CALL.args; params; params = params->tail)
  {
    T_exp param = params->head;
    Temp_temp exp = munchExp(param);

    if (i <= 7)
    {
      emit(AS_Move("mov `d0, `s0", L(F_XN(i)), L(exp)));
    }
    else
    {
      int offset = F_wordSize * (i - 8);

      if (offset == 0)
        emit(AS_Oper("str `s0, [`s1]", NULL, L(exp, F_SP(), NULL), NULL));
      else
        emit(AS_Oper(Format("str `s0, [`s1, #%d]", offset), NULL, L(exp, F_SP(), NULL), NULL));
    }

    ++i;
  }

  emit(AS_Oper(Format("bl %s", call->CALL.fun->NAME->name), NULL, NULL, NULL));
  if (returned)
  {
    maybeReturn = Temp_newtemp();
    emit(AS_Oper("mov `d0, `s0", L(maybeReturn), L(F_RV()), NULL));
  }

  // 恢复寄存器
  for (; reversed && saved; reversed = reversed->tail, saved = saved->tail)
  {
    Temp_temp r = reversed->head;
    Temp_temp t = saved->head;
    emit(AS_Move("mov `d0, `s0", L(r), L(t)));
  }

  return maybeReturn;
}

static void munchBinop(Temp_temp d, T_exp exp)
{
  assert(exp->kind == T_BINOP);

  Temp_tempList dl = L(d);

  if (tileExp(exp, binop_x_const()))
  {
    Temp_temp s = munchExp(exp->BINOP.left);
    Temp_tempList sl = L(s);
    int c = exp->BINOP.right->CONST;

    switch (exp->BINOP.op)
    {
    case T_plus:
      if (c < 1 << 12)
      {
        emit(AS_Oper(Format("add `d0, `s0, #%d", c), dl, sl, NULL));
      }
      else
      {
        Temp_temp t = Temp_newtemp();
        emit(AS_Move(Format("mov `d0 #%d", c), L(t), NULL));
        emit(AS_Oper("add `d0, `s0, `s1", dl, L(s, t), NULL));
      }
      break;
    case T_minus:
      if (c <= 1 << 12)
      {
        emit(AS_Oper(Format("subs `d0, `s0, #%d", c), dl, sl, NULL));
      }
      else
      {
        Temp_temp t = Temp_newtemp();
        emit(AS_Move(Format("mov `d0 #%d", c), L(t), NULL));
        emit(AS_Oper("subs `d0, `s0, `s1", dl, L(s, t), NULL));
      }
      break;
    case T_mul:
      emit(AS_Oper(Format("mul `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    case T_div:
      emit(AS_Oper(Format("sdiv `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    case T_and:
      emit(AS_Oper(Format("and `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    case T_or:
      emit(AS_Oper(Format("orr `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    case T_lshift:
      emit(AS_Oper(Format("lsl `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    case T_rshift:
      emit(AS_Oper(Format("lsr `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    case T_arshift:
      emit(AS_Oper(Format("asr `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    case T_xor:
      emit(AS_Oper(Format("eor `d0, `s0, #%d", c), dl, sl, NULL));
      break;
    }
  }
  else
  {
    Temp_temp l = munchExp(exp->BINOP.left);
    Temp_temp r = munchExp(exp->BINOP.right);
    Temp_tempList dl = L(d);
    Temp_tempList sl = L(l, r);

    switch (exp->BINOP.op)
    {
    case T_plus:
      emit(AS_Oper("add `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_minus:
      emit(AS_Oper("subs `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_mul:
      emit(AS_Oper("mul `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_div:
      emit(AS_Oper("sdiv `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_and:
      emit(AS_Oper("and `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_or:
      emit(AS_Oper("orr `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_lshift:
      emit(AS_Oper("lsl `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_rshift:
      emit(AS_Oper("lsr `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_arshift:
      emit(AS_Oper("asr `d0, `s0, `s1", dl, sl, NULL));
      break;
    case T_xor:
      emit(AS_Oper("eor `d0, `s0, `s1", dl, sl, NULL));
      break;
    }
  }
}

static Temp_temp munchExp(T_exp exp)
{
  if (exp->kind == T_CONST)
  {
    Temp_temp t = Temp_newtemp();
    emit(AS_Oper(Format("mov `d0, #%d", exp->CONST), L(t), NULL, NULL));
    return t;
  }
  else if (exp->kind == T_TEMP)
  {
    return exp->TEMP;
  }
  else if (exp->kind == T_CALL)
  {
    return munchCall(exp, true);
  }
  else if (exp->kind == T_BINOP)
  {
    Temp_temp t = Temp_newtemp();
    munchBinop(t, exp);
    return t;
  }
  else if (exp->kind == T_MEM)
  {
    // right value
    // todo: ldr rt, [base, offset]
    Temp_temp t = Temp_newtemp();
    Temp_temp addr = munchExp(exp->MEM);
    emit(AS_Oper("ldr `s0, [`s1]", NULL, L(t, addr), NULL));
    return t;
  }
  else
  {
    // TODO [temp]
    return Temp_newtemp();
  }
}

char *relop2cond(T_relOp op)
{
  switch (op)
  {
  case T_eq:
    return "eq";
  case T_ne:
    return "ne";
  case T_lt:
    return "lt";
  case T_gt:
    return "gt";
  case T_le:
    return "le";
  case T_ge:
    return "ge";
  case T_ult:
    return "lo";
  case T_ule:
    return "ls";
  case T_ugt:
    return "hi";
  case T_uge:
    return "hs";
  }
}

void saveMem(T_exp mem, Temp_temp t)
{
  if (tileExp(mem, binop_x_const()) && mem->BINOP.op == T_plus)
  {
    int offset = mem->BINOP.right->CONST;
    Temp_temp base = munchExp(mem->BINOP.left);

    if (offset > 0)
      emit(AS_Oper(Format("str `s0, [`s1, %d]", offset), NULL, L(t, base), NULL));
    else if (offset < 0)
      emit(AS_Oper(Format("str `s0, [`s1, %d]", offset), NULL, L(t, base), NULL));
    else
      emit(AS_Oper("str `s0, [`s1]", NULL, L(t, base), NULL));
  }
  else
  {
    Temp_temp d = munchExp(mem);
    emit(AS_Oper("str `s0, [`d0]", L(d), L(t), NULL));
  }
}

static void munchStm(T_stm stm)
{
  if (stm->kind == T_LABEL)
  {
    if (lastIsLabel)
      emit(AS_Oper("nop", NULL, NULL, NULL));
    emit(AS_Label(Format("%s:", Temp_labelstring(stm->LABEL)), stm->LABEL));
  }
  else if (tileStm(stm, jump_to_name()))
  {
    emit(AS_Oper("b `j0", NULL, NULL, AS_Targets(stm->JUMP.jumps)));
  }
  else if (stm->kind == T_JUMP)
  {
    Temp_temp t = munchExp(stm->JUMP.exp);
    emit(AS_Oper("br `s0", NULL, L(t), AS_Targets(stm->JUMP.jumps)));
  }
  else if (stm->kind == T_CJUMP)
  {
    Temp_temp l = munchExp(stm->CJUMP.lhs);
    Temp_temp r = munchExp(stm->CJUMP.rhs);
    emit(AS_Oper("cmp `s1, `s0", NULL, L(r, l), NULL));
    char *cond = relop2cond(stm->CJUMP.op);
    Temp_labelList tl = Temp_LabelList(stm->CJUMP.trueLabel, NULL);
    emit(AS_Oper(Format("b%s `j0", cond), NULL, NULL, AS_Targets(tl)));
  }
  else if (stm->kind == T_EXP)
  {
    munchExp(stm->EXP);
  }
  else if (tileStm(stm, move_from_binop_x_const()))
  {
    if (stm->MOVE.dst->kind == T_MEM)
    {
      Temp_temp t = Temp_newtemp();
      munchStm(T_Move(T_Temp(t), stm->MOVE.dst));
      saveMem(stm->MOVE.dst->MEM, t);
      return;
    }
    else if (stm->MOVE.dst->kind == T_TEMP)
    {
      munchBinop(stm->MOVE.dst->TEMP, stm->MOVE.src);
    }
    else
      assert(0 && "bad move dst");
  }
  else if (tileStm(stm, move_const_to_temp()))
  {
    Temp_temp t = stm->MOVE.dst->TEMP;
    int c = stm->MOVE.src->CONST;
    emit(AS_Move(Format("mov `d0, #%d", c), L(t), NULL));
  }
  else if (stm->kind == T_MOVE)
  {
    assert(stm->MOVE.dst->kind == T_TEMP || stm->MOVE.dst->kind == T_MEM);

    if (stm->MOVE.dst->kind == T_MEM)
    {
      Temp_temp t = Temp_newtemp();
      munchStm(T_Move(T_Temp(t), stm->MOVE.dst));
      saveMem(stm->MOVE.dst->MEM, t);
    }
    else
    {
      Temp_temp d = stm->MOVE.dst->TEMP;
      if (tileStm(stm, move_const_offset_mem_to_x()))
      {
        Temp_temp base = stm->MOVE.src->MEM->BINOP.left->TEMP;
        int offset = stm->MOVE.src->MEM->BINOP.right->CONST;

        if (offset > 0)
          emit(AS_Oper(Format("ldr `d0, [`s0, #%d]", offset), L(d), L(base), NULL));
        else if (offset < 0)
          emit(AS_Oper(Format("ldur `d0, [`s0, #%d]", offset), L(d), L(base), NULL));
        else
          emit(AS_Oper("ldr `d0, [`s0]", L(d), L(base), NULL));
      }
      else
      {
        Temp_temp s = munchExp(stm->MOVE.src);
        emit(AS_Move("mov `d0, `s0", L(d), L(s)));
      }
    }
  }
  else if (stm->kind == T_EXP)
  {
    T_exp exp = stm->EXP;
    if (exp->kind == T_CALL)
      munchCall(exp, false);
    else
      munchExp(exp);
  }
  else
  {
    emit(AS_Oper("<unknown>", NULL, NULL, NULL));
  }
}

AS_instrList F_codegen(F_frame f, T_stmList stmList)
{
  for (; stmList; stmList = stmList->tail)
    munchStm(stmList->head);

  if (last && last->head->kind == I_LABEL)
    emit(AS_Oper("nop", NULL, NULL, NULL));

  AS_instrList il = iList;
  iList = last = NULL;
  return il;
}
