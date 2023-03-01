#include "mipsframe.h"
#include "temp.h"

static F_access InFrame(int offset)
{
  F_access access = _malloc(sizeof(*access));
  access->type = inFrame;
  access->offset = offset;
  return access;
}

static F_access InReg(Temp_temp reg)
{
  F_access access = _malloc(sizeof(*access));
  access->type = inReg;
  access->reg = reg;
  return access;
}

F_frame F_newFrame(Temp_label name, U_boolList formals)
{
  // TODO: implement create new frame
  return NULL;
}

Temp_label F_name(F_frame f)
{
  return f->begin_label;
}

F_access F_staticLink()
{
  static F_access static_link = NULL;
  InFrame(0);
  return static_link;
}

static Temp_temp sn[8] = {};
static Temp_temp tn[10] = {};
static Temp_temp an[4] = {};
static Temp_temp vn[2] = {};

Temp_temp F_FP()
{
  // TODO: implement
  return NULL;
}

Temp_temp F_RA()
{
  // TODO: implement
  return NULL;
}

Temp_temp F_RV()
{
  // TODO: implement
  return NULL;
}

Temp_temp F_SP()
{
  // TODO: implement
  return NULL;
}

Temp_temp F_ZERO()
{
  // TODO: implement
  return NULL;
}

Temp_temp F_SN(int i)
{
  // TODO: implement
  return NULL;
}

Temp_temp F_TN(int i)
{
  // TODO: implement
  return NULL;
}

Temp_temp F_AN(int i)
{
  // TODO: implement
  return NULL;
}

Temp_temp F_VN(int i)
{
  // TODO: implement
  return NULL;
}