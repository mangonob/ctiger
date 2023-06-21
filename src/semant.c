#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include "semant.h"
#include "errormsg.h"
#include "absyn.h"
#include "env.h"
#include "utils.h"

typedef struct expty expty;

struct expty
{
  Tr_exp exp;
  Ty_ty ty;
};

Ty_ty actual_ty(Ty_ty ty)
{
  if (!ty)
    return NULL;

  switch (ty->type)
  {
  case Ty_named:
    assert(ty->named.ty);
    return actual_ty(ty->named.ty);
  default:
    return ty;
  }
}

expty expTy(Tr_exp exp, Ty_ty ty)
{
  expty e;
  e.exp = exp;
  e.ty = actual_ty(ty);
  return e;
}

bool checkType(Ty_ty type, Ty_ty expect)
{
  return actual_ty(type) == actual_ty(expect) ||
         actual_ty(expect)->type == Ty_record && checkType(type, Ty_Nil());
}

/** lookup type from type-environment */
const Ty_ty lookupTenv(S_table tenv, A_id id)
{
  if (!id)
    return NULL;

  const Ty_ty ty = S_lookup(tenv, id->id);

  if (!ty)
    EM_Error(id->pos, "undeclared type %s", S_name(id->id));

  return ty;
}

const E_enventry lookupFunc(S_table venv, A_id id)
{
  if (!id)
    return NULL;

  E_enventry entry = S_lookup(venv, id->id);

  if (!entry || entry->type != E_funEntry)
    EM_Error(id->pos, "undeclared function", S_name(id->id));

  return entry;
}

const E_enventry lookupVar(S_table venv, A_id id)
{
  if (!id)
    return NULL;

  E_enventry entry = S_lookup(venv, id->id);

  if (!entry || entry->type != E_varEntry)
    EM_Error(id->pos, "undeclared variable %s", S_name(id->id));

  return entry;
}

Ty_tyList makeFormalTyList(S_table tenv, A_tyfields params);
void transDecsHead(Tr_level level, S_table venv, S_table tenv, A_decs decs);
void checkupCircularAlias(A_Pos pos, Ty_ty ty, Ty_tyList breadcrumbs);

expty transExp(Tr_level level, S_table venv, S_table tenv, A_exp exp, Temp_label brk);
expty transVar(Tr_level level, S_table venv, S_table tenv, A_var var, Temp_label brk);
Tr_exp transDec(Tr_level level, S_table venv, S_table tenv, A_dec dec, Temp_label brk);
Ty_ty transTy(Tr_level level, S_table tenv, A_ty ty);

Ty_field Ty_FieldListLookup(Ty_fieldList list, S_symbol sym)
{
  Ty_fieldList p = list;
  while (p)
  {
    if (p->head->name == sym)
      return p->head;
    p = p->tail;
  }
  return NULL;
}

int Ty_findFieldListIndex(Ty_fieldList list, Ty_field field)
{
  if (field)
  {
    int index = 0;
    while (list && list->head)
    {
      if (list->head == field)
        return index;
      list = list->tail;
      index += 1;
    }
  }

  return -1;
}

A_tyfield A_TyFieldListLookup(A_tyfields fields, S_symbol sym)
{
  A_tyfields p = fields;
  while (p)
  {
    if (p->head->name->id == sym)
      return p->head;
    p = p->tail;
  }
  return NULL;
}

A_record A_RecordListLookup(A_record_list list, S_symbol sym)
{
  A_record_list p = list;
  while (p)
  {
    if (p->head->name->id == sym)
      return p->head;
    p = p->tail;
  }
  return NULL;
}

