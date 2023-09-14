#include <assert.h>
#include "translate.h"
#include "temp.h"
#include "print_tree.h"
#include "frame.h"

struct Tr_access_
{
  Tr_level level;
  F_access access;
};

struct Tr_accessList_
{
  Tr_access head;
  Tr_accessList tail;
};

struct Tr_level_
{
  Tr_level parent;
  F_frame frame;
};

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

    T_stm seq = T_vSeq(
        T_Move(T_Temp(r), T_Const(1)),
        e->cx.stm,
        T_Label(f),
        T_Move(T_Temp(r), T_Const(0)),
        T_Label(t),
        NULL);

    return T_Eseq(seq, T_Temp(r));
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

Tr_expseq Tr_ExpSeq(Tr_exp head, Tr_expseq tail)
{
  if (head)
  {
    Tr_expseq p = _malloc(sizeof(*p));
    p->head = head;
    p->tail = tail;
    return p;
  }
  else
    return tail;
}

Tr_expseq Tr_ExpSeqReversed(Tr_expseq seq)
{
  Tr_expseq r = NULL;

  for (; seq && seq->head; seq = seq->tail)
    r = Tr_ExpSeq(seq->head, r);

  return r;
}

int Tr_ExpSeqLength(Tr_expseq seq)
{
  int length = 0;
  for (; seq; seq = seq->tail)
    length += 1;
  return length;
}

static F_fragList frag_list = NULL;
F_fragList Tr_getResult()
{
  return frag_list;
}

void Tr_procEntryExit(Tr_level level, Tr_exp body, Tr_accessList accessList)
{
  T_stm stm = T_Move(T_Temp(F_RV()), unEx(body));
  stm = F_procEntryExit1(level->frame, stm);
  frag_list = F_FragList(F_ProcFrag(stm, level->frame), frag_list);
}

