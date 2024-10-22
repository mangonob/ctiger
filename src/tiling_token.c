#include "utils.h"
#include "tiling_token.h"

Tt_token Tt_Token(Tt_token_kind_t kind, Tt_tokenValue value)
{
  Tt_token p = _malloc(sizeof(*p));
  p->kind = kind;
  p->value = value;
  return p;
}

Tt_tokenList Tt_TokenList(Tt_token head, Tt_tokenList tail)
{
  Tt_tokenList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

Tt_tokenValue Tt_TokenValueLabel(Temp_label label)
{
  Tt_tokenValue t;
  t.label = label;
  return t;
}

Tt_tokenValue Tt_TokenValueName(Temp_label name)
{
  Tt_tokenValue t;
  t.name = name;
  return t;
}

Tt_tokenValue Tt_TokenValueTemp(Temp_temp temp)
{
  Tt_tokenValue t;
  t.temp = temp;
  return t;
}

Tt_tokenValue Tt_TokenValueConst(int constValue)
{
  Tt_tokenValue t;
  t.constValue = constValue;
  return t;
}
