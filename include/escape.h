#ifndef ESCAPE_H_
#define ESCAPE_H_
#include <stdbool.h>
#include "absyn.h"

void Esc_findEscape(A_exp exp);

typedef struct Esc_escapeEntry_ *Esc_escapeEntry;
struct Esc_escapeEntry_
{
  int depth;
  bool *escape;
};
Esc_escapeEntry Esc_EscapeEntry(int depth, bool *escape);

#endif