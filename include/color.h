#ifndef COLOR_H_
#define COLOR_H_
#include "temp.h"
#include "graph.h"
#include "liveness.h"
typedef struct
{
  Temp_map coloring;
  Temp_tempList spills;
} COL_result;

COL_result COL_color(G_graph ig, Temp_map initial, Live_moveList moves, G_table nodeMoves, G_table spillCosts, Temp_tempList registers);

#endif
