#include <stdbool.h>
#include <math.h>
#include "color.h"
#include "set.h"
#include "liveness.h"
#include "frame.h"
#include "assem.h"

// #define VERBOSE

typedef struct
{
  SET_set precolored;
  SET_set initial;
  SET_set simplifyWorklist;
  SET_set freezeWorklist;
  SET_set spillWorklist;
  SET_set spillNodes;
  G_table spillCosts;
  SET_set coalescedNodes;
  SET_set coloredNodes;
  SET_set selectStack;
  SET_set coalescedMoves;
  SET_set constrainedMoves;
  SET_set frozenMoves;
  SET_set worklistMoves;
  SET_set activeMoves;
  G_table degree;
  G_table nodeMoves;
  G_table alias;
  Temp_map color;

  // Map temp to nodes;
  TAB_table nodes;

  int K;
} COL_ctx;

COL_ctx context;

static G_node temp2Node(Temp_temp t)
{
  return TAB_lookup(context.nodes, t);
}

static Temp_temp node2Temp(G_node n)
{
  return Live_gtemp(n);
}

static G_nodeList set2NodeList(SET_set s)
{
  List_list el = SET_elements(s);
  G_nodeList list = NULL;
  for (; el; el = el->tail)
    list = G_NodeList(el->head, list);
  return list;
}

static SET_set nodeList2Set(G_nodeList nl)
{
  SET_set s = SET_empty();
  for (; nl; nl = nl->tail)
    SET_enter(s, nl->head);
  return s;
}

static Temp_tempList nodeList2TempList(G_nodeList nl)
{
  Temp_tempList tl = NULL;
  Temp_tempList last = NULL;
  for (; nl; nl = nl->tail)
  {
    Temp_tempList n = Temp_TempList(node2Temp(nl->head), NULL);
    if (tl)
      last = last->tail = n;
    else
      tl = last = n;
  }
  return tl;
}

static SET_set temps2Nodes(SET_set s)
{
  return SET_map(s, (void *(*)(void *))temp2Node);
}

static SET_set tempList2Set(Temp_tempList tl)
{
  SET_set s = SET_empty();
  for (; tl; tl = tl->tail)
    SET_enter(s, tl->head);
  return s;
}

static SET_set moveListToSet(Live_moveList l)
{
  SET_set s = SET_empty();
  for (; l; l = l->tail)
    SET_enter(s, l);
  return s;
}

static int getDegree(G_node n)
{
  return (int)(uintptr_t)G_look(context.degree, n);
}

static G_node getAlias(G_node n)
{
  G_node alias = G_look(context.alias, n);
  return alias ? getAlias(alias) : n;
}

static void setAlias(G_node n, G_node alias)
{
  G_enter(context.alias, n, alias);
}

static void setDegree(G_node n, int d)
{
  G_enter(context.degree, n, (void *)(uintptr_t)d);
}

static bool moveRelatived(G_node n)
{
  SET_set s = G_look(context.nodeMoves, n);
  return s != NULL && !SET_isEmpty(s);
}

static SET_set adjacent(G_node n)
{
  SET_set adjs = nodeList2Set(G_adj(n));
  SET_subtractingWith(adjs, SET_union(context.selectStack, context.coloredNodes));
  return adjs;
}

static void print_temp(FILE *out, void *temp)
{
  Temp_temp t = (Temp_temp)temp;
  string name = Temp_look(context.color, t);
  if (name)
    fprintf(out, "%s", name);
  else
    fprintf(out, "t%d", t->num);
}

static void print_node(FILE *out, void *node)
{
  print_temp(out, node2Temp(node));
}

static void printAlias(FILE *out, void *k, void *v)
{
  G_node alias = (G_node)v;
  G_node n = (G_node)k;
  print_node(out, alias);
  fprintf(out, " <- ");
  print_node(out, n);
  fprintf(out, ", ");
}

