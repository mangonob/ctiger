#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "arm64frame.h"
#include "utils.h"
#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define L(...) mkTempList(__VA_ARGS__, NULL)

#define MAX_REG_NO 30

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

Temp_temp gen_registers[MAX_REG_NO + 1] = {0};

Temp_temp F_XN(int n)
{
  assert(n >= 0 && n <= MAX_REG_NO);

  if (!gen_registers[n])
    gen_registers[n] = Temp_newtemp();
  return gen_registers[n];
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
      f->offset -= F_wordSize;
      formals = F_AccessList(InFrame(f->offset), formals);
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
    f->offset -= F_wordSize;
    access = InFrame(f->offset);
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
    fp = F_XN(29);
  return fp;
}

static Temp_temp ra = NULL;
Temp_temp F_RA()
{
  if (!ra)
    ra = F_XN(30);
  return ra;
}

static Temp_temp rv = NULL;
Temp_temp F_RV()
{
  if (!rv)
    rv = F_XN(0);
  return rv;
}

static Temp_temp sp = NULL;
Temp_temp F_SP()
{
  if (!sp)
    sp = Temp_newtemp();
  return sp;
}

static Temp_temp zero = NULL;
Temp_temp F_ZERO()
{
  if (!zero)
    zero = Temp_newtemp();
  return zero;
}

Temp_tempList F_callersaves()
{
  return mkTempList(F_XN(8), F_XN(9), F_XN(10), F_XN(11), F_XN(12), F_XN(13), F_XN(14), F_XN(15), NULL);
}

Temp_tempList F_calleesaves()
{
  return mkTempList(F_XN(19), F_XN(20), F_XN(21), F_XN(22), F_XN(23), F_XN(24), F_XN(25), F_XN(26), F_XN(27), F_XN(28), NULL);
}

static Temp_tempList F_arguments()
{
  return mkTempList(F_XN(0), F_XN(1), F_XN(2), F_XN(3), F_XN(4), F_XN(5), F_XN(6), F_XN(7), NULL);
}

Temp_tempList F_registers()
{
  return Temp_listSplice(
      Temp_listSplice(
          F_callersaves(),
          F_calleesaves()),
      Temp_listSplice(
          F_arguments(),
          mkTempList(F_SP(), F_FP(), F_RV(), F_ZERO(), NULL)));
}

Temp_map F_initialRegisters(F_frame f)
{
  Temp_map m = Temp_empty();
  for (int n = 0; n <= MAX_REG_NO; ++n)
  {
    char reg_name[4] = {};
    sprintf(reg_name, "x%d", n);
    Temp_enter(m, F_XN(n), String(reg_name));
  }
  Temp_enter(m, F_ZERO(), "xzr");
  Temp_enter(m, F_FP(), "fp");
  Temp_enter(m, F_SP(), "sp");
  return m;
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
  // 参数复制
  T_stm copyFormals = NULL;
  int i = 0;

  for (F_accessList formals = F_formals(frame); formals; formals = formals->tail)
  {
    F_access acc = formals->head;
    T_stm mov = NULL;
    T_exp d = F_Exp(acc, T_Temp(F_FP()));

    if (i <= 7)
      mov = T_Move(d, T_Temp(F_XN(i)));
    else
      mov = T_Move(d, T_Mem(T_Binop(T_plus, T_Temp(F_FP()), T_Const(F_wordSize * (8 - i)))));
    copyFormals = copyFormals ? T_Seq(copyFormals, mov) : mov;

    ++i;
  }

  if (copyFormals)
    stm = T_Seq(copyFormals, stm);

  // 保存Callee寄存器
  Temp_tempList callee = F_calleesaves();
  Temp_tempList reversed = NULL;
  Temp_tempList saved = NULL;

  T_stm saveStm = NULL;
  for (; callee; callee = callee->tail)
  {
    Temp_temp r = callee->head;
    reversed = Temp_TempList(r, reversed);
    Temp_temp t = Temp_newtemp();
    saved = Temp_TempList(t, saved);
    T_stm mov = T_Move(T_Temp(t), T_Temp(r));
    saveStm = saveStm ? T_Seq(saveStm, mov) : mov;
  }

  if (saveStm)
    stm = T_Seq(saveStm, stm);

  // 恢复Callee寄存器
  for (; saved; saved = saved->tail, reversed = reversed->tail)
  {
    Temp_temp t = saved->head;
    Temp_temp r = reversed->head;
    stm = T_Seq(stm, T_Move(T_Temp(r), T_Temp(t)));
  }

  return stm;
}

int align(int n, int size)
{
  return n % size ? (n / size + 1) * size : (n / size * size);
}

AS_instrList F_procEntryExit2(F_frame frame, AS_instrList body)
{
  // -1 means if leaf function, no need to alloc stack
  int max_formals_cnt = -1;
  for (AS_instrList iList = body; iList; iList = iList->tail)
  {
    AS_instr instr = iList->head;
    if (instr->kind == I_CALL)
      max_formals_cnt = MAX(max_formals_cnt, instr->CALL.formals_cnt);
  }

  int frame_size = align(-frame->offset + max_formals_cnt * F_wordSize, 16)
                   // reserve for return address and frame pointer
                   - F_wordSize * 2;
  AS_instrList prefix = mkInstrList(
      AS_Oper(Format("sub `d0, `s0, #%d", frame_size + F_wordSize * 2), L(F_SP()), L(F_SP()), NULL),
      AS_Oper(Format("stp `s0, `s1, [`s2, %d]", frame_size), NULL, L(F_FP(), F_RA(), F_SP()), NULL),
      NULL);
  AS_instrList postfix = mkInstrList(
      AS_Oper(Format("ldp `s0, `s1, [`s2, %d]", frame_size), NULL, L(F_FP(), F_RA(), F_SP()), NULL),
      AS_Oper("ret", NULL, NULL, NULL),
      NULL);

  return AS_splice(AS_splice(prefix, body), postfix);
}

AS_proc F_procEntryExit3(F_frame frame, AS_instrList body)
{
  return AS_Proc(
      Format("; PROCEDURE %s BEGIN", frame->name->name),
      AS_InstrList(AS_Label(Format("%s:", Temp_labelstring(frame->name)), frame->name), body),
      Format("; PROCEDURE %s END", frame->name->name));
}
