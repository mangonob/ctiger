#ifndef REGALLOC_H_
#define REGALLOC_H_
#include "temp.h"
#include "assem.h"
#include "frame.h"

struct RA_result
{
  Temp_map coloring;
  AS_instrList il;
};
struct RA_result RA_regAlloc(F_frame f, AS_instrList il);

#endif
