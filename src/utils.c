#include <stdio.h>
#include <stdlib.h>
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