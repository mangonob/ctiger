#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "regalloc.h"
#include "liveness.h"
#include "flowgraph.h"
#include "color.h"
#include "temp.h"
#define L(...) mkTempList(__VA_ARGS__, NULL)

// #define SKIP_REDUCE

static SET_set tempList2Set(Temp_tempList tl)
{
  SET_set s = SET_empty();
  for (; tl; tl = tl->tail)
    SET_enter(s, tl->head);
  return s;
}

static Temp_tempList getSrc(AS_instr instr)
{
  switch (instr->kind)
  {
  case I_CALL:
    return getSrc(instr->CALL.oper);
  case I_OPER:
    return instr->OPER.src;
  case I_MOVE:
    return instr->MOVE.src;
  default:
    break;
  }

  return NULL;
}

static Temp_tempList getDst(AS_instr instr)
{
  switch (instr->kind)
  {
  case I_CALL:
    return getDst(instr->CALL.oper);
  case I_OPER:
    return instr->OPER.dst;
  case I_MOVE:
    return instr->MOVE.dst;
  default:
    break;
  }

  return NULL;
}

static AS_instrList instrListLast(AS_instrList l)
{
  for (; l && l->tail;)
    l = l->tail;
  return l;
}

static AS_instrList rewriteInstr(AS_instrList il, AS_instr instr, Temp_temp spill, F_access acc)
{
  AS_instrList last = instrListLast(il);

  bool used = false;
  bool defined = false;
  Temp_temp t = Temp_newtemp();
  int offset = F_accessOffset(acc);

  for (Temp_tempList src = getSrc(instr); src; src = src->tail)
    if (src->head == spill)
    {
      src->head = t;
      used = true;
    }

  for (Temp_tempList dst = getDst(instr); dst; dst = dst->tail)
    if (dst->head == spill)
    {
      dst->head = t;
      defined = true;
    }

  if (used)
  {
    AS_instr r = AS_Oper(Format("ldur `d0, [`s0, #%d]\t\t\t;%d bytes folded reload", offset, F_wordSize), L(t), L(F_FP()), NULL);
    il = AS_InstrList(r, il);
  }

  if (defined)
  {
    AS_instr w = AS_Oper(Format("stur `s0, [`s1, #%d]\t\t\t;%d bytes folded spill", offset, F_wordSize), NULL, L(t, F_FP()), NULL);
    last = last->tail = AS_InstrList(w, NULL);
  }

  return il;
}

static bool used(AS_instr instr, Temp_temp t)
{
  assert(instr && t);

  for (Temp_tempList tl = getSrc(instr); tl; tl = tl->tail)
    if (tl->head == t)
      return true;
  return false;
}

static bool defined(AS_instr instr, Temp_temp t)
{
  assert(instr && t);

  for (Temp_tempList tl = getDst(instr); tl; tl = tl->tail)
    if (tl->head == t)
      return true;
  return false;
}

static AS_instrList rewriteProgram(F_frame f, AS_instrList il, Temp_tempList spills)
{
  TAB_table accs = TAB_empty();
  for (Temp_tempList tl = spills; tl; tl = tl->tail)
    TAB_push(accs, tl->head, F_allocLocal(f, true));

  AS_instrList rl = NULL;
  AS_instrList last = NULL;
  for (; il; il = il->tail)
  {
    AS_instr instr = il->head;
    AS_instrList n = AS_InstrList(instr, NULL);

    for (Temp_tempList tl = spills; tl; tl = tl->tail)
    {
      Temp_temp spill = tl->head;
      if (used(instr, spill) || defined(instr, spill))
      {
        F_access acc = TAB_lookup(accs, spill);
        n = rewriteInstr(n, instr, spill, acc);
      }
    }

    if (!n)
      n = AS_InstrList(instr, NULL);

    if (rl)
    {
      last->tail = n;
    }
    else
      rl = n;

    last = instrListLast(n);
  }

  return rl;
}

static bool isSynonymMove(AS_instr i, Temp_map color)
{
  if (i->kind == I_MOVE)
  {
    assert(!i->MOVE.src->tail);
    assert(!i->MOVE.dst->tail);
    string src_color = Temp_look(color, i->MOVE.src->head);
    string dst_color = Temp_look(color, i->MOVE.dst->head);
    return !!src_color && src_color == dst_color;
  }
  else
  {
    return false;
  }
}

/**
 * Remove move instructions between source register and destination register
 */
static AS_instrList reduceMoves(AS_instrList iList, Temp_map color)
{
  AS_instrList rl = NULL;
  AS_instrList last = NULL;
  for (AS_instrList il = iList; il; il = il->tail)
  {
    AS_instrList l = AS_InstrList(il->head, NULL);
    if (isSynonymMove(il->head, color))
    {
      continue;
    }
    else
    {
      if (rl)
        last = last->tail = l;
      else
        rl = last = l;
    }
  }

  return rl;
}

static Temp_labelList instrJumps(AS_instr i)
{
  switch (i->kind)
  {
  case I_OPER:
    return i->OPER.jumps ? i->OPER.jumps->labels : NULL;
  case I_MOVE:
  case I_CALL:
  case I_LABEL:
    return NULL;
  }
}

/**
 * Remove useless label and "nop" instructions
 */
static AS_instrList reduceLabel(AS_instrList iList)
{
  TAB_table jumps = TAB_empty();
  for (AS_instrList il = iList; il; il = il->tail)
    for (Temp_labelList ll = instrJumps(il->head); ll; ll = ll->tail)
      TAB_push(jumps, ll->head, SET_union(TAB_lookup(jumps, ll->head), SET_singleton(il->head)));

  AS_instrList rl = NULL;
  AS_instrList last = NULL;

  for (; iList; iList = iList->tail)
  {
    AS_instr i = iList->head;
    AS_instrList n = AS_InstrList(i, NULL);

    if (i->kind == I_OPER && strcmp(i->OPER.assem, "nop") == 0)
      continue;

    if (rl)
      last = last->tail = n;
    else
      rl = last = n;
  }

  return rl;
}

static COL_result colorInstrList(F_frame frame, AS_instrList il)
{
  G_graph flow = FG_AssemFlowGraph(il);
  Live_graph live = Live_liveness(flow);
  return COL_color(live.graph, F_initialRegisters(frame), live.moves, live.nodeMoves, live.spillCosts, F_registers());
}

RA_result RA_regAlloc(F_frame frame, AS_instrList il)
{
  COL_result col_result;
  for (int try = 7; try; try--)
  {
    col_result = colorInstrList(frame, il);

    if (col_result.spills)
    {
      il = rewriteProgram(frame, il, col_result.spills);
    }
    else
    {
      il = reduceMoves(il, col_result.coloring);
      il = reduceLabel(il);
      break;
    }
  }

  if (col_result.spills)
  {
    fprintf(stderr, "registers alloc failure.\n");
    exit(1);
  }

  RA_result r;
  r.il = il;
  r.coloring = col_result.coloring;
  return r;
}
