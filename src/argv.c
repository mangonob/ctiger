#include <stdio.h>
#include <string.h>
#include "argv.h"

C_strList C_StrList(string head, C_strList tail)
{
  C_strList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

bool C_StrListContain(C_strList list, string str)
{
  return list && (strcmp(list->head, str) == 0 || C_StrListContain(list->tail, str));
}

int C_StrLength(C_strList list)
{
  return list ? C_StrLength(list->tail) + 1 : 0;
}

Arg_result Arg_Result(C_strList nonamed, C_strList names, S_table named)
{
  Arg_result p = _malloc(sizeof(*p));
  p->nonamed = nonamed;
  p->names = names;
  p->named = named;
  return p;
}

bool hasPrefix(string str, string prefix)
{
  return str && prefix && strstr(str, prefix) == str;
}

Arg_result parse_argv(int argc, char *argv[])
{
  Arg_result result = Arg_Result(NULL, NULL, S_empty());

  for (int i = 1; i < argc; ++i)
  {
    char *arg = argv[i];
    if (hasPrefix(arg, "--"))
    {
      char *s = arg + 2;
      while (*s && *s != '=')
        s++;
      char *name = strndup(arg, s - arg);
      result->names = C_StrList(name, result->names);
      if (*s)
        S_insert(result->named, S_Symbol(name), strdup(++s));
      else
        S_insert(result->named, S_Symbol(name), "");
    }
    else if (hasPrefix(arg, "-"))
    {
      char *name = strdup(arg + 1);
      char *next = argv[i + 1];
      result->names = C_StrList(name, result->names);

      if (i + 1 >= argc || hasPrefix(next, "-"))
      {
        S_insert(result->named, S_Symbol(name), "");
      }
      else
      {
        i++;
        S_insert(result->named, S_Symbol(name), next);
      }
    }
    else
    {
      result->nonamed = C_StrList(arg, result->nonamed);
    }
  }

  return result;
}
