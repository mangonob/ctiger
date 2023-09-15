#ifndef ARGV_H_
#define ARGV_H_
#include <stdbool.h>
#include "utils.h"
#include "symbol.h"
#include "table.h"

typedef struct C_strList_ *C_strList;
struct C_strList_
{
  string head;
  C_strList tail;
};

C_strList C_StrList(string head, C_strList tail);

typedef struct Arg_result_ *Arg_result;
struct Arg_result_
{
  C_strList nonamed;
  C_strList names;
  S_table named;
};

bool C_StrListContain(C_strList list, string str);
int C_StrLength(C_strList list);

Arg_result Arg_Result(C_strList nonamed, C_strList names, S_table named);

Arg_result parse_argv(int argc, char *argv[]);

#endif
