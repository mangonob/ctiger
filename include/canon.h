#ifndef CANON_H_
#define CANON_H_
#include "temp.h"
#include "tree.h"

typedef struct C_stmListList_ *C_stmListList;
struct C_stmListList_
{
  T_stmList head;
  C_stmListList tail;
};

typedef struct
{
  C_stmListList stmLists;
  Temp_label label;
} C_block;

T_stmList C_linearize(T_stm stm);
C_block C_basicBlocks(T_stmList stmList);
T_stmList C_traceSchedule(C_block b);

#endif
