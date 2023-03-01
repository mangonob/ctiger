#ifndef FRAME_H_
#define FRAME_H_
#include "temp.h"
#include "utils.h"

typedef struct F_frame_ *F_frame;
typedef struct F_access_ *F_access;

typedef struct F_accessList_ *F_accessList;
struct F_accessList_
{
  F_access head;
  F_accessList *tail;
};

F_frame F_newFrame(Temp_label name, U_boolList formals);
Temp_label F_name(F_frame f);
F_access F_staticLink();

/** Register */
Temp_temp F_FP();
Temp_temp F_RA();
Temp_temp F_RV();
Temp_temp F_SP();
Temp_temp F_ZERO();
Temp_temp F_SN(int i);
Temp_temp F_TN(int i);
Temp_temp F_AN(int i);
Temp_temp F_VN(int i);

#endif
