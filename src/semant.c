#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <assert.h>
#include "semant.h"
#include "error.h"
#include "absyn.h"
#include "env.h"
#include "utils.h"

/** make expty */
expty expTy(Tr_exp exp, Ty_ty ty);

Ty_ty actual_ty(Ty_ty ty);

/** Check the actual type of Ty_ty */
bool checkType(Ty_ty source, Ty_ty target);

const Ty_ty lookupTenv(S_table tenv, A_id id);

const E_enventry lookupFunc(S_table venv, A_id id);

const E_enventry lookupVar(S_table venv, A_id id);

Ty_tyList makeFormalTyList(S_table tenv, A_tyfields params);

void transDecHead(A_dec dec, va_list args);

void visitDec(A_dec dec, va_list args);

void checkupCircularAlias(A_Pos pos, Ty_ty ty, Ty_tyList breadcrumbs);

void travelDecs(A_decs decs, void (*visit)(A_dec dec, va_list), ...);

Ty_field Ty_FieldListLookup(Ty_fieldList list, S_symbol sym);

A_tyfield A_TyFieldListLookup(A_tyfields fields, S_symbol sym);

A_record A_RecordListLookup(A_record_list list, S_symbol sym);

/** Format semantic error */
_Noreturn void SM_Error(A_Pos pos, const char *msg, ...);

