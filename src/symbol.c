#include "symbol.h"
#include "utils.h"

S_symbol S_Symbol(string name)
{
  S_symbol s = _malloc(sizeof(*s));
  return s;
}
