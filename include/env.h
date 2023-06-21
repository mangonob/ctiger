#ifndef ENV_H_
#define ENV_H_
#include "types.h"
#include "translate.h"
#include "temp.h"

typedef struct E_enventry_ *E_enventry;

struct E_enventry_
{
  enum
  {
    E_varEntry,
    E_funEntry
  } type;

  union
  {
    struct
    {
      Tr_access access;
      Ty_ty ty;
    } var;
    struct
    {
      Tr_level level;
      Temp_label label;
      Ty_tyList formals;
      Ty_ty result;
    } fun;
  };
};

E_enventry E_VarEntry(Tr_access access, Ty_ty ty);
E_enventry E_FunEntry(Tr_level level, Temp_label label, Ty_tyList formals, Ty_ty result);

/* Ty_ty environment */
S_table E_base_tenv();
/* E_enventry environment */
S_table E_base_venv();

#endif
