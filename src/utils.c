#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include "table.h"
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

string Format(char *fmt, ...)
{
  va_list argv1, argv2;
  va_start(argv1, fmt);
  va_copy(argv2, argv1);
  int len = vsnprintf(NULL, 0, fmt, argv1);
  string p = _malloc(len + 1);
  vsnprintf(p, len + 1, fmt, argv2);
  va_end(argv1);
  va_end(argv2);
  return p;
}

string _mkStrings(string s, ...)
{
  int len = strlen(s);
  va_list as;
  va_start(as, s);
  for (string n = va_arg(as, string); n; n = va_arg(as, string))
    len += strlen(n);
  va_end(as);
  string r = _malloc(len + 1);

  strcpy(r, s);

  va_start(as, s);
  for (string n = va_arg(as, string); n; n = va_arg(as, string))
    strcat(r, n);
  va_end(as);
  return r;
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

typedef struct U_timeline_ *U_timeline;
struct U_timeline_
{
  string label;
  struct timeval start;
};

U_timeline U_Timeline(string label, struct timeval start)
{
  U_timeline p = _malloc(sizeof(*p));
  p->label = label;
  p->start = start;
  return p;
}

typedef struct U_timelineList_ *U_timelineList;
struct U_timelineList_
{
  U_timeline head;
  U_timelineList tail;
};

U_timelineList U_TimelineList(U_timeline head, U_timelineList tail)
{
  U_timelineList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

static U_timelineList timelines = NULL;
void startTimeline(string label)
{
  struct timeval start;
  gettimeofday(&start, NULL);
  timelines = U_TimelineList(U_Timeline(label, start), timelines);
}

void endTimeline()
{
  if (timelines)
  {
    U_timeline tl = timelines->head;
    timelines = timelines->tail;
    struct timeval start = tl->start;
    struct timeval end;
    gettimeofday(&end, NULL);

    if (end.tv_sec - start.tv_sec > 0)
      printf("%s used %.2lfs\n", tl->label, (end.tv_usec - start.tv_usec) / 1000000.0 + end.tv_sec - start.tv_sec);
    else
      printf("%s used %.2lfms\n", tl->label, (end.tv_usec - start.tv_usec) / 1000.0);
  }
}

double *Double(double d)
{
  double *p = _malloc(sizeof(*p));
  *p = d;
  return p;
}
