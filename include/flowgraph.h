#ifndef FLOWGRAPH_H_
#define FLOWGRAPH_H_
#include <stdio.h>
#include "graph.h"
#include "temp.h"
#include "assem.h"

Temp_tempList FG_def(G_node n);
Temp_tempList FG_use(G_node n);
bool FG_isMove(G_node n);
void FG_show(FILE *out, G_graph graph, AS_instrList il, Temp_map m);

G_graph FG_AssemFlowGraph(AS_instrList il);

#endif
