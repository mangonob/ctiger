#include <assert.h>
#include "graph.h"
#include "utils.h"

struct G_graph_
{
  int nodecount;
  G_nodeList nodes;
  G_nodeList last;
};

struct G_node_
{
  G_graph graph;
  int key;
  G_nodeList succs;
  G_nodeList preds;
  void *info;
};

G_graph G_Graph(void)
{
  G_graph p = _malloc(sizeof(*p));
  p->nodecount = 0;
  p->last = NULL;
  p->nodes = NULL;
  return p;
}

G_node G_Node(G_graph g, void *info)
{
  G_node p = _malloc(sizeof(*p));
  G_nodeList l = G_NodeList(p, NULL);
  assert(g);
  p->graph = g;
  p->key = g->nodecount++;

  if (g->last == NULL)
    g->nodes = g->last = l;
  else
    g->last = g->last->tail = l;

  p->succs = NULL;
  p->preds = NULL;
  p->info = info;
  return p;
}

G_nodeList G_NodeList(G_node head, G_nodeList tail)
{
  G_nodeList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

G_nodeList G_NodeListReversed(G_nodeList list)
{
  G_nodeList nl = NULL;

  for (; list; list = list->tail)
    nl = G_NodeList(list->head, nl);

  return nl;
}

G_nodeList G_nodes(G_graph g)
{
  return g->nodes;
}

bool G_inNodeList(G_node n, G_nodeList l)
{
  if (!n || !l)
    return false;

  for (; l; l = l->tail)
    if (n && n == l->head)
      return true;

  return false;
}

void G_addEdge(G_node from, G_node to)
{
  assert(from && to);
  assert(from->graph == to->graph);

  if (G_goesTo(from, to))
    return;

  to->preds = G_NodeList(from, to->preds);
  from->succs = G_NodeList(to, from->succs);
}

static G_nodeList delete_(G_node a, G_nodeList l)
{
  if (!l)
    return NULL;
  if (a == l->head)
    return l->tail;
  else
    return G_NodeList(l->head, delete_(a, l->tail));
}

void G_rmEdge(G_node from, G_node to)
{
  assert(from && to);
  from->succs = delete_(to, from->succs);
  to->preds = delete_(from, to->preds);
}

int G_nodeListFindIndex(G_nodeList nl, G_node n)
{
  if (nl && n)
  {
    for (int i = 0; nl; nl = nl->tail, ++i)
      if (nl->head == n)
        return i;
  }
  return -1;
}

void G_show(FILE *out, G_nodeList p, void showInfo(FILE *, void *))
{
  G_nodeList nl = p;
  for (int i = 0; p; p = p->tail, ++i)
  {
    G_node node = p->head;
    showInfo(out, G_nodeInfo(node));
    G_nodeList succs = node->succs;
    if (succs)
    {
      fprintf(out, "\t==> { ");
      for (; succs; succs = succs->tail)
      {
        showInfo(out, G_nodeInfo(succs->head));
        if (succs->tail)
          fprintf(out, ", ");
      }
      fprintf(out, " }");
    }

    fprintf(out, "\n");
  }
}

G_nodeList G_succ(G_node n)
{
  assert(n);
  return n->succs;
}
G_nodeList G_pred(G_node n)
{
  assert(n);
  return n->preds;
}

static G_nodeList cat(G_nodeList a, G_nodeList b)
{
  G_nodeList l = NULL;
  G_nodeList last = NULL;

  for (; a; a = a->tail)
  {
    G_nodeList n = G_NodeList(a->head, NULL);
    if (l)
      last = last->tail = n;
    else
      l = last = n;
  }

  for (; b; b = b->tail)
  {
    G_nodeList n = G_NodeList(b->head, NULL);
    if (l)
      last = last->tail = n;
    else
      l = last = n;
  }

  return l;
}

G_nodeList G_adj(G_node n)
{
  return cat(G_succ(n), G_pred(n));
}

bool G_goesTo(G_node from, G_node to)
{
  return G_inNodeList(to, from->succs);
}

static int G_nodeListLength(G_nodeList l)
{
  int c = 0;
  for (; l; l = l->tail)
    c++;
  return c;
}

int G_degree(G_node n)
{
  return G_nodeListLength(G_pred(n)) + G_nodeListLength(G_succ(n));
}

void *G_nodeInfo(G_node n)
{
  return n->info;
}

G_table G_empty()
{
  return TAB_empty();
}

void G_enter(G_table t, G_node n, void *v)
{
  TAB_push(t, n, v);
}

void *G_look(G_table t, G_node n)
{
  return TAB_lookup(t, n);
}
