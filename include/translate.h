#ifndef TRANSLATE_H_
#define TRANSLATE_H_
#include "tree.h"
#include "absyn.h"
#include "utils.h"
#include "frame.h"

typedef struct patchList_ *patchList;

typedef struct Tr_exp_ *Tr_exp;

typedef struct Tr_expseq_ *Tr_expseq;

typedef struct Tr_access_ *Tr_access;

typedef struct Tr_accessList_ *Tr_accessList;

typedef struct Tr_level_ *Tr_level;

struct Cx
{
  patchList trues;
  patchList falses;
  T_stm stm;
};

struct Tr_exp_
{
  enum
  {
    Tr_ex,
    Tr_nx,
    Tr_cx
  } kind;

  union
  {
    T_exp ex;
    T_stm nx;
    struct Cx cx;
  };
};

struct Tr_expseq_
{
  Tr_exp head;
  Tr_expseq tail;
};

struct patchList_
{
  Temp_label *head;
  patchList tail;
};

static patchList PatchList(Temp_label *head, patchList tail);

static Tr_exp Tr_Ex(T_exp ex);
static Tr_exp Tr_Nx(T_stm nx);
static Tr_exp Tr_Cx(patchList trues, patchList falses, T_stm stm);

static T_exp unEx(Tr_exp e);
static T_stm unNx(Tr_exp e);
static struct Cx unCx(Tr_exp e);

Tr_expseq Tr_ExpSeq(Tr_exp head, Tr_expseq tail);
Tr_expseq Tr_ExpSeqReversed(Tr_expseq seq);
int Tr_ExpSeqLength(Tr_expseq seq);

void Tr_procEntryExit(Tr_level level, Tr_exp body, Tr_accessList accessList);
F_fragList Tr_getResult();

Tr_exp Tr_intExp(int value);
Tr_exp Tr_stringExp(string str);
Tr_exp Tr_nilExp();
Tr_exp Tr_assignExp(Tr_exp dest, Tr_exp source);
Tr_exp Tr_seqExp(Tr_expseq seq);
Tr_exp Tr_arithExp(A_oper op, Tr_exp left, Tr_exp right);
Tr_exp Tr_logicExp(A_oper op, Tr_exp left, Tr_exp right);
Tr_exp Tr_strcmpExp(A_oper op, Tr_exp left, Tr_exp right);
Tr_exp Tr_breakExp(Temp_label brk);
Tr_exp Tr_whileExp(Tr_exp cond, Tr_exp body, Temp_label brk);
Tr_exp Tr_forExp(Tr_exp var, Tr_exp low, Tr_exp high, Tr_exp body, Temp_label brk);
Tr_exp Tr_ifExp(Tr_exp cond, Tr_exp then, Tr_exp els);
Tr_exp Tr_arrayExp(Tr_exp elem, Tr_exp capacity);
Tr_exp Tr_recordExp(Tr_expseq fields);
Tr_exp Tr_simpleVar(Tr_access access, Tr_level level);
Tr_exp Tr_arrayVar(Tr_exp array, Tr_exp index);
Tr_exp Tr_fieldVar(Tr_exp record, int offset);
Tr_exp Tr_callExp(Tr_level caller, Tr_level callee, Temp_label label, Tr_expseq argv);

Tr_level Tr_outermost();
Tr_level Tr_newLevel(Tr_level parent, Temp_label name, U_boolList formals);

Tr_access Tr_accessListHead(Tr_accessList list);
Tr_accessList Tr_accessListTail(Tr_accessList list);
Tr_accessList Tr_formals(Tr_level level);
Tr_access Tr_allocLocal(Tr_level level, bool escape);

void Tr_printTree(Tr_exp exp);

#endif