expty transExp(S_table venv, S_table tenv, A_exp exp)
{
  switch (exp->type)
  {
  case A_intExp:
    return expTy(NULL, Ty_Int());
  case A_strExp:
    return expTy(NULL, Ty_String());
  case A_nilExp:
    return expTy(NULL, Ty_Nil());
  case A_varExp:
    return transVar(venv, tenv, exp->var);
  case A_assignExp:
  {
    expty lvalue = transVar(venv, tenv, exp->assign.var);
    expty rvalue = transExp(venv, tenv, exp->assign.exp);

    // TODO: record = nil
    if (checkType(rvalue.ty, lvalue.ty))
      return expTy(NULL, Ty_Void());
    else
      SM_Error(exp->assign.exp->pos, "unmatchd type");
  }
  case A_seqExp:
  {
    A_expseq curr = exp->seq;

    for (; curr && curr->tail; curr = curr->tail)
      transExp(venv, tenv, curr->head);

    if (curr && curr->head)
      return transExp(venv, tenv, curr->head);
    else
      return expTy(NULL, Ty_Void());
  }
  case A_opExp:
  {
    expty lhs = transExp(venv, tenv, exp->op.lhs);
    expty rhs = transExp(venv, tenv, exp->op.rhs);

    switch (exp->op.oper)
    {
    case A_plusOp:
    case A_minusOp:
    case A_timesOp:
    case A_divideOp:
    case A_andOp:
    case A_orOp:
    {
      if (checkType(lhs.ty, Ty_Int()) && checkType(rhs.ty, Ty_Int()))
        return expTy(NULL, Ty_Int());
      else
        SM_Error(exp->op.lhs->pos, "except int type");
    }
    case A_eqOp:
    case A_neqOp:
    {
      Ty_ty ty_l = actual_ty(lhs.ty);
      Ty_ty ty_r = actual_ty(rhs.ty);

      bool isAddressCompare =
          ty_l->type == Ty_record && ty_l == ty_r ||
          ty_l->type == Ty_record && ty_r == Ty_Nil() ||
          ty_l == Ty_Nil() && ty_r->type == Ty_record;

      if (isAddressCompare)
        return expTy(NULL, Ty_Int());
    }
    case A_gtOp:
    case A_ltOp:
    case A_geOp:
    case A_leOp:
    {
      if (!checkType(lhs.ty, Ty_Int()) && !checkType(lhs.ty, Ty_String()))
        SM_Error(exp->op.lhs->pos, "must be comparable type");

      if (!checkType(rhs.ty, Ty_Int()) && !checkType(rhs.ty, Ty_String()))
        SM_Error(exp->op.rhs->pos, "must be comparable type");

      if (!checkType(rhs.ty, lhs.ty))
        SM_Error(exp->op.rhs->pos, "unmatch type to compare");

      return expTy(NULL, Ty_Int());
    }
    }
  }
  case A_callExp:
  {
    E_enventry entry = lookupFunc(venv, exp->call.func);
    assert(entry->type == E_funEntry);

    Ty_ty result = entry->fun.result;
    Ty_tyList formals = entry->fun.formals;
    A_expseq args = exp->call.args;

    while (formals && formals->head && args && args->head)
    {
      expty arg = transExp(venv, tenv, args->head);

      if (!checkType(arg.ty, formals->head))
        SM_Error(args->head->pos, "arguments type unmatched");

      formals = formals->tail;
      args = args->tail;
    }

    if (formals && formals->head && !args)
    {
      SM_Error(exp->call.func->pos, "too few arguments to function %s", S_name(exp->call.func->id));
    }
    else if (args && args->head && !formals)
    {
      SM_Error(args->head->pos, "too many arguments to function %s", S_name(exp->call.func->id));
    }
    else
    {
      return expTy(NULL, result);
    }
  }
  case A_letExp:
  {
    S_beginScope(venv);
    S_beginScope(tenv);
    {
      A_decs decs = exp->let.decs;
      A_expseq body = exp->let.body;

      travelDecs(decs, transDecHead, venv, tenv);
      travelDecs(decs, visitDec, venv, tenv, true);
      travelDecs(decs, visitDec, venv, tenv, false);

      for (; body && body->tail; body = body->tail)
        transExp(venv, tenv, body->head);

      expty result = body && body->head ? transExp(venv, tenv, body->head) : expTy(NULL, Ty_Void());

      S_endScope(tenv);
      S_endScope(venv);
      return result;
    }
  }
  case A_recordExp:
  {
    Ty_ty ty = actual_ty(lookupTenv(tenv, exp->record.type_id));
    if (ty->type != Ty_record)
      SM_Error(exp->record.type_id->pos, "record type expected");

    A_record_list records = exp->record.record_list;
    Ty_fieldList fields = ty->record;

    for (A_record_list _records = records; _records && _records->head; _records = _records->tail)
    {
      A_record record = _records->head;
      Ty_field field = Ty_FieldListLookup(fields, record->name->id);

      if (field)
      {
        expty value = transExp(venv, tenv, record->value);

        if (!checkType(value.ty, field->ty))
          SM_Error(record->value->pos, "field %s type unmatched", S_name(record->name->id));
      }
      else
      {
        SM_Error(record->name->pos, "unexcepted field %s", S_name(record->name->id));
      }
    }

    for (Ty_fieldList _fields = fields; _fields && _fields->head; _fields = _fields->tail)
    {
      Ty_field field = _fields->head;
      A_record record = A_RecordListLookup(records, _fields->head->name);

      if (actual_ty(field->ty)->type != Ty_record && !record)
        SM_Error(exp->record.type_id->pos, "field %s not initialized", _fields->head->name->name);
    }

    return expTy(NULL, ty);
  }
  case A_arrayExp:
  {
    Ty_ty ty = actual_ty(lookupTenv(tenv, exp->array.type_id));
    if (ty->type != Ty_array)
      SM_Error(exp->array.type_id->pos, "array type expected");

    expty element = transExp(venv, tenv, exp->array.element);

    if (!checkType(ty->array, element.ty))
      SM_Error(exp->array.element->pos, "unmatch element type in array expression");

    return expTy(NULL, ty);
  }
  case A_ifExp:
  {
    expty cond = transExp(venv, tenv, exp->if_exp.condition);

    if (!checkType(cond.ty, Ty_Int()))
      SM_Error(exp->if_exp.condition->pos, "if condition must be int type");

    expty body = transExp(venv, tenv, exp->if_exp.body);

    if (exp->if_exp.els)
    {
      expty els = transExp(venv, tenv, exp->if_exp.els);

      if (checkType(body.ty, els.ty) || checkType(els.ty, body.ty))
        return expTy(NULL, body.ty);
      else
        SM_Error(exp->if_exp.els->pos, "unmatch type in if-else expression");
    }
    else
    {
      return expTy(NULL, Ty_Void());
    }
  }
  case A_forExp:
  {
    expty from = transExp(venv, tenv, exp->forr.from);

    if (!checkType(from.ty, Ty_Int()))
      SM_Error(exp->forr.from->pos, "unmatch with int type");

    expty to = transExp(venv, tenv, exp->forr.to);

    if (!checkType(to.ty, Ty_Int()))
      SM_Error(exp->forr.to->pos, "unmatch with int type");

    S_beginScope(venv);
    {
      S_insert(venv, exp->forr.var->id, E_VarEntry(Ty_Int()));
      expty body = transExp(venv, tenv, exp->forr.body);

      S_endScope(venv);
      return body;
    }
  }
  case A_whileExp:
  {
    expty cond = transExp(venv, tenv, exp->whil.condition);

    if (!checkType(cond.ty, Ty_Int()))
      SM_Error(exp->whil.condition->pos, "while condition must be int type");

    transExp(venv, tenv, exp->whil.body);

    return expTy(NULL, Ty_Void());
  }
  case A_breakExp:
    return expTy(NULL, Ty_Void());
  }
}

