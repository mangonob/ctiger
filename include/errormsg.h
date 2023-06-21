#ifndef ERROR_MSG_H_
#define ERROR_MSG_H_
#include "absyn.h"

_Noreturn void EM_Error(A_Pos pos, const char *msg, ...);

#endif