static void dumpMoves(FILE *out, SET_set s)
{
  fprintf(out, "{ ");
  for (List_list el = SET_elements(s); el; el = el->tail)
  {
    Live_moveList ml = el->head;
    print_node(out, ml->dst);
    fprintf(out, " <= ");
    print_node(out, ml->src);
    fprintf(out, el->tail ? ", " : " ");
  }
  fprintf(out, "}\n");
}

static void dumpContext(FILE *out)
{
  fprintf(out, "================ Context ================\n");
  fprintf(out, "precolored:\t");
  SET_show(out, context.precolored, print_temp);
  fprintf(out, "simplifyWorklist:\t");
  SET_show(out, context.simplifyWorklist, print_node);
  fprintf(out, "freezeWorklist:\t");
  SET_show(out, context.freezeWorklist, print_node);
  fprintf(out, "spillWorklist:\t");
  SET_show(out, context.spillWorklist, print_node);
  fprintf(out, "spillNodes:\t");
  SET_show(out, context.spillNodes, print_node);
  fprintf(out, "coalescedNodes:\t");
  SET_show(out, context.coalescedNodes, print_node);
  fprintf(out, "coloredNodes:\t");
  SET_show(out, context.coloredNodes, print_node);
  fprintf(out, "selectStack:\t");
  SET_show(out, context.selectStack, print_node);
  fprintf(out, "alias:\t{ ");
  TAB_dump(out, context.alias, printAlias);
  fprintf(out, "}\n");
  fprintf(out, "worklistMoves:\t");
  dumpMoves(out, context.worklistMoves);
  fprintf(out, "activeMoves:\t");
  dumpMoves(out, context.activeMoves);
  fprintf(out, "constrainedMoves:\t");
  dumpMoves(out, context.constrainedMoves);
  fprintf(out, "coalescedMoves:\t");
  dumpMoves(out, context.coalescedMoves);
  fprintf(out, "frozenMoves:\t");
  dumpMoves(out, context.frozenMoves);
}

static void makeWorklist()
{
  for (Temp_temp t = SET_dequeue(context.initial); t; t = SET_dequeue(context.initial))
  {
    G_node node = temp2Node(t);
    int degree = getDegree(node);
    if (degree >= context.K)
      SET_enter(context.spillWorklist, node);
    else if (moveRelatived(node))
      SET_enter(context.freezeWorklist, node);
    else
      SET_enter(context.simplifyWorklist, node);
  }
}

static SET_set nodeMoves(G_node node)
{
  SET_set moves = G_look(context.nodeMoves, node);
  if (moves)
    return SET_intersection(moves, SET_union(context.activeMoves, context.worklistMoves));
  else
    return SET_empty();
}

static void enableMoves(SET_set moves)
{
  List_list el = SET_elements(moves);
  for (; el; el = el->tail)
  {
    List_list ml = SET_elements(nodeMoves(el->head));
    for (; ml; ml = ml->tail)
    {
      if (SET_contains(context.activeMoves, ml))
      {
        SET_remove(context.activeMoves, ml);
        SET_enter(context.activeMoves, ml);
      }
    }
  }
}

static void decrementDegree(G_node n)
{
  int d = getDegree(n);
  setDegree(n, d - 1);
  if (d == context.K)
  {
    enableMoves(SET_union(SET_singleton(n), adjacent(n)));
    SET_remove(context.spillWorklist, n);
    if (moveRelatived(n))
      SET_enter(context.freezeWorklist, n);
    else
      SET_enter(context.simplifyWorklist, n);
  }
}

static bool isPrecolored(G_node n)
{
  return SET_contains(context.precolored, node2Temp(n));
}

static bool isOk(G_node t, G_node r)
{
  return getDegree(t) < context.K || isPrecolored(t) || G_goesTo(t, r);
}

static bool allAdjsOk(G_node n, G_node with)
{
  for (List_list nl = SET_elements(adjacent(n)); nl; nl = nl->tail)
    if (!isOk(nl->head, with))
      return false;
  return true;
}

