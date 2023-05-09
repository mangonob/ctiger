#include "arm64frame.h"

const int F_wordSize = 8;

F_frame F_newFrame(Temp_label name, U_boolList formals)
{
  // TODO
  notImplementation();
}

Temp_label F_name(F_frame f)
{
  return f->entryPoint;
}

F_accessList F_formals(F_frame f)
{
  return f->formals;
}

static F_access InFrame(int offset)
{
  F_access p = _malloc(sizeof(p));
  p->kind = inFrame;
  p->offset = offset;
  return p;
}

static F_access InReg(Temp_temp reg)
{
  F_access p = _malloc(sizeof(p));
  p->kind = inReg;
  p->reg = reg;
  return p;
}

F_access F_allocLocal(F_frame f, bool escape)
{
  F_access access;
  if (escape)
  {
    access = InFrame(f->offset);
    f->offset -= F_wordSize;
  }
  else
  {
    // TODO
  }
  return access;
}

F_access F_staticLink()
{
  // TODO
  notImplementation();
}

T_exp F_externalCall(string s, T_expList args)
{
  return T_Call(T_Name(Temp_namedLabel(s)), args);
}

T_stm F_procEntryExit1(F_frame frame, T_stm stm)
{
  // TODO
  return stm;
}