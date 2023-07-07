#ifndef ASSEM_H_
#define ASSEM_H_
#include <stdio.h>
#include "temp.h"

typedef struct
{
  Temp_labelList labels;
} *AS_targets;
AS_targets AS_Targets(Temp_labelList labels);

typedef struct
{
  enum
  {
    I_OPER,
    I_LABEL,
    I_MOVE
  } kind;

  union
  {
    struct
    {
      string assem;
      Temp_tempList dst;
      Temp_tempList src;
      AS_targets jumps;
    } OPER;

    struct
    {
      string assem;
      Temp_label label;
    } LABEL;

    struct
    {
      string assem;
      Temp_tempList dst;
      Temp_tempList src;
    } MOVE;
  };
} *AS_instr;

AS_instr AS_Oper(string assem, Temp_tempList dst, Temp_tempList src, AS_targets jumps);
AS_instr AS_Label(string assem, Temp_label label);
AS_instr AS_Move(string assem, Temp_tempList dst, Temp_tempList src);

void AS_print(FILE *out, AS_instr i, Temp_map m);

typedef struct AS_instrList_ *AS_instrList;
struct AS_instrList_
{
  AS_instr head;
  AS_instrList tail;
};
AS_instrList AS_InstrList(AS_instr head, AS_instrList tail);

AS_instrList AS_splice(AS_instrList a, AS_instrList b);
void AS_printInstrList(FILE *out, AS_instrList iList, Temp_map m);

typedef struct
{
  string prolog;
  AS_instrList body;
  string epilog;
} *AS_proc;

AS_proc AS_Proc(string prolog, AS_instrList body, string epilog);

#endif
