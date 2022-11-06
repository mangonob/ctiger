#include "symbol.h"
#include "absyn.h"

S_symbol S_Symbol(char *sym)
{
  S_symbol s = _malloc(sizeof(*s));
  s->sym = sym;
  return s;
}
