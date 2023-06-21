#ifndef ARM64FRAME_H_
#define ARM64FRAME_H_
#include "frame.h"
#include "temp.h"

struct F_frame_
{
  F_accessList formals;
  F_accessList locals;
  int offset;
  Temp_label name;
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