static void simplify()
{
  G_node n = SET_dequeue(context.simplifyWorklist);
  SET_enter(context.selectStack, n);
  for (List_list nl = SET_elements(adjacent(n)); nl; nl = nl->tail)
    decrementDegree(nl->head);
}

static void addWorkList(G_node n)
{
  if (!isPrecolored(n) && !moveRelatived(n) && getDegree(n) < context.K)
  {
    SET_remove(context.freezeWorklist, n);
    SET_enter(context.simplifyWorklist, n);
  }
}

static bool conservative(SET_set nodes)
{
  int k = 0;
  for (List_list nl = SET_elements(nodes); nl; nl = nl->tail)
    if (getDegree(nl->head) >= context.K)
      k++;
  return k < context.K;
}

static void addEdge(G_node u, G_node v)
{
  if (!G_goesTo(u, v) && u != v)
  {
    G_addEdge(u, v);
    G_addEdge(v, u);
    if (!isPrecolored(u))
      setDegree(u, getDegree(u) + 1);
    if (!isPrecolored(v))
      setDegree(v, getDegree(v) + 1);
  }
}

static void combine(G_node u, G_node v)
{
  if (SET_contains(context.freezeWorklist, v))
    SET_remove(context.freezeWorklist, v);
  else
    SET_remove(context.spillWorklist, v);

  SET_enter(context.coalescedNodes, v);
  setAlias(v, u);
  G_enter(context.nodeMoves, u, SET_union(G_look(context.nodeMoves, u), G_look(context.nodeMoves, v)));
  enableMoves(SET_singleton(v));
  for (List_list el = SET_elements(adjacent(v)); el; el = el->tail)
  {
    G_node t = el->head;
    addEdge(t, u);
    decrementDegree(t);
  }
  if (getDegree(u) >= context.K && SET_contains(context.freezeWorklist, u))
  {
    SET_remove(context.freezeWorklist, u);
    SET_enter(context.spillWorklist, u);
  }
}

static void coalesce()
{
  Live_moveList m = SET_pop(context.worklistMoves);
  G_node x = m->dst;
  G_node y = m->src;
  G_node u = x;
  G_node v = y;
  if (isPrecolored(y))
  {
    u = y;
    v = x;
  }
  if (u == v)
  {
    SET_enter(context.coalescedMoves, m);
    addWorkList(u);
  }
  else if (isPrecolored(v) || G_goesTo(u, v))
  {
    SET_enter(context.constrainedMoves, m);
    addWorkList(u);
    addWorkList(v);
  }
  else if (isPrecolored(u) && allAdjsOk(v, u) ||
           !isPrecolored(u) && conservative(adjacent(u)))
  {
    SET_enter(context.coalescedMoves, m);
    combine(u, v);
    addWorkList(u);
  }
  else
  {
    SET_enter(context.activeMoves, m);
  }
}

static void freezeMoves(G_node node)
{
  for (List_list nl = SET_elements(nodeMoves(node)); nl; nl = nl->tail)
  {
    Live_moveList ml = nl->head;
    G_node x = ml->dst;
    G_node y = ml->src;
    G_node v = getAlias(x) == getAlias(node) ? getAlias(y) : getAlias(x);
    SET_remove(context.activeMoves, ml);
    SET_enter(context.activeMoves, ml);

    if (SET_isEmpty(nodeMoves(v)) && getDegree(v) < context.K)
    {
      SET_remove(context.freezeWorklist, v);
      SET_enter(context.simplifyWorklist, v);
    }
  }
}

static void freeze()
{
  G_node n = SET_pop(context.freezeWorklist);
  SET_enter(context.simplifyWorklist, n);
  freezeMoves(n);
}

static double spillCosts(G_node n)
{
  return *(double *)G_look(context.spillCosts, n);
}

static void selectSpill()
{
  double maxCost = -INFINITY;
  G_node m = NULL;
  for (List_list el = SET_elements(context.spillWorklist); el; el = el->tail)
  {
    G_node n = el->head;
    double cost = spillCosts(n);
    if (cost > maxCost)
    {
      maxCost = cost;
      m = n;
    }
  }
  SET_remove(context.spillWorklist, m);
  SET_enter(context.simplifyWorklist, m);
  freezeMoves(m);
}

