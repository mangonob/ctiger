#ifndef SYMBOL_HEADER__
#define SYMBOL_HEADER__

typedef char *string;

typedef struct S_symbol_ *S_symbol;

struct S_symbol_
{
  string name;
  S_symbol next;
};

S_symbol S_Symbol(string);
string S_name(S_symbol);

#endif