expty transVar(S_table venv, S_table tenv, A_var var)
{
  switch (var->type)
  {
  case A_simpleVar:
    return expTy(NULL, lookupVar(venv, var->simple)->var);
  case A_fieldVar:
  {
    expty lvalue = transVar(venv, tenv, var->field.var);

    if (lvalue.ty->type == Ty_record)
    {
      Ty_field field = Ty_FieldListLookup(lvalue.ty->record, var->field.sym->id);

      if (field)
        return expTy(NULL, field->ty);
      else
        SM_Error(var->field.sym->pos, "record type have not field %s", S_name(var->field.sym->id));
    }
    else
    {
      SM_Error(var->field.sym->pos, "unexcepted field %s", S_name(var->field.sym->id));
    }

    break;
  }
  case A_subscriptVar:
  {
    A_var arr = var->subscript.var;
    A_exp exp = var->subscript.exp;
    expty lvalue = transVar(venv, tenv, arr);

    if (lvalue.ty->type == Ty_array)
    {
      expty subscript = transExp(venv, tenv, exp);

      if (checkType(subscript.ty, Ty_Int()))
        return expTy(NULL, lvalue.ty->array);
      else
        SM_Error(var->subscript.exp->pos, "subscript must be int");
    }
    else
    {
      SM_Error(var->subscript.var->pos, "unexcepted subscript");
    }

    break;
  }
  }
}

void visitDec(A_dec dec, va_list args)
{
  va_list dupargs;
  va_copy(dupargs, args);
  S_table venv = va_arg(dupargs, S_table);
  S_table tenv = va_arg(dupargs, S_table);
  int onlyTypeDeclare = va_arg(dupargs, int);
  va_end(dupargs);

  if (onlyTypeDeclare && dec->type == A_typeDec || !onlyTypeDeclare && dec->type != A_typeDec)
    transDec(venv, tenv, dec);
}

