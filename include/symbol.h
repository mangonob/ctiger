#ifndef SYMBOL_HEADER__
#define SYMBOL_HEADER__
#include "table.h"

typedef char *string;

typedef struct S_symbol_ *S_symbol;

struct S_symbol_
{
  string name;
  S_symbol next;
};

typedef TAB_table S_table;

S_symbol S_Symbol(string);

static S_symbol mkSymbol(string name, S_symbol next);

S_symbol S_Symbol(string name);

string S_name(S_symbol sym);

S_table S_empty();

void S_insert(S_table t, S_symbol sym, void *value);

void *S_lookup(S_table t, S_symbol sym);

void S_beginScope(S_table t);

void S_endScope(S_table t);

void S_dump(S_table t, void (*show)(S_symbol sym, void *binding));

#endif