#include <assert.h>
#include <stdbool.h>
#include "codegen.h"
#include "tiles.h"

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

Temp_tempList L(Temp_temp head, Temp_tempList tail)
{
  return Temp_TempList(head, tail);
}

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
    emit(AS_Move("mov `d0, `s0", L(t, NULL), L(r, NULL)));
  }

  // TODO parameters
  emit(AS_Oper(Format("bl %s", call->CALL.fun->NAME->name), NULL, NULL, NULL));
  if (returned)
  {
    maybeReturn = Temp_newtemp();
    emit(AS_Oper("mov `d0, `s0", L(maybeReturn, NULL), L(F_RV(), NULL), NULL));
  }

  // 恢复寄存器
  for (; reversed && saved; reversed = reversed->tail, saved = saved->tail)
  {
    Temp_temp r = reversed->head;
    Temp_temp t = saved->head;
    emit(AS_Move("mov `d0, `s0", L(r, NULL), L(t, NULL)));
  }

  return maybeReturn;
}

static Temp_temp munchExp(T_exp exp)
{
  if (exp->kind == T_CONST)
  {
    Temp_temp t = Temp_newtemp();
    emit(AS_Oper(Format("mov `d0, #%d", exp->CONST), L(t, NULL), NULL, NULL));
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
    emit(AS_Oper(Format("str `s0, [`d0 + %d]", offset), L(base, NULL), L(t, NULL), NULL));
  }
  else
  {
    Temp_temp d = munchExp(mem);
    emit(AS_Oper("str `s0, [`d0]", L(d, NULL), L(t, NULL), NULL));
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
    emit(AS_Oper("br `j0", NULL, NULL, AS_Targets(stm->JUMP.jumps)));
  }
  else if (stm->kind == T_JUMP)
  {
    Temp_temp t = munchExp(stm->JUMP.exp);
    emit(AS_Oper("br `s0", NULL, L(t, NULL), AS_Targets(stm->JUMP.jumps)));
  }
  else if (stm->kind == T_CJUMP)
  {
    Temp_temp l = munchExp(stm->CJUMP.lhs);
    Temp_temp r = munchExp(stm->CJUMP.rhs);
    emit(AS_Oper("cmp `s1, `s0", NULL, L(r, L(l, NULL)), NULL));
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

    T_binOp op = stm->MOVE.src->BINOP.op;
    Temp_temp d = stm->MOVE.dst->TEMP;
    Temp_temp s = munchExp(stm->MOVE.src->BINOP.left);
    int c = stm->MOVE.src->BINOP.right->CONST;

    switch (op)
    {
    case T_plus:
      if (c < 1 << 12)
      {
        emit(AS_Oper(Format("add `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      }
      else
      {
        Temp_temp t = Temp_newtemp();
        emit(AS_Move(Format("mov `d0 #%d", c), L(t, NULL), NULL));
        emit(AS_Oper("add `d0, `s0, `s1", L(d, NULL), L(s, L(t, NULL)), NULL));
      }
      break;
    case T_minus:
      if (c <= 1 << 12)
      {
        emit(AS_Oper(Format("subs `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      }
      else
      {
        Temp_temp t = Temp_newtemp();
        emit(AS_Move(Format("mov `d0 #%d", c), L(t, NULL), NULL));
        emit(AS_Oper("subs `d0, `s0, `s1", L(d, NULL), L(s, L(t, NULL)), NULL));
      }
      break;
    case T_mul:
      emit(AS_Oper(Format("mul `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    case T_div:
      emit(AS_Oper(Format("sdiv `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    case T_and:
      emit(AS_Oper(Format("and `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    case T_or:
      emit(AS_Oper(Format("orr `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    case T_lshift:
      emit(AS_Oper(Format("lsl `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    case T_rshift:
      emit(AS_Oper(Format("lsr `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    case T_arshift:
      emit(AS_Oper(Format("asr `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    case T_xor:
      emit(AS_Oper(Format("eor `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    }
  }
  else if (tileStm(stm, move_const_to_temp()))
  {
    Temp_temp t = stm->MOVE.dst->TEMP;
    int c = stm->MOVE.src->CONST;
    emit(AS_Move(Format("mov `d0, #%d", c), L(t, NULL), NULL));
  }
  else if (stm->kind == T_MOVE)
  {
    if (stm->MOVE.dst->kind == T_TEMP)
    {
      Temp_temp s = munchExp(stm->MOVE.src);
      emit(AS_Oper("mov `d0, `s0", L(stm->MOVE.dst->TEMP, NULL), L(s, NULL), NULL));
    }
    else if (stm->MOVE.dst->kind == T_MEM)
    {
      Temp_temp t = Temp_newtemp();
      munchStm(T_Move(T_Temp(t), stm->MOVE.dst));
      saveMem(stm->MOVE.dst->MEM, t);
    }
    else
      assert(0);
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
    emit(AS_Oper("<null>", NULL, NULL, NULL));
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
