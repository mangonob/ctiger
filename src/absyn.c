#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"

void *_malloc(size_t byte)
{
  void *p = malloc(byte);

  if (!p)
  {
    fprintf(stderr, "bad memory allocation");
    exit(1);
  }
  else
    return p;
}

A_exp A_IntExp(A_Pos pos, int i)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_intExp;
  p->pos = pos;
  p->int_value = i;
  return p;
}

A_exp A_StrExp(A_Pos pos, A_id str)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_strExp;
  p->pos = pos;
  p->str = str;
  return p;
}

A_exp A_NilExp(A_Pos pos)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_nilExp;
  p->pos = pos;
  return p;
}

A_exp A_VarExp(A_Pos pos, A_var var)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_varExp;
  p->pos = pos;
  p->var = var;
  return p;
}

A_exp A_AssignExp(A_Pos pos, A_var var, A_exp exp)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_assignExp;
  p->pos = pos;
  p->assign.var = var;
  p->assign.exp = exp;
  return p;
}

A_exp A_SeqExp(A_Pos pos, A_expseq seq)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_seqExp;
  p->pos = pos;
  p->seq = seq;
  return p;
}

A_exp A_CallExp(A_Pos pos, A_id func, A_expseq args)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_callExp;
  p->pos = pos;
  p->call.func = func;
  p->call.args = args;
  return p;
}

A_exp A_OpExp(A_Pos pos, A_oper oper, A_exp lhs, A_exp rhs)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_opExp;
  p->pos = pos;
  p->op.oper = oper;
  p->op.lhs = lhs;
  p->op.rhs = rhs;
  return p;
}

A_exp A_RecordExp(A_Pos pos, A_id name, A_record_list record_list)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_recordExp;
  p->pos = pos;
  p->record.name = name;
  p->record.record_list = record_list;
  return p;
}

A_exp A_IfExp(A_Pos pos, A_exp condition, A_exp body, A_exp els)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_ifExp;
  p->pos = pos;
  p->if_exp.condition = condition;
  p->if_exp.body = body;
  p->if_exp.els = els;
  return p;
}

A_exp A_WhileExp(A_Pos pos, A_exp condition, A_exp body)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_whileExp;
  p->pos = pos;
  p->whil.condition = condition;
  p->whil.body = body;
  return p;
}

A_exp A_ForExp(A_Pos pos, A_id var, A_exp lo, A_exp hi, A_exp body)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_forExp;
  p->pos = pos;
  p->forr.var = var;
  p->forr.from = lo;
  p->forr.to = hi;
  p->forr.body = body;
  return p;
}

A_exp A_BreakExp(A_Pos pos)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_breakExp;
  p->pos = pos;
  return p;
}

A_exp A_LetExp(A_Pos pos, A_decs decs, A_expseq body)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_letExp;
  p->pos = pos;
  p->let.decs = decs;
  p->let.body = body;
  return p;
}

A_var A_SimpleVar(A_Pos pos, A_id name)
{
  A_var p = _malloc(sizeof(*p));
  p->type = A_simpleVar;
  p->pos = pos;
  p->simple = name;
  return p;
}

A_var A_FieldVar(A_Pos pos, A_var var, A_id name)
{
  A_var p = _malloc(sizeof(*p));
  p->type = A_fieldVar;
  p->pos = pos;
  p->field.var = var;
  p->field.sym = name;
  return p;
}

A_var A_SubscriptVar(A_Pos pos, A_var var, A_exp exp)
{
  A_var p = _malloc(sizeof(*p));
  p->type = A_subscriptVar;
  p->pos = pos;
  p->subscript.var = var;
  p->subscript.exp = exp;
  return p;
}

A_expseq A_ExpSeq(A_exp head, A_expseq tail)
{
  A_expseq p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

A_record_list A_RecordList(A_record head, A_record_list tail)
{
  A_record_list p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

A_decs A_Decs(A_dec head, A_decs tail)
{
  A_decs p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

A_tyfields A_TyFields(A_tyfield head, A_tyfields tail)
{
  A_tyfields p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

A_id A_Id(A_Pos pos, char *id)
{
  A_id p = _malloc(sizeof(*p));
  p->pos = pos;
  p->id = id;
  return p;
}