expty transVar(Tr_level level, S_table venv, S_table tenv, A_var var, Temp_label brk)
{
  switch (var->type)
  {
  case A_simpleVar:
  {
    E_enventry var_entry = lookupVar(venv, var->simple);
    return expTy(Tr_simpleVar(var_entry->var.access, level), var_entry->var.ty);
  }
  case A_fieldVar:
  {
    expty lvalue = transVar(level, venv, tenv, var->field.var, brk);

    if (lvalue.ty->type == Ty_record)
    {
      Ty_field field = Ty_FieldListLookup(lvalue.ty->record, var->field.sym->id);

      if (field)
      {
        int offset = Ty_findFieldListIndex(lvalue.ty->record, field);
        return expTy(Tr_fieldVar(lvalue.exp, offset), field->ty);
      }
      else
        EM_Error(var->field.sym->pos, "record type have not field %s", S_name(var->field.sym->id));
    }
    else
      EM_Error(var->field.sym->pos, "unexcepted field %s", S_name(var->field.sym->id));
  }
  case A_subscriptVar:
  {
    A_var arr = var->subscript.var;
    A_exp exp = var->subscript.exp;
    expty lvalue = transVar(level, venv, tenv, arr, brk);

    if (lvalue.ty->type == Ty_array)
    {
      expty subscript = transExp(level, venv, tenv, exp, brk);

      if (checkType(subscript.ty, Ty_Int()))
        return expTy(Tr_arrayVar(lvalue.exp, subscript.exp), lvalue.ty->array);
      else
        EM_Error(var->subscript.exp->pos, "subscript must be int");
    }
    else
      EM_Error(var->subscript.var->pos, "unexcepted subscript");
  }
  }
}