static void assignColors()
{
  SET_set coloredNodes = SET_empty();
  for (G_node n = SET_pop(context.selectStack); n; n = SET_pop(context.selectStack))
  {
    SET_set okColors = SET_empty();
    for (List_list el = SET_elements(context.precolored); el; el = el->tail)
    {
      string col = Temp_look(context.color, el->head);
      SET_enter(okColors, col);
    }

    for (G_nodeList nl = G_adj(n); nl; nl = nl->tail)
    {
      G_node w = nl->head;
      if (SET_contains(SET_union(context.coloredNodes, temps2Nodes(context.precolored)), getAlias(w)))
        SET_remove(okColors, Temp_look(context.color, node2Temp(getAlias(w))));
    }

    if (SET_isEmpty(okColors))
    {
      SET_enter(context.spillNodes, n);
    }
    else
    {
      SET_enter(context.coloredNodes, n);
      Temp_enter(context.color, node2Temp(n), SET_first(okColors));
    }
  }

  for (List_list el = SET_elements(context.coalescedNodes); el; el = el->tail)
  {
    G_node n = el->head;
    Temp_temp t = node2Temp(n);
    G_node alias = getAlias(n);
    Temp_temp at = node2Temp(alias);
    Temp_enter(context.color, t, Temp_look(context.color, at));
  }
}

static void colorMain()
{
  makeWorklist();
#ifdef VERBOSE
  dumpContext(stdout);
#endif
  do
  {
    if (!SET_isEmpty(context.simplifyWorklist))
      simplify();
    else if (!SET_isEmpty(context.worklistMoves))
      coalesce();
    else if (!SET_isEmpty(context.freezeWorklist))
      freeze();
    else if (!SET_isEmpty(context.spillWorklist))
      selectSpill();
#ifdef VERBOSE
    dumpContext(stdout);
#endif
  } while (
      !SET_isEmpty(context.simplifyWorklist) ||
      !SET_isEmpty(context.worklistMoves) ||
      !SET_isEmpty(context.freezeWorklist) ||
      !SET_isEmpty(context.spillWorklist));
  assignColors();
}

COL_result COL_color(G_graph ig, Temp_map initial, Live_moveList moves, G_table nodeMoves, G_table spillCosts, Temp_tempList registers)
{
  COL_result result;

  context.precolored = tempList2Set(registers);
  context.simplifyWorklist = SET_empty();
  context.freezeWorklist = SET_empty();
  context.spillWorklist = SET_empty();
  context.spillNodes = SET_empty();
  context.spillCosts = spillCosts;
  context.coalescedNodes = SET_empty();
  context.coloredNodes = SET_empty();
  context.selectStack = SET_empty();
  context.coalescedMoves = SET_empty();
  context.constrainedMoves = SET_empty();
  context.frozenMoves = SET_empty();
  context.worklistMoves = moveListToSet(moves);
  context.activeMoves = SET_empty();
  context.degree = G_empty();
  context.nodeMoves = nodeMoves;
  context.alias = G_empty();
  context.color = Temp_layerMap(Temp_empty(), initial);
  context.K = Temp_listLen(registers);

#ifdef VERBOSE
  G_show(stdout, G_nodes(ig), print_temp);
#endif

  context.nodes = TAB_empty();
  context.initial = SET_empty();
  for (G_nodeList nl = G_nodes(ig); nl; nl = nl->tail)
  {
    G_node node = nl->head;
    Temp_temp t = node2Temp(node);
    TAB_push(context.nodes, t, node);
    if (Temp_look(initial, t))
    {
      setDegree(node, __INT_MAX__);
    }
    else
    {
      setDegree(node, G_degree(node) / 2);
      SET_enter(context.initial, t);
    }
  }

  colorMain();

  result.coloring = context.color;
  result.spills = nodeList2TempList(set2NodeList(context.spillNodes));
  return result;
}
