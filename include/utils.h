#ifndef UTILS_HEADER__
#define UTILS_HEADER__
#include <stddef.h>
#include <stdbool.h>

#ifdef __APPLE__
#include <malloc/malloc.h>
#define msize(ptr) malloc_size((const void *)(ptr))
#elif defined __linux__
#include <malloc.h>
#define msize(ptr) malloc_usable_size((void *)(ptr))
#else
#error msize is not implemented on this platform
#endif

#define mkStrings(...) _mkStrings(__VA_ARGS__, NULL)

void *_malloc(size_t byte);

typedef struct U_boolList_ *U_boolList;
struct U_boolList_
{
  bool head;
  U_boolList tail;
};

typedef char *string;

string String(char *s);
string Format(char *fmt, ...);
string _mkStrings(string s, ...);

/** Construct a bool list */
U_boolList U_BoolList(bool head, U_boolList tail);
U_boolList U_BoolListReversed(U_boolList blist);

_Noreturn void fatalError(char *msg);

_Noreturn void notImplementation();

typedef enum
{
  TINT_BLACK,
  TINT_RED,
  TINT_GREEN,
  TINT_YELLOW,
  TINT_BLUE,
  TINT_PURPLE,
  TINT_CYAN,
  TINT_WHITE,
} TintColor;

char *tintString(char *input, TintColor color);

char *tintDanger(char *input);
char *tintWarning(char *input);
char *tintSuccess(char *input);
char *tintInfo(char *input);

void startTimeline(string label);
void endTimeline();

double *Double(double d);

#endif
