#include <stdio.h>
#include "absyn.h"
#include "parser.h"

extern int yyparse(FILE *input);

extern YYSTYPE yylval;

int main(int argc, char *argv[])
{
  FILE *input = fopen("testcases/test1.tig", "r");
  yyparse(input);
  return 0;
}