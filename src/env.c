#include <stdarg.h>
#include "env.h"
#include "utils.h"

E_enventry E_VarEntry(Tr_access access, Ty_ty ty)
{
  E_enventry e = _malloc(sizeof(*e));
  e->type = E_varEntry;
  e->var.access = access;
  e->var.ty = ty;
  return e;
}

E_enventry E_FunEntry(Tr_level level, Temp_label label, Ty_tyList formals, Ty_ty result)
{
  E_enventry e = _malloc(sizeof(*e));
  e->type = E_funEntry;
  e->fun.level = level;
  e->fun.label = label;
  e->fun.formals = formals;
  e->fun.result = result;
  return e;
}

S_table E_base_tenv()
{
  S_table table = S_empty();
  S_insert(table, S_Symbol("int"), Ty_Int());
  S_insert(table, S_Symbol("string"), Ty_String());
  S_insert(table, S_Symbol("void"), Ty_Void());
  S_insert(table, S_Symbol("nil"), Ty_Nil());
  return table;
}

static E_enventry makeFuncEntry(string name, Ty_ty result, ...)
{
  va_list args;
  va_start(args, result);

  Ty_tyList formals = NULL;
  while (1)
  {
    Ty_ty param = va_arg(args, Ty_ty);

    if (param)
      formals = Ty_TyList(param, formals);
    else
      break;
  }

  va_end(args);

  return E_FunEntry(Tr_outermost(), Temp_namedLabel(name), Ty_TyListReversed(formals), result);
}

S_table E_base_venv()
{
  S_table table = S_empty();
  S_insert(table, S_Symbol("print"), makeFuncEntry("print", Ty_Void(), Ty_String(), 0));
  S_insert(table, S_Symbol("flush"), makeFuncEntry("flush", Ty_Void(), 0));
  S_insert(table, S_Symbol("getchar"), makeFuncEntry("getchar", Ty_String(), 0));
  S_insert(table, S_Symbol("ord"), makeFuncEntry("ord", Ty_Int(), Ty_String(), 0));
  S_insert(table, S_Symbol("chr"), makeFuncEntry("chr", Ty_String(), Ty_Int(), 0));
  S_insert(table, S_Symbol("size"), makeFuncEntry("size", Ty_Int(), Ty_String(), 0));
  S_insert(table, S_Symbol("substring"), makeFuncEntry("substring", Ty_String(), Ty_String(), Ty_Int(), Ty_Int(), 0));
  S_insert(table, S_Symbol("concat"), makeFuncEntry("concat", Ty_String(), Ty_String(), Ty_String(), 0));
  S_insert(table, S_Symbol("not"), makeFuncEntry("not", Ty_Int(), Ty_Int(), 0));
  S_insert(table, S_Symbol("exit"), makeFuncEntry("exit", Ty_Void(), Ty_Int(), 0));
  return table;
}
