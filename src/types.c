#include <stdio.h>
#include "types.h"
#include "utils.h"

static struct Ty_ty_ tyNil = {Ty_nil};
Ty_ty Ty_Nil() { return &tyNil; }

static struct Ty_ty_ tyInt = {Ty_int};
Ty_ty Ty_Int() { return &tyInt; }

static struct Ty_ty_ tyString = {Ty_string};
Ty_ty Ty_String() { return &tyString; }

static struct Ty_ty_ tyVoid = {Ty_void};
Ty_ty Ty_Void() { return &tyVoid; };

Ty_ty Ty_Array(Ty_ty ty)
{
  Ty_ty array = _malloc(sizeof(*array));
  array->type = Ty_array;
  array->array = ty;
  return array;
}

Ty_ty Ty_Named(S_symbol sym, Ty_ty ty)
{
  Ty_ty named = _malloc(sizeof(*named));
  named->type = Ty_named;
  named->named.sym = sym;
  named->named.ty = ty;
  return named;
}

Ty_ty Ty_Record(Ty_fieldList fields)
{
  Ty_ty record = _malloc(sizeof(*record));
  record->type = Ty_record;
  record->record = fields;
  return record;
}

Ty_tyList Ty_TyList(Ty_ty head, Ty_tyList tail)
{
  Ty_tyList list = _malloc(sizeof(*list));
  list->head = head;
  list->tail = tail;
  return list;
}

Ty_tyList Ty_TyListReversed(Ty_tyList tys)
{
  Ty_tyList r = NULL;

  for (; tys && tys->head; tys = tys->tail)
    r = Ty_TyList(tys->head, r);

  return r;
}

Ty_field Ty_Field(S_symbol name, Ty_ty ty)
{
  Ty_field field = _malloc(sizeof(*field));
  field->name = name;
  field->ty = ty;
  return field;
}

Ty_fieldList Ty_FieldList(Ty_field head, Ty_fieldList tail)
{
  Ty_fieldList fieldList = _malloc(sizeof(*fieldList));
  fieldList->head = head;
  fieldList->tail = tail;
  return fieldList;
}

Ty_fieldList Ty_FieldListReversed(Ty_fieldList fields)
{
  Ty_fieldList r = NULL;

  for (; fields && fields->head; fields = fields->tail)
    r = Ty_FieldList(fields->head, r);

  return r;
}

int tyListLen(Ty_tyList list)
{
  return list ? tyListLen(list->tail) + 1 : 0;
}

int fprintTy(FILE *file, Ty_ty ty)
{
  if (!ty)
    return fprintf(file, "<null>");

  static Ty_tyList arrayPath;
  static Ty_tyList recordPath;

  switch (ty->type)
  {
  case Ty_int:
    return fprintf(file, "int");
  case Ty_void:
    return fprintf(file, "void");
  case Ty_string:
    return fprintf(file, "string");
  case Ty_nil:
    return fprintf(file, "nil");
  case Ty_named:
    return fprintf(file, "%s", ty->named.sym->name);
  case Ty_array:
  {
    int n1 = fprintf(file, "[");
    int n2 = fprintTy(file, ty->array);
    int n3 = fprintf(file, "]");
    return n1 + n2 + n3;
  }
  case Ty_record:
  {
    int n = 0;
    n += fprintf(file, "{ ");

    Ty_fieldList fields = ty->record;
    Ty_field field;

    while (fields && fields->head)
    {
      field = fields->head;
      n += fprintf(file, "%s: ", field->name->name);
      n += fprintTy(file, field->ty);

      if (fields->tail)
        n += fprintf(file, ", ");

      fields = fields->tail;
    }

    n += fprintf(file, " }");
    return n;
  }
  }
}
