#ifndef FRAME_H_
#define FRAME_H_
#include <stdbool.h>
#include "temp.h"
#include "utils.h"
#include "tree.h"
#include "symbol.h"
#include "assem.h"

typedef struct F_frame_ *F_frame;
typedef struct F_access_ *F_access;

typedef struct F_accessList_ *F_accessList;
struct F_accessList_
{
  F_access head;
  F_accessList tail;
};

typedef struct F_frag_ *F_frag;
struct F_frag_
{
  enum
  {
    F_stringFrag,
    F_procFrag
  } kind;
  union
  {
    struct
    {
      Temp_label label;
      string str;
    } stringg;
    struct
    {
      T_stm body;
      F_frame frame;
    } proc;
  };
};

F_frag F_StringFrag(Temp_label label, string str);
F_frag F_ProcFrag(T_stm body, F_frame frame);

typedef struct F_fragList_ *F_fragList;
struct F_fragList_
{
  F_frag head;
  F_fragList tail;
};
F_fragList F_FragList(F_frag head, F_fragList tail);

F_frame F_newFrame(Temp_label name, U_boolList formalEscapes);
Temp_label F_name(F_frame f);
F_accessList F_formals(F_frame f);
int F_accessOffset(F_access f);
F_accessList F_AccessList(F_access head, F_accessList tail);
F_accessList F_AccessListReversed(F_accessList list);
F_access F_allocLocal(F_frame f, bool escape);
F_access F_staticLink();

/** Registers */

/** Frame pointer */
Temp_temp F_FP();
/** Return addresss */
Temp_temp F_RA();
/** Return value */
Temp_temp F_RV();
/** Stack pointer */
Temp_temp F_SP();
/** Constant zero */
Temp_temp F_ZERO();
/** Generic register */
Temp_temp F_XN(int i);

Temp_tempList F_callersaves();
Temp_tempList F_calleesaves();
Temp_tempList F_registers();

Temp_map F_initialRegisters(F_frame f);

/** The mapping of special registers and thier names */
Temp_map F_tempMap(void);

typedef enum
{
  specialregs = 0,
  argregs,
  calleesaves,
  callersaves
} RL_Type;
Temp_tempList F_getRegList(RL_Type type);

extern const int F_wordSize;
T_exp F_Exp(F_access acc, T_exp framePtr);
T_exp F_externalCall(string s, T_expList args);

T_stm F_procEntryExit1(F_frame frame, T_stm stm);
AS_instrList F_procEntryExit2(F_frame frame, AS_instrList body);
AS_proc F_procEntryExit3(F_frame frame, AS_instrList body);

#endif