expty transExp(Tr_level level, S_table venv, S_table tenv, A_exp exp, Temp_label brk)
{
  switch (exp->type)
  {
  case A_intExp:
    return expTy(Tr_intExp(exp->int_value), Ty_Int());
  case A_strExp:
    return expTy(Tr_stringExp(exp->str), Ty_String());
  case A_nilExp:
    return expTy(Tr_nilExp(), Ty_Nil());
  case A_varExp:
    return transVar(level, venv, tenv, exp->var, brk);
  case A_assignExp:
  {
    expty lvalue = transVar(level, venv, tenv, exp->assign.var, brk);
    expty rvalue = transExp(level, venv, tenv, exp->assign.exp, brk);

    if (checkType(rvalue.ty, lvalue.ty))
      return expTy(Tr_assignExp(lvalue.exp, rvalue.exp), Ty_Void());
    else
      EM_Error(exp->assign.exp->pos, "unmatchd type");
  }
  case A_seqExp:
  {
    A_expseq curr = exp->seq;
    expty exp;
    Tr_expseq el = NULL;

    for (; curr && curr->head; curr = curr->tail)
    {
      exp = transExp(level, venv, tenv, curr->head, brk);
      el = Tr_ExpSeq(exp.exp, el);
    }
    el = Tr_ExpSeqReversed(el);

    return expTy(Tr_seqExp(el), exp.ty);
  }
  case A_opExp:
  {
    expty lhs = transExp(level, venv, tenv, exp->op.lhs, brk);
    expty rhs = transExp(level, venv, tenv, exp->op.rhs, brk);

    switch (exp->op.oper)
    {
    case A_plusOp:
    case A_minusOp:
    case A_timesOp:
    case A_divideOp:
      if (!checkType(lhs.ty, Ty_Int()))
        EM_Error(exp->op.lhs->pos, "must be int type");

      if (!checkType(rhs.ty, Ty_Int()))
        EM_Error(exp->op.rhs->pos, "must be int type");

      return expTy(Tr_arithExp(exp->op.oper, lhs.exp, rhs.exp), Ty_Int());
    case A_gtOp:
    case A_ltOp:
    case A_geOp:
    case A_leOp:
      if (!checkType(lhs.ty, Ty_Int()) && !checkType(lhs.ty, Ty_String()))
        EM_Error(exp->op.lhs->pos, "must be comparable type");

      if (!checkType(rhs.ty, Ty_Int()) && !checkType(rhs.ty, Ty_String()))
        EM_Error(exp->op.rhs->pos, "must be comparable type");

      /** fallthrough to case A_negOp */
    case A_eqOp:
    case A_neqOp:
      if (!checkType(lhs.ty, rhs.ty))
        EM_Error(exp->op.rhs->pos, "unmatch type to compare");

      if (checkType(lhs.ty, Ty_String()))
        return expTy(Tr_strcmpExp(exp->op.oper, lhs.exp, rhs.exp), Ty_Int());
      else /** Ty_Record or Ty_Int */
        return expTy(Tr_logicExp(exp->op.oper, lhs.exp, rhs.exp), Ty_Int());
    }
  }
  case A_callExp:
  {
    E_enventry entry = lookupFunc(venv, exp->call.func);
    assert(entry->type == E_funEntry);

    Ty_ty result = entry->fun.result;
    Ty_tyList formals = entry->fun.formals;
    A_expseq args = exp->call.args;

    Tr_expseq arg_exps = NULL;
    while (formals && formals->head && args && args->head)
    {
      expty arg = transExp(level, venv, tenv, args->head, brk);
      arg_exps = Tr_ExpSeq(arg.exp, arg_exps);

      if (!checkType(arg.ty, formals->head))
        EM_Error(args->head->pos, "arguments type unmatched");

      formals = formals->tail;
      args = args->tail;
    }

    if (formals && formals->head && !args)
      EM_Error(exp->call.func->pos, "too few arguments to function %s", S_name(exp->call.func->id));
    else if (args && args->head && !formals)
      EM_Error(args->head->pos, "too many arguments to function %s", S_name(exp->call.func->id));
    else
      return expTy(Tr_callExp(level, entry->fun.level, entry->fun.label, arg_exps), result);
  }
  case A_letExp:
  {
    Tr_expseq seq = NULL;
    expty bodyexp;

    S_beginScope(venv);
    S_beginScope(tenv);
    {
      A_decs decs = exp->let.decs;

      transDecsHead(level, venv, tenv, decs);

      for (A_decs ds = decs; ds && ds->head; ds = ds->tail)
        seq = Tr_ExpSeq(transDec(level, venv, tenv, ds->head, brk), seq);

      bodyexp = transExp(level, venv, tenv, exp->let.body, brk);
      seq = Tr_ExpSeq(bodyexp.exp, seq);
      seq = Tr_ExpSeqReversed(seq);
    }
    S_endScope(tenv);
    S_endScope(venv);

    return expTy(Tr_seqExp(seq), bodyexp.ty);
  }
  case A_recordExp:
  {
    Ty_ty ty = actual_ty(lookupTenv(tenv, exp->record.type_id));
    if (ty->type != Ty_record)
      EM_Error(exp->record.type_id->pos, "record type expected");

    A_record_list records = exp->record.record_list;
    Ty_fieldList fields = ty->record;

    S_table exps = S_empty();

    for (A_record_list rs = records; rs && rs->head; rs = rs->tail)
    {
      A_record record = rs->head;
      Ty_field field = Ty_FieldListLookup(fields, record->name->id);

      if (field)
      {
        expty value = transExp(level, venv, tenv, record->value, brk);
        S_insert(exps, record->name->id, value.exp);

        if (!checkType(value.ty, field->ty))
          EM_Error(record->value->pos, "field %s type unmatched", S_name(record->name->id));
      }
      else
        EM_Error(record->name->pos, "unexcepted field %s", S_name(record->name->id));
    }

    Tr_expseq inits = NULL;
    for (Ty_fieldList fs = fields; fs && fs->head; fs = fs->tail)
    {
      Ty_field field = fs->head;
      A_record record = A_RecordListLookup(records, fs->head->name);

      if (actual_ty(field->ty)->type != Ty_record && !record)
        EM_Error(exp->record.type_id->pos, "field %s not initialized", fs->head->name->name);

      Tr_exp exp = S_lookup(exps, fs->head->name);
      if (!exp)
        exp = Tr_nilExp();
      inits = Tr_ExpSeq(exp, inits);
    }
    inits = Tr_ExpSeqReversed(inits);

    return expTy(Tr_recordExp(inits), ty);
  }
  case A_arrayExp:
  {
    Ty_ty ty = actual_ty(lookupTenv(tenv, exp->array.type_id));
    if (ty->type != Ty_array)
      EM_Error(exp->array.type_id->pos, "array type expected");

    expty capacity = transExp(level, venv, tenv, exp->array.capacity, brk);
    if (!checkType(capacity.ty, Ty_Int()))
      EM_Error(exp->array.capacity->pos, "array capacity must be int type");

    expty element = transExp(level, venv, tenv, exp->array.element, brk);
    if (!checkType(ty->array, element.ty))
      EM_Error(exp->array.element->pos, "unmatch element type in array expression");

    return expTy(Tr_arrayExp(element.exp, capacity.exp), ty);
  }
  case A_ifExp:
  {
    expty cond = transExp(level, venv, tenv, exp->iff.condition, brk);

    if (!checkType(cond.ty, Ty_Int()))
      EM_Error(exp->iff.condition->pos, "if condition must be int type");

    expty then = transExp(level, venv, tenv, exp->iff.then, brk);

    if (exp->iff.els)
    {
      expty els = transExp(level, venv, tenv, exp->iff.els, brk);

      if (checkType(then.ty, els.ty) || checkType(els.ty, then.ty))
        return expTy(Tr_ifExp(cond.exp, then.exp, els.exp), then.ty);
      else
        EM_Error(exp->iff.els->pos, "unmatch type in if-else expression");
    }
    else
      return expTy(Tr_ifExp(cond.exp, then.exp, NULL), Ty_Void());
  }
  case A_forExp:
  {
    expty from = transExp(level, venv, tenv, exp->forr.from, brk);

    if (!checkType(from.ty, Ty_Int()))
      EM_Error(exp->forr.from->pos, "unmatch with int type");

    expty to = transExp(level, venv, tenv, exp->forr.to, brk);

    if (!checkType(to.ty, Ty_Int()))
      EM_Error(exp->forr.to->pos, "unmatch with int type");

    // break label for for-loop
    Temp_label b = Temp_newLabel();
    S_beginScope(venv);
    {
      S_insert(venv, exp->forr.var->id, E_VarEntry(Tr_allocLocal(level, exp->forr.escape), Ty_Int()));
      expty body = transExp(level, venv, tenv, exp->forr.body, b);

      S_endScope(venv);
      // TOOD: var
      return expTy(Tr_forExp(Tr_nilExp(), from.exp, to.exp, body.exp, b), Ty_Void());
    }
  }
  case A_whileExp:
  {
    expty cond = transExp(level, venv, tenv, exp->whil.condition, brk);
    // break label for while
    Temp_label b = Temp_newLabel();

    if (!checkType(cond.ty, Ty_Int()))
      EM_Error(exp->whil.condition->pos, "while condition must be int type");

    expty body = transExp(level, venv, tenv, exp->whil.body, b);
    return expTy(Tr_whileExp(cond.exp, body.exp, b), Ty_Void());
  }
  case A_breakExp:
    return expTy(Tr_breakExp(brk), Ty_Void());
  }
}

