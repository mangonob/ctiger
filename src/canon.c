#include <assert.h>
#include <stdbool.h>
#include "canon.h"
#include "utils.h"
#include "symbol.h"

typedef struct expRefList_ *expRefList;
struct expRefList_
{
  T_exp *head;
  expRefList tail;
};

typedef struct
{
  T_stm stm;
  T_exp exp;
} stmExp;

stmExp StmExp(T_stm stm, T_exp exp)
{
  stmExp x;
  x.stm = stm;
  x.exp = exp;
  return x;
}

expRefList ExpRefList(T_exp *head, expRefList tail)
{
  expRefList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

expRefList ExpRefListReversed(expRefList list)
{
  expRefList r = NULL;
  for (; list; list = list->tail)
    r = ExpRefList(list->head, r);
  return r;
}

static expRefList getCallRefList(T_exp exp)
{
  assert(exp->kind == T_CALL);

  T_expList exps = exp->CALL.args;
  expRefList refs = ExpRefList(&exp->CALL.fun, NULL);
  for (; exps; exps = exps->tail)
    refs = ExpRefList(&exps->head, refs);
  return ExpRefListReversed(refs);
}

static T_stm reorder(expRefList rlist);

static bool isNop(T_stm stm)
{
  return stm->kind == T_EXP && stm->EXP->kind == T_CONST;
}

static bool commute(T_stm stm, T_exp exp)
{
  return isNop(stm) || (exp->kind == T_NAME || exp->kind == T_CONST);
}

static T_stm seq(T_stm left, T_stm right)
{
  if (isNop(left))
    return right;
  else if (isNop(right))
    return left;
  else
    return T_Seq(left, right);
}

static T_stm do_stm(T_stm stm)
{
  switch (stm->kind)
  {
  case T_SEQ:
    if (!stm->SEQ.left)
      return do_stm(stm->SEQ.right);
    else if (!stm->SEQ.right)
      return do_stm(stm->SEQ.left);
    else
      return seq(do_stm(stm->SEQ.left),
                 do_stm(stm->SEQ.right));
  case T_JUMP:
    return seq(reorder(ExpRefList(&stm->JUMP.exp, NULL)), stm);
  case T_CJUMP:
    return seq(reorder(ExpRefList(&stm->CJUMP.lhs, ExpRefList(&stm->CJUMP.rhs, NULL))), stm);
  case T_MOVE:
    if (stm->MOVE.dst->kind == T_TEMP && stm->MOVE.src->kind == T_CALL)
      return seq(reorder(getCallRefList(stm->MOVE.src)), stm);
    else if (stm->MOVE.dst->kind == T_TEMP)
      return seq(reorder(ExpRefList(&stm->MOVE.src, NULL)), stm);
    else if (stm->MOVE.dst->kind == T_MEM)
      return seq(reorder(ExpRefList(&stm->MOVE.dst, ExpRefList(&stm->MOVE.src, NULL))), stm);
    else if (stm->MOVE.dst->kind == T_ESEQ)
    {
      T_stm s = stm->MOVE.dst->ESEQ.stm;
      stm->MOVE.dst = stm->MOVE.dst->ESEQ.exp;
      return do_stm(T_Seq(s, stm));
    }
    else
      assert(false);
  case T_EXP:
    if (stm->EXP->kind == T_CALL)
      return seq(reorder(getCallRefList(stm->EXP)), stm);
    else
      return seq(reorder(ExpRefList(&stm->EXP, NULL)), stm);
  default:
    return stm;
  }
}

static stmExp do_exp(T_exp exp)
{
  switch (exp->kind)
  {
  case T_BINOP:
    return StmExp(
        reorder(ExpRefList(&exp->BINOP.left, ExpRefList(&exp->BINOP.right, NULL))),
        exp);
  case T_MEM:
    return StmExp(
        reorder(ExpRefList(&exp->MEM, NULL)),
        exp);
  case T_ESEQ:
  {
    stmExp x = do_exp(exp->ESEQ.exp);
    return StmExp(seq(do_stm(exp->ESEQ.stm), x.stm), x.exp);
  }
  case T_CALL:
    return StmExp(reorder(getCallRefList(exp)), exp);
  default:
    return StmExp(reorder(0), exp);
  }
}

static T_stm reorder(expRefList rlist)
{
  if (!rlist)
    return T_Exp(T_Const(0));
  else if ((*rlist->head)->kind == T_CALL)
  {
    Temp_temp t = Temp_newtemp();
    *rlist->head = T_Eseq(T_Move(T_Temp(t), *rlist->head), T_Temp(t));
    return reorder(rlist);
  }
  else
  {
    stmExp se = do_exp(*rlist->head);
    T_stm s = reorder(rlist->tail);

    if (commute(s, se.exp))
    {
      *rlist->head = se.exp;
      return seq(se.stm, s);
    }
    else
    {
      Temp_temp t = Temp_newtemp();
      *rlist->head = T_Temp(t);
      return seq(se.stm, seq(T_Move(T_Temp(t), se.exp), s));
    }
  }
}

static T_stmList linear(T_stm stm, T_stmList right)
{
  if (stm->kind == T_SEQ)
    return linear(stm->SEQ.left, linear(stm->SEQ.right, right));
  else
    return T_StmList(stm, right);
}

T_stmList C_linearize(T_stm stm)
{
  return linear(do_stm(stm), NULL);
}

static C_stmListList StmListList(T_stmList head, C_stmListList tail)
{
  C_stmListList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

static C_stmListList mkBlocks(T_stmList stmList, Temp_label done);
static C_stmListList next(T_stmList prev, T_stmList stms, Temp_label done)
{
  if (!stms)
    return next(prev, T_StmList(T_Jump(T_Name(done), Temp_LabelList(done, NULL)), NULL), done);
  else if (stms->head->kind == T_JUMP || stms->head->kind == T_CJUMP)
  {
    C_stmListList head;
    prev->tail = stms;
    head = mkBlocks(stms->tail, done);
    stms->tail = NULL;
    return head;
  }
  else if (stms->head->kind == T_LABEL)
  {
    Temp_label l = stms->head->LABEL;
    return next(prev, T_StmList(T_Jump(T_Name(l), Temp_LabelList(l, NULL)), stms), done);
  }
  else
  {
    prev->tail = stms;
    return next(stms, stms->tail, done);
  }
}

static C_stmListList mkBlocks(T_stmList stmList, Temp_label done)
{
  if (!stmList)
    return NULL;

  if (stmList->head->kind != T_LABEL)
    return mkBlocks(T_StmList(T_Label(Temp_newLabel()), stmList), done);

  return StmListList(stmList, next(stmList, stmList->tail, done));
}

C_block C_basicBlocks(T_stmList stmList)
{
  C_block b;
  Temp_label done = Temp_newLabel();
  b.label = done;
  b.stmLists = mkBlocks(stmList, done);
  return b;
}

static T_stmList getLast2(T_stmList list)
{
  while (list->tail->tail)
    list = list->tail;
  return list;
}

/** unmarked basic block */
static S_table block_table;
static C_block global_block;

static T_stmList getNext();

static void trace(T_stmList list)
{
  T_stm lab = list->head;
  // mark current basic block
  S_insert(block_table, lab->LABEL, NULL);
  T_stmList last2 = getLast2(list);
  T_stm j = last2->tail->head;

  if (j->kind == T_JUMP)
  {
    T_stmList target = S_lookup(block_table, j->JUMP.jumps->head);

    if (!j->JUMP.jumps->tail && target)
    {
      last2->tail = target;
      trace(target);
    }
    else
      last2->tail->tail = getNext();
  }
  else if (j->kind == T_CJUMP)
  {
    T_stmList t = S_lookup(block_table, j->CJUMP.trueLabel);
    T_stmList f = S_lookup(block_table, j->CJUMP.falseLabel);

    if (f)
    {
      last2->tail->tail = f;
      trace(f);
    }
    else if (t)
    {
      last2->tail->head = T_Cjump(T_notRel(j->CJUMP.op), j->CJUMP.lhs, j->CJUMP.rhs, j->CJUMP.falseLabel, j->CJUMP.trueLabel);
      last2->tail->tail = t;
      trace(t);
    }
    else
    {
      Temp_label f = Temp_newLabel();
      j->CJUMP.falseLabel = f;
      last2->tail->tail = T_StmList(T_Label(f), getNext());
    }
  }
  else
    assert(0);
}

static T_stmList getNext()
{
  if (!global_block.stmLists)
    return T_StmList(T_Label(global_block.label), NULL);
  else
  {
    T_stmList s = global_block.stmLists->head;
    if (S_lookup(block_table, s->head->LABEL))
    {
      trace(s);
      return s;
    }
    else
    {
      global_block.stmLists = global_block.stmLists->tail;
      return getNext();
    }
  }
}

T_stmList C_traceSchedule(C_block b)
{
  block_table = S_empty();
  global_block = b;
  for (C_stmListList stmLists = b.stmLists; stmLists; stmLists = stmLists->tail)
    S_insert(block_table, stmLists->head->head->LABEL, stmLists->head);
  return getNext();
}
