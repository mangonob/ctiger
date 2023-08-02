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
    emit(AS_Oper("bl `j0", NULL, NULL, AS_Targets(stm->JUMP.jumps)));
  }
  else if (stm->kind == T_JUMP)
  {
    Temp_temp t = munchExp(stm->JUMP.exp);
    emit(AS_Oper("bl `s0", NULL, L(t, NULL), AS_Targets(stm->JUMP.jumps)));
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
  else if (tileStm(stm, move_binop_temp_const_to_temp()))
  {
    T_binOp op = stm->MOVE.src->BINOP.op;
    Temp_temp d = stm->MOVE.dst->TEMP;
    Temp_temp s = stm->MOVE.src->BINOP.left->TEMP;
    int c = stm->MOVE.src->BINOP.right->CONST;

    switch (op)
    {
    case T_plus:
      if (c < 0x1000)
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
      if (c <= 0x1000)
      {
        emit(AS_Oper(Format("subs `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      }
      else
      {
        Temp_temp t = Temp_newtemp();
        emit(AS_Move(Format("mov `d0 #%d", c), L(t, NULL), NULL));
        emit(AS_Oper("subs `d0, `s0, `s1", L(d, NULL), L(s, L(t, NULL)), NULL));
      }
    case T_mul:
      emit(AS_Oper(Format("mul `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
    case T_div:
      emit(AS_Oper(Format("sdiv `d0, `s0, #%d", c), L(d, NULL), L(s, NULL), NULL));
      break;
    default:
      // TODO
      assert(0);
    }
  }
  else if (tileStm(stm, move_const_to_temp()))
  {
    Temp_temp t = stm->MOVE.dst->TEMP;
    int c = stm->MOVE.src->CONST;
    emit(AS_Move(Format("mov `d0, #%d", c), L(t, NULL), NULL));
  }
  else
  {
    emit(AS_Oper("<null>", NULL, NULL, NULL));
  }
}

static Temp_tempList munchArgs(int i, T_expList args)
{
  // TODO
  return NULL;
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
