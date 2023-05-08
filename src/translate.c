#include "translate.h"
#include "utils.h"
#include "temp.h"

static Tr_exp Tr_Ex(T_exp ex)
{
  Tr_exp p = _malloc(sizeof(*p));
  p->kind = Tr_ex;
  p->ex = ex;
  return p;
}

static Tr_exp Tr_Nx(T_stm nx)
{
  Tr_exp p = _malloc(sizeof(*p));
  p->kind = Tr_nx;
  p->nx = nx;
  return p;
}

static Tr_exp Tr_Cx(patchList trues, patchList falses, T_stm stm)
{
  Tr_exp p = _malloc(sizeof(*p));
  p->kind = Tr_cx;
  p->cx.trues = trues;
  p->cx.falses = falses;
  p->cx.stm = stm;
  return p;
}

static void doPatch(patchList list, Temp_label label)
{
  for (; list; list = list->tail)
    if (list->head)
      *(list->head) = label;
}

static T_exp unEx(Tr_exp e)
{
  switch (e->kind)
  {
  case Tr_ex:
    return e->ex;
  case Tr_cx:
  {
    Temp_temp r = Temp_newtemp();
    Temp_label t = Temp_newLabel();
    Temp_label f = Temp_newLabel();
    struct Cx cx = e->cx;
    doPatch(cx.trues, t);
    doPatch(cx.falses, f);
    return T_Eseq(T_Move(T_Temp(r), T_Const(1)),
                  T_Eseq(cx.stm,
                         T_Eseq(T_Label(f),
                                T_Eseq(T_Move(T_Temp(r), T_Const(0)),
                                       T_Eseq(T_Label(t), T_Temp(r))))));
  }
  case Tr_nx:
    return T_Eseq(e->nx, T_Const(0));
  }
}

static T_stm unNx(Tr_exp e)
{
  // TODO
  notImplementation();
}

static struct Cx unCx(Tr_exp e)
{
  // TODO
  notImplementation();
}