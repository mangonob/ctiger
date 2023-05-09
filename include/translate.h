#ifndef TRANSLATE_H_
#define TRANSLATE_H_

#include "tree.h"

typedef struct patchList_ *patchList;
typedef struct Tr_exp_ *Tr_exp;

struct Cx
{
  patchList trues;
  patchList falses;
  T_stm stm;
};

struct Tr_exp_
{
  enum
  {
    Tr_ex,
    Tr_nx,
    Tr_cx
  } kind;

  union
  {
    T_exp ex;
    T_stm nx;
    struct Cx cx;
  };
};

struct patchList_
{
  Temp_label *head;
  patchList tail;
};

static patchList PatchList(Temp_label *head, patchList tail);

static Tr_exp Tr_Ex(T_exp ex);
static Tr_exp Tr_Nx(T_stm nx);
static Tr_exp Tr_Cx(patchList trues, patchList falses, T_stm stm);

static T_exp unEx(Tr_exp e);
static T_stm unNx(Tr_exp e);
static struct Cx unCx(Tr_exp e);

#endif