#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "errormsg.h"

_Noreturn void EM_Error(A_Pos pos, const char *msg, ...)
{
  if (msg)
  {
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
  }

  fprintf(stderr, " (line: %d, column: %d)\n", pos.row, pos.column);
  exit(1);
}
