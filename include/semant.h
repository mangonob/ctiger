#ifndef SEMANT_H_
#define SEMANT_H_

#include "types.h"
#include "absyn.h"

typedef void *Tr_exp;

struct expty
{
  Tr_exp exp;
  Ty_ty ty;
};

typedef struct expty expty;

expty expTy(Tr_exp exp, Ty_ty ty);

expty transVar(S_table venv, S_table tenv, A_var var);

expty transExp(S_table venv, S_table tenv, A_exp exp);

void transDec(S_table venv, S_table tenv, A_dec dec);

Ty_ty transTy(S_table tenv, A_ty ty);

#endif