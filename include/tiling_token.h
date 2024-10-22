#ifndef TILING_TOKEN_H_
#define TILING_TOKEN_H_
#include "temp.h"
#include "tree_tiling.h"

typedef struct Tt_token_ *Tt_token;
typedef struct Tt_tokenList_ *Tt_tokenList;

typedef union
{
  Temp_label label;
  Temp_label name;
  Temp_temp temp;
  int constValue;
} Tt_tokenValue;

struct Tt_token_
{
  Tt_token_kind_t kind;
  Tt_tokenValue value;
};

struct Tt_tokenList_
{
  Tt_token head;
  Tt_tokenList tail;
};

Tt_token Tt_Token(Tt_token_kind_t kind, Tt_tokenValue value);
Tt_tokenList Tt_TokenList(Tt_token head, Tt_tokenList tail);
Tt_tokenValue Tt_TokenValueLabel(Temp_label label);
Tt_tokenValue Tt_TokenValueName(Temp_label name);
Tt_tokenValue Tt_TokenValueTemp(Temp_temp temp);
Tt_tokenValue Tt_TokenValueConst(int constValue);

#endif
