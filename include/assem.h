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

#endif
