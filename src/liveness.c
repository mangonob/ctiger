#include <stdbool.h>
#include <assert.h>
#include "liveness.h"
#include "utils.h"
#include "flowgraph.h"
#include "frame.h"

Live_moveList Live_MoveList(G_node src, G_node dst, Live_moveList tail)
{
  Live_moveList p = _malloc(sizeof(*p));
  p->src = src;
  p->dst = dst;
  p->tail = tail;
  return p;
}

Temp_temp Live_gtemp(G_node n)
{
  return G_nodeInfo(n);
}

SET_set setFromTempList(Temp_tempList tl)
{
  SET_set s = SET_empty();
  for (; tl; tl = tl->tail)
    SET_enter(s, tl->head);
  return s;
}

Temp_tempList setToTempList(SET_set s)
{
  Temp_tempList tl = NULL;
  for (List_list el = SET_elements(s); el; el = el->tail)
    tl = Temp_TempList(el->head, tl);
  return tl;
}

static void generateLiveMap(G_graph flow, G_table in, G_table out)
{
  for (G_nodeList nl = G_nodes(flow); nl; nl = nl->tail)
  {
    enterLiveMap(in, nl->head, SET_empty());
    enterLiveMap(out, nl->head, SET_empty());
  }

  G_nodeList rnl = G_NodeListReversed(G_nodes(flow));
  bool changed = true;
  while (changed)
  {
    changed = false;
    for (G_nodeList nl = rnl; nl; nl = nl->tail)
    {
      G_node node = nl->head;
      SET_set in_n = lookupLiveMap(in, node);
      SET_set out_n = lookupLiveMap(out, node);
      assert(in_n);
      assert(out_n);
      int in_n_sz = SET_size(in_n);
      int out_n_sz = SET_size(out_n);
      SET_set use = setFromTempList(FG_use(node));
      SET_set def = setFromTempList(FG_def(node));

      in_n = SET_union(use, SET_subtracting(out_n, def));

      for (G_nodeList succs = G_succ(node); succs; succs = succs->tail)
      {
        G_node succ = succs->head;
        SET_set in_s = lookupLiveMap(in, succ);
        SET_unionWith(out_n, in_s);
      }

      enterLiveMap(in, node, in_n);
      enterLiveMap(out, node, out_n);

      if (SET_size(in_n) != in_n_sz || SET_size(out_n) != out_n_sz)
        changed = true;
    }
  }
}

G_node requestNode(G_graph graph, TAB_table nodes, Temp_temp t)
{
  G_node n = TAB_lookup(nodes, t);
  if (!n)
  {
    n = G_Node(graph, t);
    TAB_push(nodes, t, n);
  }
  return n;
}

void generateConflictMap(Live_graph *g, G_graph flow, G_table out)
{
  G_graph conflict = G_Graph();
  Live_moveList moves = NULL;
  TAB_table nodes = TAB_empty();
  G_table nodeMoves = G_empty();

  for (G_nodeList nl = G_nodes(flow); nl; nl = nl->tail)
  {
    G_node node = nl->head;
    if (FG_isMove(node))
    {
      Temp_tempList use = FG_use(node);
      Temp_tempList def = FG_def(node);
      assert(use && def);

      Temp_temp dst = def->head;
      Temp_temp src = use->head;
      G_node dst_node = requestNode(conflict, nodes, dst);
      G_node src_node = requestNode(conflict, nodes, src);
      moves = Live_MoveList(src_node, dst_node, moves);

      AS_instr instr = G_nodeInfo(node);
      G_enter(nodeMoves, dst_node, SET_union(G_look(nodeMoves, dst_node), SET_singleton(moves)));
      G_enter(nodeMoves, src_node, SET_union(G_look(nodeMoves, src_node), SET_singleton(moves)));

      for (Temp_tempList out_temps = setToTempList(lookupLiveMap(out, node)); out_temps; out_temps = out_temps->tail)
        if (out_temps->head != src && out_temps->head != dst)
        {
          G_node out_node = requestNode(conflict, nodes, out_temps->head);
          G_addEdge(dst_node, out_node);
          G_addEdge(out_node, dst_node);
        }
    }
    else
    {
      for (Temp_tempList uses = FG_use(node); uses; uses = uses->tail)
        requestNode(conflict, nodes, uses->head);

      for (Temp_tempList defs = FG_def(node); defs; defs = defs->tail)
      {
        Temp_temp def_t = defs->head;
        G_node def_node = requestNode(conflict, nodes, def_t);

        for (Temp_tempList out_temps = setToTempList(lookupLiveMap(out, node)); out_temps; out_temps = out_temps->tail)
          if (out_temps->head != def_t)
          {
            G_node out_node = requestNode(conflict, nodes, out_temps->head);
            G_addEdge(def_node, out_node);
            G_addEdge(out_node, def_node);
          }
      }
    }
  }

  // reserved registers
  Temp_tempList rtl = mkTempList(F_SP(), F_FP(), F_ZERO(), F_RA(), NULL);
  G_nodeList reserve = NULL;
  for (; rtl; rtl = rtl->tail)
    reserve = G_NodeList(requestNode(conflict, nodes, rtl->head), reserve);

  for (G_nodeList nl = G_nodes(conflict); nl; nl = nl->tail)
  {
    G_node n = nl->head;
    for (G_nodeList rl = reserve; rl; rl = rl->tail)
      if (n != rl->head)
      {
        G_addEdge(n, rl->head);
        G_addEdge(rl->head, n);
      }
  }

  g->graph = conflict;
  g->moves = moves;
  g->nodeMoves = nodeMoves;
}

static void calculateCost(G_graph flow, Live_graph *live)
{
  G_nodeList f_nodes = G_nodes(flow);
  G_nodeList g_nodes = G_nodes(live->graph);

  TAB_table tempTimes = TAB_empty();
  for (; f_nodes; f_nodes = f_nodes->tail)
  {
    G_node n = f_nodes->head;
    for (Temp_tempList tl = Temp_listSplice(FG_def(n), FG_use(n)); tl; tl = tl->tail)
    {
      Temp_temp t = tl->head;
      int times = (int)(uintptr_t)TAB_lookup(tempTimes, t);
      TAB_push(tempTimes, t, (void *)(uintptr_t)(times + 1));
    }
  }

  G_table costs = G_empty();
  for (; g_nodes; g_nodes = g_nodes->tail)
  {
    G_node n = g_nodes->head;
    Temp_temp t = G_nodeInfo(n);
    int times = (int)(uintptr_t)TAB_lookup(tempTimes, t);
    double cost = (double)G_degree(n) / 2 / times;
    G_enter(costs, n, Double(cost));
  }
  live->spillCosts = costs;
}

Live_graph Live_liveness(G_graph flow)
{
  G_table in = G_empty(), out = G_empty();
  generateLiveMap(flow, in, out);

  Live_graph g;
  generateConflictMap(&g, flow, out);
  calculateCost(flow, &g);
  return g;
}
