#ifndef SYMBOL_HEADER__
#define SYMBOL_HEADER__

typedef char *string;

typedef struct S_symbol_ *S_symbol;

struct S_symbol_
{
  string name;
  S_symbol next;
};

#define SYMBOL_TABLE_SIZE 109
static S_symbol symbol_hash_table[SYMBOL_TABLE_SIZE];

#endif