#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

void *_malloc(size_t byte)
{
  void *p = malloc(byte);

  if (!p)
  {
    fprintf(stderr, "bad memory allocation");
    exit(1);
  }
  else
    return p;
}

string String(char *s)
{
  string p = _malloc(strlen(s) + 1);
  strcpy(p, s);
  return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{
  U_boolList p = _malloc(sizeof(*p));
  return p;
}

_Noreturn void fatalError(char *msg)
{
  if (msg)
    fprintf(stderr, "%s", msg);

  assert(false);
}

_Noreturn void notImplementation()
{
  fatalError("not implementation");
}