#include <stdbool.h>
#include <string.h>
#include "symbol.h"
#include "utils.h"

#define SIZE 109
static S_symbol hashtable[SIZE];

static unsigned int hash(char *s0)
{
  unsigned int h = 0;
  char *s;

  for (s = s0; *s; s++)
    h = h * 65599 + *s;

  return h;
}

static bool streq(string s1, string s2)
{
  return !strcmp(s1, s2);
}

static S_symbol mkSymbol(string name, S_symbol next)
{
  S_symbol s = _malloc(sizeof(*s));
  s->name = name;
  s->next = next;
  return s;
}

S_symbol S_Symbol(string name)
{
  int index = hash(name) % SIZE;
  S_symbol syms = hashtable[index], sym;

  for (sym = syms; sym; sym = sym->next)
    if (streq(sym->name, name))
      return sym;

  sym = mkSymbol(name, syms);
  hashtable[index] = sym;
  return sym;
}

string S_name(S_symbol sym)
{
  return sym->name;
}

S_table S_empty()
{
  return TAB_empty();
}

void S_insert(S_table t, S_symbol sym, void *value)
{
  TAB_push(t, sym, value);
}

void *S_lookup(S_table t, S_symbol sym)
{
  return TAB_lookup(t, sym);
}

static struct S_symbol_ marksym = (struct S_symbol_){.name = NULL, .next = NULL};

void S_beginScope(S_table t)
{
  S_insert(t, &marksym, NULL);
}

void S_endScope(S_table t)
{
  for (S_symbol s = TAB_pop(t); s != &marksym; s = TAB_pop(t))
    ;
}

void S_dump(FILE *out, S_table t, void (*show)(FILE *out, S_symbol sym, void *binding))
{
  TAB_dump(out, t, (void (*)(FILE *, void *, void *))show);
}
