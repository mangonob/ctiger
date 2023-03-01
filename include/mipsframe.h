#ifndef MIPSFRAME_H_
#define MIPSFRAME_H_
#include "frame.h"

struct F_frame_
{
  F_accessList formals;
  int locals;
  int offset;
  Temp_label begin_label;
};

struct F_access_
{
  enum
  {
    inFrame,
    inReg
  } type;

  union
  {
    int offset;
    Temp_temp reg;
  };
};

#endif