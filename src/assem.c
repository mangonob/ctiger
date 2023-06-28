#include "assem.h"
#include "utils.h"

AS_instr AS_Oper(string assem, Temp_tempList dst, Temp_tempList src, AS_targets jumps)
{
  AS_instr p = _malloc(sizeof(*p));
  p->kind = I_OPER;
  p->OPER.assem = assem;
  p->OPER.dst = dst;
  p->OPER.src = src;
  p->OPER.jumps = jumps;
  return p;
}

AS_instr AS_Label(string assem, Temp_label label)
{
  AS_instr p = _malloc(sizeof(*p));
  p->kind = I_LABEL;
  p->LABEL.assem = assem;
  p->LABEL.label = label;
  return p;
}

AS_instr AS_Move(string assem, Temp_tempList dst, Temp_tempList src)
{
  AS_instr p = _malloc(sizeof(*p));
  p->kind = I_MOVE;
  p->MOVE.assem = assem;
  p->MOVE.dst = dst;
  p->MOVE.src = src;
  return p;
}
