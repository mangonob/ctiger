#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

void *_malloc(size_t byte)
{
  void *p = malloc(byte);

  if (!p)
  {
    fprintf(stderr, "bad memory allocation");
    exit(1);
  }
  else
    return p;
}

string String(char *s)
{
  string p = _malloc(strlen(s) + 1);
  strcpy(p, s);
  return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{
  U_boolList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

U_boolList U_BoolListReversed(U_boolList blist)
{
  U_boolList r = NULL;
  for (; blist; blist = blist->tail)
    r = U_BoolList(blist->head, r);
  return r;
}

_Noreturn void fatalError(char *msg)
{
  if (msg)
    fprintf(stderr, "%s\n", msg);

  exit(1);
}

/// Mark a function as not implementation
/// @note Remove in release
_Noreturn void notImplementation()
{
  fatalError("not implementation");
}

// ANSI escape code
static const char *ANSI_RESET = "\033[0m";
static const char *ANSI_BLACK = "\033[30m";
static const char *ANSI_RED = "\033[31m";
static const char *ANSI_GREEN = "\033[32m";
static const char *ANSI_YELLOW = "\033[33m";
static const char *ANSI_BLUE = "\033[34m";
static const char *ANSI_PURPLE = "\033[35m";
static const char *ANSI_CYAN = "\033[36m";
static const char *ANSI_WHITE = "\033[37m";

char *tintString(char *input, TintColor color)
{

  const char *escape;

  switch (color)
  {
  case TINT_BLACK:
    escape = ANSI_BLACK;
    break;
  case TINT_RED:
    escape = ANSI_RED;
    break;
  case TINT_GREEN:
    escape = ANSI_GREEN;
    break;
  case TINT_YELLOW:
    escape = ANSI_YELLOW;
    break;
  case TINT_BLUE:
    escape = ANSI_BLUE;
    break;
  case TINT_PURPLE:
    escape = ANSI_PURPLE;
    break;
  case TINT_CYAN:
    escape = ANSI_CYAN;
    break;
  case TINT_WHITE:
    escape = ANSI_WHITE;
    break;
  }

  if (escape)
  {
    char *output = _malloc(strlen(input) + 10);
    sprintf(output, "%s%s%s", escape, input, ANSI_RESET);
    return output;
  }
  else
    return input;
}

char *tintDanger(char *input)
{
  return tintString(input, TINT_RED);
}

char *tintWarning(char *input)
{
  return tintString(input, TINT_YELLOW);
}

char *tintSuccess(char *input)
{
  return tintString(input, TINT_GREEN);
}

char *tintInfo(char *input)
{
  return tintString(input, TINT_BLUE);
}
