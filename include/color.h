#ifndef COLOR_H_
#define COLOR_H_
#include "temp.h"
#include "graph.h"

struct COL_result
{
  Temp_map coloring;
  Temp_tempList spills;
};
struct COL_result COL_color(G_graph ig, Temp_map initial, Temp_tempList regs);

#endif
