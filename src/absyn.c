#include <stdio.h>
#include "absyn.h"
#include "utils.h"

A_exp A_IntExp(A_Pos pos, long i)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_intExp;
  p->pos = pos;
  p->int_value = i;
  return p;
}

A_exp A_StrExp(A_Pos pos, char *str)
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

A_exp A_VarExp(A_var var)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_varExp;
  p->pos = var->pos;
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

A_exp A_RecordExp(A_Pos pos, A_id type_id, A_record_list record_list)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_recordExp;
  p->pos = pos;
  p->record.type_id = type_id;
  p->record.record_list = record_list;
  return p;
}

A_exp A_ArrayExp(A_Pos pos, A_id type_id, A_exp capcity, A_exp element)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_arrayExp;
  p->pos = pos;
  p->array.type_id = type_id;
  p->array.capcity = capcity;
  p->array.element = element;
  return p;
}

A_exp A_IfExp(A_Pos pos, A_exp condition, A_exp then, A_exp els)
{
  A_exp p = _malloc(sizeof(*p));
  p->type = A_ifExp;
  p->pos = pos;
  p->iff.condition = condition;
  p->iff.then = then;
  p->iff.els = els;
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
  p->forr.escape = false;
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

A_expseq A_ExpSeqReverse(A_expseq seq)
{
  A_expseq r = NULL;

  for (; seq && seq->head; seq = seq->tail)
    r = A_ExpSeq(seq->head, r);

  return r;
}

A_record A_Record(A_Pos pos, A_id name, A_exp value)
{
  A_record p = _malloc(sizeof(*p));
  p->pos = pos;
  p->name = name;
  p->value = value;
  return p;
}

A_record_list A_RecordList(A_record head, A_record_list tail)
{
  A_record_list p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

A_record_list A_RecordListReverse(A_record_list list)
{
  A_record_list r = NULL;

  for (; list && list->head; list = list->tail)
    r = A_RecordList(list->head, r);

  return r;
}

A_dec A_FuncDec(A_Pos pos, A_id name, A_tyfields parameters, A_id return_type, A_exp init)
{
  A_dec p = _malloc(sizeof(*p));
  p->type = A_funcDec;
  p->pos = pos;
  p->funcdec.funcname = name;
  p->funcdec.parameters = parameters;
  p->funcdec.return_type = return_type;
  p->funcdec.body = init;
  return p;
}

A_dec A_TypeDec(A_Pos pos, A_id type_id, A_ty ty)
{
  A_dec p = _malloc(sizeof(*p));
  p->type = A_typeDec;
  p->pos = pos;
  p->typedec.type_id = type_id;
  p->typedec.ty = ty;
  return p;
}

A_dec A_VarDec(A_Pos pos, A_id var, A_id type_id, A_exp exp)
{
  A_dec p = _malloc(sizeof(*p));
  p->type = A_varDec;
  p->pos = pos;
  p->vardec.var = var;
  p->vardec.type_id = type_id;
  p->vardec.exp = exp;
  p->vardec.escape = false;
  return p;
}

A_ty A_NamedTy(A_Pos pos, A_id named)
{
  A_ty p = _malloc(sizeof(*p));
  p->pos = pos;
  p->type = A_namedTy;
  p->named = named;
  return p;
}

A_ty A_ArrayTy(A_Pos pos, A_id array)
{
  A_ty p = _malloc(sizeof(*p));
  p->pos = pos;
  p->type = A_arrayTy;
  p->array = array;
  return p;
}

A_ty A_RecordTy(A_Pos pos, A_tyfields fields)
{
  A_ty p = _malloc(sizeof(*p));
  p->pos = pos;
  p->type = A_recordTy;
  p->fields = fields;
  return p;
}

A_decs A_Decs(A_dec head, A_decs tail)
{
  A_decs p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

A_decs A_DecsReverse(A_decs decs)
{
  A_decs r = NULL;

  for (; decs && decs->head; decs = decs->tail)
    r = A_Decs(decs->head, r);

  return r;
}

A_tyfields A_TyFields(A_tyfield head, A_tyfields tail)
{
  A_tyfields p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

A_tyfields A_TyFieldsReverse(A_tyfields tyfields)
{
  A_tyfields r = NULL;

  for (; tyfields && tyfields->head; tyfields = tyfields->tail)
    r = A_TyFields(tyfields->head, r);

  return r;
}

A_tyfield A_TyField(A_Pos pos, A_id name, A_id type_id)
{
  A_tyfield p = _malloc(sizeof(*p));
  p->name = name;
  p->type_id = type_id;
  p->pos = pos;
  p->escape = false;
  return p;
}

A_id A_Id(A_Pos pos, S_symbol id)
{
  A_id p = _malloc(sizeof(*p));
  p->pos = pos;
  p->id = id;
  return p;
}
