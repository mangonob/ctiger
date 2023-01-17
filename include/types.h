#ifndef TYPES_HEADER
#define TYPES_HEADER
#include <stdio.h>
#include "symbol.h"

typedef struct Ty_ty_ *Ty_ty;
typedef struct Ty_tyList_ *Ty_tyList;
typedef struct Ty_field_ *Ty_field;
typedef struct Ty_fieldList_ *Ty_fieldList;

struct Ty_ty_
{
  enum
  {
    Ty_record,
    Ty_nil,
    Ty_int,
    Ty_string,
    Ty_array,
    Ty_named,
    Ty_void,
  } type;

  union
  {
    Ty_fieldList record;
    Ty_ty array;
    struct
    {
      S_symbol sym;
      Ty_ty ty;
    } named;
  };
};

struct Ty_tyList_
{
  Ty_ty head;
  Ty_tyList tail;
};

struct Ty_field_
{
  S_symbol name;
  Ty_ty ty;
};

struct Ty_fieldList_
{
  Ty_field head;
  Ty_fieldList tail;
};

Ty_ty Ty_Nil();
Ty_ty Ty_Int();
Ty_ty Ty_String();
Ty_ty Ty_Void(void);

Ty_ty Ty_Array(Ty_ty ty);
Ty_ty Ty_Named(S_symbol sym, Ty_ty ty);
Ty_ty Ty_Record(Ty_fieldList fields);

Ty_tyList Ty_TyList(Ty_ty head, Ty_tyList tail);
Ty_tyList Ty_TyListReverse(Ty_tyList tys);
Ty_field Ty_Field(S_symbol name, Ty_ty ty);
Ty_fieldList Ty_FieldList(Ty_field head, Ty_fieldList tail);
Ty_fieldList Ty_FieldListReverse(Ty_fieldList fields);

int fprintTy(FILE *file, Ty_ty ty);

#endif