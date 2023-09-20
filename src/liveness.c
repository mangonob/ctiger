#include <stdbool.h>
#include <assert.h>
#include "liveness.h"
#include "utils.h"
#include "flowgraph.h"
#include "frame.h"
// #define REPORT_LIVE_MAP

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
  for (SET_voidPtrList el = SET_elements(s); el; el = el->tail)
  {
    tl = Temp_TempList(el->head, tl);
  }
  return tl;
}

static void printTemp(FILE *out, void *t)
{
  Temp_temp _t = (Temp_temp)t;
  Temp_map map = F_initialRegisters(NULL);
  string name = Temp_look(map, _t);

  if (name)
    fprintf(out, "%s", name);
  else
    fprintf(out, "t%d", _t->num);
}

static void reportLiveMap(G_graph flow, G_table in, G_table out, int loop_cnt)
{
  printf("================ Pass %d ================\n", loop_cnt);
  int sn = 1;
  for (G_nodeList nl = G_nodes(flow); nl; nl = nl->tail, ++sn)
  {
    SET_set in_n = lookupLiveMap(in, nl->head);
    SET_set out_n = lookupLiveMap(out, nl->head);
    // TODO print in, out set
    AS_instr instr = (AS_instr)G_nodeInfo(nl->head);
    printf("%d. \t", sn);
    AS_print(stdout, instr, F_initialRegisters(NULL));
    printf("\t in: ");
    SET_show(stdout, in_n, printTemp);
    printf(", out: ");
    SET_show(stdout, out_n, printTemp);
    printf(", def: ");
    SET_show(stdout, setFromTempList(FG_def(nl->head)), printTemp);
    printf(", use: ");
    SET_show(stdout, setFromTempList(FG_use(nl->head)), printTemp);
    printf("\n");
  }
  printf("\n");
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
  // 迭代次数
  int loop_cnt = 0;
  while (changed)
  {
    changed = false;
    loop_cnt++;
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

#ifdef REPORT_LIVE_MAP
    reportLiveMap(flow, in, out, loop_cnt);
#endif
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

void generateConflictMap(struct Live_graph *g, G_graph flow, G_table out)
{
  G_graph conflict = G_Graph();
  Live_moveList moves = NULL;
  TAB_table nodes = TAB_empty();

  for (G_nodeList nl = G_nodes(flow); nl; nl = nl->tail)
  {
    G_node node = nl->head;
    if (FG_isMove(node))
    {
      Temp_tempList use = FG_use(node);
      Temp_tempList def = FG_def(node);

      if (use && def)
      {
        Temp_temp dst = def->head;
        Temp_temp src = use->head;
        G_node dst_node = requestNode(conflict, nodes, dst);
        moves = Live_MoveList(requestNode(conflict, nodes, src), dst_node, moves);

        for (Temp_tempList out_temps = setToTempList(lookupLiveMap(out, node)); out_temps; out_temps = out_temps->tail)
          if (out_temps->head != src)
          {
            G_node out_node = requestNode(conflict, nodes, out_temps->head);
            G_addEdge(dst_node, out_node);
            G_addEdge(out_node, dst_node);
          }
      }
    }
    else
    {
      for (Temp_tempList defs = FG_def(node); defs; defs = defs->tail)
      {
        Temp_temp def_t = defs->head;
        G_node def_node = requestNode(conflict, nodes, def_t);
        for (Temp_tempList out_temps = setToTempList(lookupLiveMap(out, node)); out_temps; out_temps = out_temps->tail)
        {
          G_node out_node = requestNode(conflict, nodes, out_temps->head);
          G_addEdge(def_node, out_node);
          G_addEdge(out_node, def_node);
        }
      }
    }
  }

  g->graph = conflict;
  g->moves = moves;
}

struct Live_graph Live_liveness(G_graph flow)
{
  G_table in = G_empty(), out = G_empty();
  generateLiveMap(flow, in, out);

  struct Live_graph g;
  generateConflictMap(&g, flow, out);

  G_show(stdout, G_nodes(g.graph), printTemp);
  return g;
}
