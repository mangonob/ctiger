#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "regalloc.h"
#include "liveness.h"
#include "flowgraph.h"
#include "color.h"

// #define SKIP_REDUCE

static SET_set tempList2Set(Temp_tempList tl)
{
  SET_set s = SET_empty();
  for (; tl; tl = tl->tail)
    SET_enter(s, tl->head);
  return s;
}

static AS_instrList rewriteProgram(AS_instrList il, Temp_tempList spills)
{
  SET_set s = tempList2Set(spills);
  AS_instrList rl = NULL;
  AS_instrList last = NULL;
  for (; il; il = il->tail)
  {
    AS_instr instr = il->head;
    // TODO [rewrite]
    AS_instrList n = AS_InstrList(instr, NULL);

    if (rl)
      last = last->tail = n;
    else
      rl = last = n;
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

static bool reduceMoves(AS_instrList *iList, Temp_map color)
{
  AS_instrList rl = NULL;
  AS_instrList last = NULL;
  bool reduced = false;
  for (AS_instrList il = *iList; il; il = il->tail)
  {
    AS_instrList l = AS_InstrList(il->head, NULL);
    if (isSynonymMove(il->head, color))
    {
      reduced = true;
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

  if (reduced)
    *iList = rl;

  return reduced;
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
      il = rewriteProgram(il, col_result.spills);
    }
    else
    {
      if (!reduceMoves(&il, col_result.coloring))
        break;
      else
        try++;
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
