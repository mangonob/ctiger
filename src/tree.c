#include <stdarg.h>
#include <assert.h>
#include "tree.h"
#include "utils.h"

T_expList T_ExpList(T_exp head, T_expList tail)
{
  T_expList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

T_stmList T_StmList(T_stm head, T_stmList tail)
{
  T_stmList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

T_stm T_Seq(T_stm left, T_stm right)
{
  T_stm p = _malloc(sizeof(*p));
  p->kind = T_SEQ;
  p->SEQ.left = left;
  p->SEQ.right = right;
  return p;
}

T_stm T_vSeq(T_stm stm, ...)
{
  if (!stm)
    return NULL;

  va_list args;
  va_start(args, stm);

  T_stm seq = T_Seq(stm, NULL);
  T_stm curr = seq;

  for (void *p = va_arg(args, T_stm); p;)
  {
    curr->SEQ.right = T_Seq(p, NULL);
    curr = curr->SEQ.right;
    p = va_arg(args, T_stm);
  }

  return seq;
}

T_stm T_Label(Temp_label label)
{
  T_stm p = _malloc(sizeof(*p));
  p->kind = T_LABEL;
  p->LABEL = label;
  return p;
}

T_stm T_Jump(T_exp exp, Temp_labelList labels)
{
  T_stm p = _malloc(sizeof(*p));
  p->kind = T_JUMP;
  p->JUMP.exp = exp;
  p->JUMP.jumps = labels;
  return p;
}

T_stm T_Cjump(T_relOp op, T_exp lhs, T_exp rhs, Temp_label trueLabel, Temp_label falseLabel)
{
  T_stm p = _malloc(sizeof(*p));
  p->kind = T_CJUMP;
  p->CJUMP.op = op;
  p->CJUMP.lhs = lhs;
  p->CJUMP.rhs = rhs;
  p->CJUMP.trueLabel = trueLabel;
  p->CJUMP.falseLabel = falseLabel;
  return p;
}

T_stm T_Move(T_exp dst, T_exp src)
{
  T_stm p = _malloc(sizeof(*p));
  p->kind = T_MOVE;
  p->MOVE.dst = dst;
  p->MOVE.src = src;
  return p;
}

T_stm T_Exp(T_exp exp)
{
  T_stm p = _malloc(sizeof(*p));
  p->kind = T_EXP;
  p->EXP = exp;
  return p;
}

T_exp T_Binop(T_binOp op, T_exp lhs, T_exp rhs)
{
  T_exp p = _malloc(sizeof(*p));
  p->kind = T_BINOP;
  p->BINOP.op = op;
  p->BINOP.left = lhs;
  p->BINOP.right = rhs;
  return p;
}

T_exp T_Mem(T_exp exp)
{
  T_exp p = _malloc(sizeof(*p));
  p->kind = T_MEM;
  p->MEM = exp;
  return p;
}

T_exp T_Temp(Temp_temp temp)
{
  T_exp p = _malloc(sizeof(*p));
  p->kind = T_TEMP;
  p->TEMP = temp;
  return p;
}

T_exp T_Eseq(T_stm stm, T_exp exp)
{
  T_exp p = _malloc(sizeof(*p));
  p->kind = T_ESEQ;
  p->ESEQ.stm = stm;
  p->ESEQ.exp = exp;
  return p;
}

T_exp T_Name(Temp_label l)
{
  T_exp p = _malloc(sizeof(*p));
  p->kind = T_NAME;
  p->NAME = l;
  return p;
}

T_exp T_Const(int value)
{
  T_exp p = _malloc(sizeof(*p));
  p->kind = T_CONST;
  p->CONST = value;
  return p;
}

T_exp T_Call(T_exp fun, T_expList args)
{
  T_exp p = _malloc(sizeof(*p));
  p->kind = T_CALL;
  p->CALL.fun = fun;
  p->CALL.args = args;
  return p;
}

T_relOp T_notRel(T_relOp relOp)
{
  switch (relOp)
  {
  case T_eq:
    return T_ne;
  case T_ne:
    return T_eq;
  case T_lt:
    return T_ge;
  case T_gt:
    return T_le;
  case T_le:
    return T_gt;
  case T_ge:
    return T_lt;
  case T_ult:
    return T_uge;
  case T_ule:
    return T_ugt;
  case T_ugt:
    return T_ule;
  case T_uge:
    return T_ult;
  }
}

T_relOp T_commute(T_relOp relOp)
{
  switch (relOp)
  {
  case T_eq:
    return T_eq;
  case T_ne:
    return T_ne;
  case T_lt:
    return T_gt;
  case T_gt:
    return T_lt;
  case T_le:
    return T_ge;
  case T_ge:
    return T_le;
  case T_ult:
    return T_ugt;
  case T_ule:
    return T_uge;
  case T_ugt:
    return T_ult;
  case T_uge:
    return T_ule;
  }
}