Tr_exp transDec(Tr_level level, S_table venv, S_table tenv, A_dec dec, Temp_label brk)
{
  switch (dec->type)
  {
  case A_varDec:
  {
    A_exp exp = dec->vardec.exp;
    A_id type_id = dec->vardec.type_id;
    A_id var = dec->vardec.var;
    Ty_ty type = lookupTenv(tenv, type_id);
    expty exp_ty = transExp(level, venv, tenv, exp, brk);

    if (type && !checkType(exp_ty.ty, type))
      EM_Error(exp->pos, "expression type unmatched with variable declaration");

    Tr_access acc = Tr_allocLocal(level, dec->vardec.escape);

    if (type)
      S_insert(venv, var->id, E_VarEntry(acc, type));
    else
      S_insert(venv, var->id, E_VarEntry(acc, exp_ty.ty));

    return Tr_assignExp(Tr_simpleVar(acc, level), exp_ty.exp);
  }
  case A_typeDec:
  {
    Ty_ty alias = lookupTenv(tenv, dec->typedec.type_id);
    assert(alias && alias->type == Ty_named);
    A_ty ty = dec->typedec.ty;
    alias->named.ty = transTy(level, tenv, ty);
    checkupCircularAlias(ty->pos, alias, NULL);

    return NULL;
  }
  case A_funcDec:
  {
    E_enventry entry = lookupFunc(venv, dec->funcdec.funcname);
    assert(entry && entry->type == E_funEntry);
    A_tyfields parameters = dec->funcdec.parameters;
    Ty_tyList formals = entry->fun.formals;
    Tr_accessList accesses = Tr_formals(entry->fun.level);

    S_beginScope(venv);
    {
      while (parameters && parameters->head)
      {
        A_tyfield param = parameters->head;
        Ty_ty ty = formals->head;
        Tr_access access = Tr_accessListHead(accesses);

        S_insert(venv, param->name->id, E_VarEntry(access, ty));

        parameters = parameters->tail;
        formals = formals->tail;
        accesses = Tr_accessListTail(accesses);
      }

      expty body = transExp(entry->fun.level, venv, tenv, dec->funcdec.body, brk);

      if (entry->fun.result && entry->fun.result != Ty_Void() && !checkType(entry->fun.result, body.ty))
        EM_Error(dec->funcdec.body->pos, "function return type unmatched");

      Tr_procEntryExit(entry->fun.level, body.exp, accesses);
    }
    S_endScope(venv);

    return NULL;
  }
  }
}

