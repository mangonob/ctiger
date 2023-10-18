#ifndef REGALLOC_H_
#define REGALLOC_H_
#include "temp.h"
#include "assem.h"
#include "frame.h"

typedef struct
{
  Temp_map coloring;
  AS_instrList il;
} RA_result;

RA_result RA_regAlloc(F_frame frame, AS_instrList il);

#endif