static patchList PatchList(Temp_label *head, patchList tail)
{
  patchList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

void Tr_printTree(Tr_exp exp)
{
  printStmList(T_StmList(unNx(exp), NULL), 0);
}

Tr_exp Tr_intExp(int value)
{
  return Tr_Ex(T_Const(value));
}

Tr_exp Tr_stringExp(string str)
{
  Temp_label label = Temp_newLabel();
  frag_list = F_FragList(F_StringFrag(label, str), frag_list);
  return Tr_Ex(T_Name(label));
}

Tr_exp Tr_nilExp()
{
  return Tr_Ex(T_Const(0));
}

Tr_exp Tr_assignExp(Tr_exp dest, Tr_exp source)
{
  return Tr_Nx(T_Move(unEx(dest), unEx(source)));
}

Tr_exp Tr_seqExp(Tr_expseq seq)
{
  seq = Tr_ExpSeqReversed(seq);
  T_exp exp = NULL;
  for (; seq && seq->head; seq = seq->tail)
    exp = exp ? T_Eseq(unNx(seq->head), exp) : unEx(seq->head);
  return Tr_Ex(exp);
}

Tr_exp Tr_arithExp(A_oper op, Tr_exp left, Tr_exp right)
{
  T_binOp binOp;

  switch (op)
  {
  case A_plusOp:
    binOp = T_plus;
    break;
  case A_minusOp:
    binOp = T_minus;
    break;
  case A_timesOp:
    binOp = T_mul;
    break;
  case A_divideOp:
    binOp = T_div;
    break;
  default:
    fatalError("unknown arith op");
  }

  return Tr_Ex(T_Binop(binOp, unEx(left), unEx(right)));
}

Tr_exp Tr_logicExp(A_oper op, Tr_exp left, Tr_exp right)
{
  T_relOp relOp;
  switch (op)
  {
  case A_eqOp:
    relOp = T_eq;
    break;
  case A_neqOp:
    relOp = T_ne;
    break;
  case A_gtOp:
    relOp = T_gt;
    break;
  case A_ltOp:
    relOp = T_lt;
    break;
  case A_geOp:
    relOp = T_ge;
    break;
  case A_leOp:
    relOp = T_le;
    break;
  default:
    fatalError("unknown logic op");
  }

  T_stm cjump = T_Cjump(relOp, unEx(left), unEx(right), NULL, NULL);
  patchList trues = PatchList(&cjump->CJUMP.trueLabel, NULL);
  patchList falses = PatchList(&cjump->CJUMP.falseLabel, NULL);
  return Tr_Cx(trues, falses, cjump);
}

Tr_exp Tr_strcmpExp(A_oper op, Tr_exp left, Tr_exp right)
{
  T_relOp relOp;
  switch (op)
  {
  case A_eqOp:
    relOp = T_eq;
    break;
  case A_neqOp:
    relOp = T_ne;
    break;
  case A_ltOp:
    relOp = T_lt;
    break;
  case A_gtOp:
    relOp = T_gt;
    break;
  case A_leOp:
    relOp = T_le;
    break;
  case A_geOp:
    relOp = T_ge;
    break;
  default:
    fatalError("unknown logic op");
  }

  T_exp t = F_externalCall("stringEqual", T_ExpList(unEx(left), T_ExpList(unEx(right), NULL)));
  T_stm cjump = T_Cjump(relOp, t, T_Const(0), NULL, NULL);
  patchList trues = PatchList(&cjump->CJUMP.trueLabel, NULL);
  patchList falses = PatchList(&cjump->CJUMP.falseLabel, NULL);
  return Tr_Cx(trues, falses, cjump);
}

Tr_exp Tr_breakExp(Temp_label brk)
{
  return Tr_Nx(T_Jump(T_Name(brk), Temp_LabelList(brk, NULL)));
}

Tr_exp Tr_whileExp(Tr_exp cond, Tr_exp body, Temp_label brk)
{
  Temp_label l = Temp_newLabel();
  Temp_label t = Temp_newLabel();

  return Tr_Nx(
      T_vSeq(
          T_Label(l),
          T_Cjump(T_ne, unEx(cond), T_Const(0), t, brk),
          T_Label(t),
          unNx(body),
          T_Label(brk),
          NULL));
}

Tr_exp Tr_forExp(Tr_exp var, Tr_exp low, Tr_exp high, Tr_exp body, Temp_label brk)
{
  Temp_label l = Temp_newLabel();
  Temp_label t = Temp_newLabel();

  return Tr_Nx(
      T_vSeq(
          T_Move(unEx(var), unEx(low)),
          T_Label(l),
          T_Cjump(T_le, unEx(var), unEx(high), t, brk),
          T_Label(t),
          unNx(body),
          T_Label(brk),
          NULL));
}

Tr_exp Tr_ifExp(Tr_exp cond, Tr_exp then, Tr_exp els)
{
  Temp_label t = Temp_newLabel();
  Temp_label f = Temp_newLabel();

  if (cond->kind == Tr_ex)
  {
    struct Cx cx = unCx(cond);
    cond = Tr_Cx(cx.trues, cx.falses, cx.stm);
  }

  assert(cond->kind == Tr_cx);

  doPatch(cond->cx.trues, t);
  doPatch(cond->cx.falses, f);

  if (els)
  {
    Temp_temp r = Temp_newtemp();
    Temp_label end = Temp_newLabel();

    T_stm seq = T_vSeq(
        unCx(cond).stm,
        T_Label(t),
        T_Move(T_Temp(r), unEx(then)),
        T_Jump(T_Name(end), Temp_LabelList(end, NULL)),
        T_Label(f),
        T_Move(T_Temp(r), unEx(els)),
        T_Label(end),
        NULL);

    return Tr_Ex(T_Eseq(seq, T_Temp(r)));
  }
  else
  {
    T_stm seq = T_vSeq(
        unCx(cond).stm,
        T_Label(t),
        T_Jump(T_Name(f), Temp_LabelList(f, NULL)),
        unNx(then),
        T_Label(f),
        NULL);

    return Tr_Nx(seq);
  }
}

Tr_exp Tr_arrayExp(Tr_exp elem, Tr_exp capacity)
{
  return Tr_Ex(F_externalCall("initArray", T_ExpList(unEx(elem), T_ExpList(unEx(capacity), NULL))));
}

Tr_exp Tr_recordExp(Tr_expseq fields)
{
  fields = Tr_ExpSeqReversed(fields);
  int size = Tr_ExpSeqLength(fields);
  Temp_temp r = Temp_newtemp();
  T_exp p = F_externalCall("allocRecord", T_ExpList(T_Const(size * F_wordSize), NULL));
  T_stm alloc = T_Move(T_Temp(r), p);
  T_stm init = NULL;

  for (int i = 0; i < size; ++i)
  {
    init = T_Seq(T_Move(T_Mem(T_Binop(T_plus, T_Temp(r), T_Const(F_wordSize * (size - 1 - i)))), unEx(fields->head)), init);
    fields = fields->tail;
  }

  return Tr_Ex(T_Eseq(T_Seq(alloc, init), T_Temp(r)));
}

Tr_exp Tr_simpleVar(Tr_access access, Tr_level level)
{
  T_exp exp = T_Temp(F_FP());
  for (; access->level != level; level = level->parent)
    exp = F_Exp(F_staticLink(), T_Temp(F_FP()));
  return Tr_Ex(F_Exp(access->access, exp));
}

Tr_exp Tr_arrayVar(Tr_exp array, Tr_exp index)
{
  return Tr_Ex(T_Mem(T_Binop(T_plus, unEx(array), T_Binop(T_mul, unEx(index), T_Const(F_wordSize)))));
}

Tr_exp Tr_fieldVar(Tr_exp record, int offset)
{
  if (offset)
  {
    return Tr_Ex(T_Mem(T_Binop(T_plus, unEx(record), T_Const(offset * F_wordSize))));
  }
  else
    return record;
}

Tr_exp Tr_callExp(Tr_level caller, Tr_level callee, Temp_label label, Tr_expseq argv)
{
  T_expList exps = NULL;
  argv = Tr_ExpSeqReversed(argv);

  for (; argv && argv->head; argv = argv->tail)
    exps = T_ExpList(unEx(argv->head), exps);

  return Tr_Ex(T_Call(T_Name(label), exps));
}

static Tr_level outermost_level = NULL;
Tr_level Tr_outermost()
{
  if (!outermost_level)
    outermost_level = Tr_newLevel(NULL, Temp_namedLabel("_main"), NULL);
  return outermost_level;
}

Tr_level Tr_newLevel(Tr_level parent, Temp_label name, U_boolList formals)
{
  Tr_level lv = _malloc(sizeof(*lv));
  lv->parent = parent;
  lv->frame = F_newFrame(name, formals);
  return lv;
}

Tr_access Tr_accessListHead(Tr_accessList list)
{
  return list->head;
}

Tr_accessList Tr_accessListTail(Tr_accessList list)
{
  return list->tail;
}

static Tr_accessList Tr_AccessList(Tr_access head, Tr_accessList tail)
{
  Tr_accessList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

static Tr_access Tr_Access(Tr_level level, F_access access)
{
  Tr_access p = _malloc(sizeof(*p));
  p->level = level;
  p->access = access;
  return p;
}

Tr_accessList Tr_accessListReversed(Tr_accessList list)
{
  Tr_accessList r = NULL;
  for (; list && list->head; list = list->tail)
    r = Tr_AccessList(list->head, r);
  return r;
}

Tr_accessList Tr_formals(Tr_level level)
{
  F_accessList f_formals = F_formals(level->frame);
  Tr_accessList r = NULL;
  for (; f_formals && f_formals->head; f_formals = f_formals->tail)
    r = Tr_AccessList(Tr_Access(level, f_formals->head), r);
  return Tr_accessListReversed(r);
}

Tr_access Tr_allocLocal(Tr_level level, bool escape)
{
  return Tr_Access(level, F_allocLocal(level->frame, escape));
}
