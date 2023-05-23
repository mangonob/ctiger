#include <stdarg.h>
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

T_exp T_vEseq(T_exp exp, T_stm sideEffect, ...)
{
  if (!sideEffect)
    return exp;

  va_list args;
  va_start(args, sideEffect);
  T_exp eseq = T_Eseq(sideEffect, exp);
  T_exp result = eseq;

  T_stm stm = va_arg(args, T_stm);
  while (stm)
  {
    eseq->ESEQ.exp = T_Eseq(stm, eseq->ESEQ.exp);
    eseq = eseq->ESEQ.exp;
    stm = va_arg(args, T_stm);
  }

  va_end(args);
  return result;
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
