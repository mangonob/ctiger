#ifndef LIVENESS_H_
#define LIVENESS_H_
#include "graph.h"
#include "temp.h"
#include "set.h"

typedef struct Live_moveList_ *Live_moveList;
struct Live_moveList_
{
  G_node src;
  G_node dst;
  Live_moveList tail;
};
Live_moveList Live_MoveList(G_node src, G_node dst, Live_moveList tail);

typedef struct
{
  G_graph graph;
  Live_moveList moves;
  G_table spillCosts;
  G_table nodeMoves;
} Live_graph;

Temp_temp Live_gtemp(G_node n);

Live_graph Live_liveness(G_graph flow);

static void enterLiveMap(G_table t, G_node flownode, SET_set temps)
{
  G_enter(t, flownode, temps);
}

static SET_set lookupLiveMap(G_table t, G_node flownode)
{
  return G_look(t, flownode);
}

#endif
