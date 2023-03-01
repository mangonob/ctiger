#include "escape.h"
#include "utils.h"
#include "table.h"

static void traverseExp(S_table env, int depth, A_exp exp);

static void traverseDec(S_table env, int depth, A_dec dec);

static void traverseVar(S_table env, int depth, A_var var);

void Esc_findEscape(A_exp exp)
{
  S_table env = S_empty();
  traverseExp(env, 0, exp);
}

Esc_escapeEntry Esc_EscapeEntry(int depth, bool *escape)
{
  Esc_escapeEntry p = _malloc(sizeof(*p));
  p->depth = depth;
  p->escape = escape;
  return p;
}

static void traverseExp(S_table env, int depth, A_exp exp)
{
  // TODO: traverse expression
}

static void traverseDec(S_table env, int depth, A_dec dec)
{
  // TODO: traverse declaration
}

static void traverseVar(S_table env, int depth, A_var var)
{
  // TODO: traverse variable
}