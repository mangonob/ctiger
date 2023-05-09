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
    doPatch(e->cx.trues, t);
    doPatch(e->cx.falses, f);

    // return T_Eseq(T_Move(T_Temp(r), T_Const(1)),
    //               T_Eseq(e->cx.stm,
    //                      T_Eseq(T_Label(f),
    //                             T_Eseq(T_Move(T_Temp(r), T_Const(0)),
    //                                    T_Eseq(T_Label(t), T_Temp(r))))));

    return vT_Eseq(
        T_Move(T_Temp(r), T_Const(1)),
        e->cx.stm,
        T_Label(f),
        T_Move(T_Temp(r), T_Const(0)),
        T_Label(t),
        T_Temp(r),
        0);
  }
  case Tr_nx:
    return T_Eseq(e->nx, T_Const(0));
  }
}

static T_stm unNx(Tr_exp e)
{
  switch (e->kind)
  {
  case Tr_ex:
    return T_Exp(e->ex);
  case Tr_cx:
  {
    Temp_label t = Temp_newLabel();
    Temp_label f = Temp_newLabel();
    doPatch(e->cx.trues, t);
    doPatch(e->cx.falses, f);
    return T_Seq(e->cx.stm, T_Seq(T_Label(t), T_Label(f)));
  }
  case Tr_nx:
    return e->nx;
  }
}

static struct Cx unCx(Tr_exp e)
{
  switch (e->kind)
  {
  case Tr_ex:
  {
    struct Cx cx;
    cx.stm = T_Cjump(T_ne, e->ex, T_Const(0), NULL, NULL);
    cx.trues = PatchList(&cx.stm->CJUMP.trueLabel, NULL);
    cx.falses = PatchList(&cx.stm->CJUMP.falseLabel, NULL);
    return cx;
  }
  case Tr_cx:
    return e->cx;
  case Tr_nx:
  {
    struct Cx cx;
    cx.stm = e->nx;
    cx.trues = NULL;
    cx.falses = NULL;
    return cx;
  }
  }
}

static patchList PatchList(Temp_label *head, patchList tail)
{
  patchList p = _malloc(sizeof(p));
  p->head = head;
  p->tail = tail;
  return p;
}