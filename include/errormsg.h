#ifndef ERROR_MSG_H_
#define ERROR_MSG_H_
#include "absyn.h"

enum Error
{
  Semant_Error = 1025,
};

_Noreturn void SM_Error(A_Pos pos, const char *msg, ...);

#endif
