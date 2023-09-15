#include "tuple.h"
#include "utils.h"

Tuple_2 mkTuple_2(void *e1, void *e2)
{
  Tuple_2 p = _malloc(sizeof(*p));
  p->e1 = e1;
  p->e2 = e2;
  return p;
}
