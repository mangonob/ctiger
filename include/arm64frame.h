#ifndef ARM64FRAME_H_
#define ARM64FRAME_H_
#include "frame.h"
#include "temp.h"

struct F_frame_
{
  F_accessList formals;
  int locals;
  int offset;
  Temp_label entryPoint;
};

struct F_access_
{
  enum
  {
    inFrame,
    inReg
  } kind;
  union
  {
    int offset;
    Temp_temp reg;
  };
};

#endif