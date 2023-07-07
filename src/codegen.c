#include <stdbool.h>
#include "codegen.h"

static AS_instrList iList = NULL;
static AS_instrList last = NULL;
static bool lastIsLabel = false;
static void emit(AS_instr i)
{
  lastIsLabel = (i->kind == I_LABEL);
  if (!last)
    last = iList = AS_InstrList(i, NULL);
  else
    last = last->tail = AS_InstrList(i, NULL);
}

static Temp_temp munchExp(T_exp exp)
{
  // TODO
  return NULL;
}

static void munchStm(T_stm stm)
{
  emit(AS_Oper("nop\n", NULL, NULL, NULL));
}

static Temp_tempList munchArgs(int i, T_expList args)
{
  // TODO
  return NULL;
}

AS_instrList F_codegen(F_frame f, T_stmList stmList)
{
  for (; stmList; stmList = stmList->tail)
    munchStm(stmList->head);

  if (last && last->head->kind == I_LABEL)
    emit(AS_Oper("nop\n", NULL, NULL, NULL));

  AS_instrList il = iList;
  iList = last = NULL;
  return il;
}
