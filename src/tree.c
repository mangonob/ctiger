#include <stdarg.h>
#include "tree.h"
#include "utils.h"

T_exp T_Call(T_exp fun, T_expList args)
{
  T_exp p = _malloc(sizeof(p));
  p->kind = T_CALL;
  p->CALL.fun = fun;
  p->CALL.args = args;
  return p;
}

T_exp T_Name(Temp_label l)
{
  T_exp p = _malloc(sizeof(p));
  p->kind = T_NAME;
  p->NAME = l;
  return p;
}

T_stm T_Seq(T_stm left, T_stm right)
{
  T_stm p = _malloc(sizeof(p));
  p->kind = T_SEQ;
  p->SEQ.left = left;
  p->SEQ.right = right;
  return p;
}

T_stm vT_Seq(T_stm stm, ...)
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

T_exp T_Eseq(T_stm stm, T_exp exp)
{
  T_exp p = _malloc(sizeof(p));
  p->kind = T_ESEQ;
  p->ESEQ.stm = stm;
  p->ESEQ.exp = exp;
  return p;
}

T_exp vT_Eseq(T_stm stm, ...)
{
  if (!stm)
    return NULL;

  T_exp root = T_Eseq(stm, NULL);
  T_exp exp = root;

  va_list args;
  va_start(args, stm);
  void *curr = va_arg(args, void *);
  void *next = va_arg(args, void *);
  while (curr)
  {
    if (next)
    {
      exp->ESEQ.exp = T_Eseq(curr, NULL);
    }
    else
    {
      exp->ESEQ.exp = curr;
    }

    curr = next;
    next = va_arg(args, void *);
  }
  va_end(args);

  return root;
}