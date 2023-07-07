#ifndef GRAPH_H_
#define GRAPH_H_
#include <stdio.h>
#include <stdbool.h>
#include "table.h"

typedef struct G_graph_ *G_graph;
typedef struct G_node_ *G_node;

typedef struct G_nodeList_ *G_nodeList;
struct G_nodeList_
{
  G_node head;
  G_nodeList tail;
};

G_graph G_Graph(void);
G_node G_Node(G_graph g, void *info);
G_nodeList G_NodeList(G_node head, G_nodeList tail);
G_nodeList G_nodes(G_graph g);
bool G_inNodeList(G_node n, G_nodeList l);
void G_addEdge(G_node from, G_node to);
void G_rmEdge(G_node from, G_node to);
void G_show(FILE *out, G_nodeList p, void showInfo(void *));
G_nodeList G_succ(G_node n);
G_nodeList G_pred(G_node n);
G_nodeList G_adj(G_node n);
bool G_goesTo(G_node from, G_node to);
int G_degree(G_node n);
void *G_nodeInfo(G_node n);

typedef struct TAB_table_ *G_table;
G_table G_empty();
void G_insert(G_table t, G_node n, void *v);
void *G_look(G_table t, G_node n);

#endif
