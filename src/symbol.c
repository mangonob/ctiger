#include "symbol.h"
#include "utils.h"

#define SYMBOL_TABLE_SIZE 109
static S_symbol symbol_hash_table[SYMBOL_TABLE_SIZE];

S_symbol S_Symbol(string name)
{
  S_symbol s = _malloc(sizeof(*s));
  return s;
}

unsigned int hash(char *s0)
{
  unsigned int h = 0;
  char *s;

  for (s = s0; *s; s++)
    h = h * 65599 + *s;

  return h;
}

typedef struct bucket
{
  char *key;
  void *binding;
  struct bucket *next;
} bucket;