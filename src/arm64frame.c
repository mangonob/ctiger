#include "arm64frame.h"

const int F_wordSize = 8;

Temp_label F_name(F_frame f)
{
  return f->name;
}

F_accessList F_formals(F_frame f)
{
  return f->formals;
}

int F_accessOffset(F_access f)
{
  return f->offset;
}

F_accessList F_AccessList(F_access head, F_accessList tail)
{
  F_accessList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

F_accessList F_AccessListReversed(F_accessList list)
{
  F_accessList r = NULL;
  for (; list && list->head; list = list->tail)
    r = F_AccessList(list->head, r);
  return r;
}

static F_access InFrame(int offset)
{
  F_access p = _malloc(sizeof(*p));
  p->kind = inFrame;
  p->offset = offset;
  return p;
}

static F_access InReg(Temp_temp reg)
{
  F_access p = _malloc(sizeof(*p));
  p->kind = inReg;
  p->reg = reg;
  return p;
}

F_frag F_StringFrag(Temp_label label, string str)
{
  F_frag p = _malloc(sizeof(*p));
  p->kind = F_stringFrag;
  p->stringg.label = label;
  p->stringg.str = str;
  return p;
}

F_frag F_ProcFrag(T_stm body, F_frame frame)
{
  F_frag p = _malloc(sizeof(*p));
  p->kind = F_procFrag;
  p->proc.body = body;
  p->proc.frame = frame;
  return p;
}

F_fragList F_FragList(F_frag head, F_fragList tail)
{
  F_fragList p = _malloc(sizeof(p));
  p->head = head;
  p->tail = tail;
  return p;
}

F_frame F_newFrame(Temp_label name, U_boolList formalEscapes)
{
  F_frame f = _malloc(sizeof(*f));
  f->name = name;
  f->offset = 0;
  f->formals = NULL;

  F_accessList formals = NULL;
  for (; formalEscapes; formalEscapes = formalEscapes->tail)
  {
    if (formalEscapes->head)
    {
      formals = F_AccessList(InFrame(f->offset), formals);
      f->offset -= F_wordSize;
    }
    else
      formals = F_AccessList(InReg(Temp_newtemp()), formals);
  }
  f->formals = F_AccessListReversed(formals);

  return f;
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
    access = InReg(Temp_newtemp());
  f->locals = F_AccessList(access, f->locals);
  return access;
}

static F_access static_link = NULL;
F_access F_staticLink()
{
  if (!static_link)
    static_link = InFrame(0);
  return static_link;
}

static Temp_temp fp = NULL;
Temp_temp F_FP()
{
  if (!fp)
    fp = Temp_newtemp();
  return fp;
}

static Temp_temp rv = NULL;
Temp_temp F_RV()
{
  if (!rv)
    rv = Temp_newtemp();
  return rv;
}

T_exp F_Exp(F_access acc, T_exp framePtr)
{
  if (acc->kind == inFrame)
    return T_Mem(T_Binop(T_plus, framePtr, T_Const(F_accessOffset(acc))));
  else
    return T_Temp(acc->reg);
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