Ty_ty transTy(Tr_level level, S_table tenv, A_ty ty)
{
  switch (ty->type)
  {
  case A_namedTy:
    return lookupTenv(tenv, ty->named);
  case A_arrayTy:
    return Ty_Array(lookupTenv(tenv, ty->array));
  case A_recordTy:
  {
    A_tyfields fields = ty->fields;
    Ty_fieldList tyfields = NULL;

    for (; fields && fields->head; fields = fields->tail)
    {
      A_tyfield field = fields->head;
      Ty_ty ty = lookupTenv(tenv, field->type_id);

      if (Ty_FieldListLookup(tyfields, field->name->id))
        EM_Error(field->name->pos, "redeclare field %s", S_name(field->name->id));

      tyfields = Ty_FieldList(Ty_Field(field->name->id, ty), tyfields);
    }

    Ty_fieldList r = Ty_FieldListReversed(tyfields);
    return Ty_Record(r);
  }
  }
}

void checkupCircularAlias(A_Pos pos, Ty_ty ty, Ty_tyList breadcrumbs)
{
  if (!ty)
    return;

  if (ty->type == Ty_named)
  {
    Ty_tyList curr = breadcrumbs;
    Ty_tyList link = NULL;

    while (curr && curr->head)
    {
      link = Ty_TyList(curr->head, link);

      if (curr->head == ty)
      {
        fprintf(stderr, "circular alias detected ");

        for (; link && link->head; link = link->tail)
          fprintf(stderr, "%s -> ", link->head->named.sym->name);

        fprintf(stderr, "%s", ty->named.sym->name);
        EM_Error(pos, NULL);
      }

      curr = curr->tail;
    }

    checkupCircularAlias(pos, ty->named.ty, Ty_TyList(ty, breadcrumbs));
  }
}

Ty_tyList makeFormalTyList(S_table tenv, A_tyfields params)
{
  Ty_tyList tys = NULL;

  for (Ty_tyList curr = tys; params && params->head; params = params->tail)
  {
    A_tyfield field = params->head;
    Ty_ty ty = lookupTenv(tenv, field->type_id);

    if (curr)
    {
      curr->tail = Ty_TyList(ty, NULL);
      curr = curr->tail;
    }
    else
    {
      curr = Ty_TyList(ty, NULL);
    }

    if (tys == NULL)
      tys = curr;
  }

  return tys;
}

U_boolList makeFormalBoolList(A_tyfields params)
{
  U_boolList r = NULL;
  for (; params && params->head; params = params->tail)
    r = U_BoolList(params->head->escape, r);
  return U_BoolListReversed(r);
}

static void transDecHead(Tr_level parent, S_table venv, S_table tenv, A_dec dec)
{
  if (dec->type == A_typeDec)
  {
    S_symbol id = dec->typedec.type_id->id;
    S_insert(tenv, id, Ty_Named(id, NULL));
  }
  else if (dec->type == A_funcDec)
  {
    A_tyfields parameters = dec->funcdec.parameters;
    A_id return_type = dec->funcdec.return_type;
    Ty_tyList formalTys = makeFormalTyList(tenv, parameters);
    U_boolList escapes = makeFormalBoolList(parameters);
    Temp_label label = Temp_newProcLabel(dec->funcdec.funcname->id->name);
    Tr_level level = Tr_newLevel(parent, label, escapes);

    if (return_type)
      S_insert(venv, dec->funcdec.funcname->id, E_FunEntry(level, label, formalTys, lookupTenv(tenv, return_type)));
    else
      S_insert(venv, dec->funcdec.funcname->id, E_FunEntry(level, label, formalTys, Ty_Void()));
  }
}

void transDecsHead(Tr_level level, S_table venv, S_table tenv, A_decs decs)
{
  for (; decs && decs->head; decs = decs->tail)
    transDecHead(level, venv, tenv, decs->head);
}

F_fragList SEM_transProg(A_exp exp)
{
  expty prog = transExp(Tr_outermost(), E_base_venv(), E_base_tenv(), exp, NULL);
  Tr_procEntryExit(Tr_outermost(), prog.exp, NULL);
  return Tr_getResult();
}