void transDec(S_table venv, S_table tenv, A_dec dec)
{
  switch (dec->type)
  {
  case A_varDec:
  {
    // TODO redeclare variable in same scope
    A_exp exp = dec->vardec.exp;
    A_id type_id = dec->vardec.type_id;
    A_id var = dec->vardec.var;
    Ty_ty type = lookupTenv(tenv, type_id);
    expty exp_ty = transExp(venv, tenv, exp);

    if (type && !checkType(exp_ty.ty, type))
      SM_Error(exp->pos, "expression type unmatched with variable declaration");

    if (type)
      S_insert(venv, var->id, E_VarEntry(type));
    else
      S_insert(venv, var->id, E_VarEntry(exp_ty.ty));

    break;
  }
  case A_typeDec:
  {
    Ty_ty alias = lookupTenv(tenv, dec->typedec.type_id);
    assert(alias && alias->type == Ty_named);
    A_ty ty = dec->typedec.ty;
    alias->named.ty = transTy(tenv, ty);
    checkupCircularAlias(ty->pos, alias, NULL);

    break;
  }
  case A_funcDec:
  {
    E_enventry entry = lookupFunc(venv, dec->funcdec.funcname);
    assert(entry && entry->type == E_funEntry);
    A_tyfields parameters = dec->funcdec.parameters;
    Ty_tyList formals = entry->fun.formals;

    S_beginScope(venv);
    {
      while (parameters && parameters->head && formals && formals->head)
      {
        A_tyfield param = parameters->head;
        Ty_ty ty = formals->head;
        S_insert(venv, param->name->id, E_VarEntry(ty));

        parameters = parameters->tail;
        formals = formals->tail;
      }

      expty init = transExp(venv, tenv, dec->funcdec.init);

      if (entry->fun.result && entry->fun.result != Ty_Void() && !checkType(entry->fun.result, init.ty))
        SM_Error(dec->funcdec.init->pos, "function return type unmatched");
    }
    S_endScope(venv);

    break;
  }
  }
}

Ty_ty transTy(S_table tenv, A_ty ty)
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
        SM_Error(field->name->pos, "redeclare field %s", S_name(field->name->id));

      tyfields = Ty_FieldList(Ty_Field(field->name->id, ty), tyfields);
    }

    Ty_fieldList r = Ty_FieldListReverse(tyfields);
    return Ty_Record(r);
  }
  }
}

void travelDecs(A_decs decs, void (*visit)(A_dec dec, va_list), ...)
{
  va_list args;
  va_start(args, visit);

  for (A_decs curr = decs; curr && curr->head; curr = curr->tail)
  {
    A_dec dec = curr->head;
    visit(dec, args);
  }

  va_end(args);
}

expty expTy(Tr_exp exp, Ty_ty ty)
{
  expty e;
  e.exp = exp;
  e.ty = actual_ty(ty);
  return e;
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
        SM_Error(pos, NULL);
      }

      curr = curr->tail;
    }

    checkupCircularAlias(pos, ty->named.ty, Ty_TyList(ty, breadcrumbs));
  }
}

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

bool checkType(Ty_ty source, Ty_ty target)
{
  return actual_ty(target) == actual_ty(source) ||
         actual_ty(target)->type == Ty_record && checkType(source, Ty_Nil());
}

/** lookup type from type-environment */
const Ty_ty lookupTenv(S_table tenv, A_id id)
{
  if (!id)
    return NULL;

  const Ty_ty ty = S_lookup(tenv, id->id);

  if (!ty)
    SM_Error(id->pos, "undeclared type %s", S_name(id->id));

  return ty;
}

const E_enventry lookupFunc(S_table venv, A_id id)
{
  if (!id)
    return NULL;

  E_enventry entry = S_lookup(venv, id->id);

  if (!entry || entry->type != E_funEntry)
    SM_Error(id->pos, "undeclared function", S_name(id->id));

  return entry;
}

const E_enventry lookupVar(S_table venv, A_id id)
{
  if (!id)
    return NULL;

  E_enventry entry = S_lookup(venv, id->id);

  if (!entry || entry->type != E_varEntry)
    SM_Error(id->pos, "undeclared variable %s", S_name(id->id));

  return entry;
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

void transDecHead(A_dec dec, va_list args)
{
  va_list dupargs;
  va_copy(dupargs, args);
  S_table venv = va_arg(dupargs, S_table);
  S_table tenv = va_arg(dupargs, S_table);
  va_end(dupargs);

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

    if (return_type)
      S_insert(venv, dec->funcdec.funcname->id, E_FunEntry(formalTys, lookupTenv(tenv, return_type)));
    else
      S_insert(venv, dec->funcdec.funcname->id, E_FunEntry(formalTys, Ty_Void()));
  }
}

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

_Noreturn void SM_Error(A_Pos pos, const char *msg, ...)
{
  if (msg)
  {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
  }

  fprintf(stderr, " (line: %d, column: %d)\n", pos.row, pos.column);
  exit(Semant_Error);
}
