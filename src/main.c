#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"
#include "parser.h"
#include "print_absyn.h"
#include "semant.h"
#include "env.h"
#include "types.h"
#include "escape.h"

extern int yyparse(FILE *input);
extern A_exp tgroot;

void usage();
void parse_wrap(FILE *input);

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    parse_wrap(stdin);
  }
  else if (argc == 2)
  {
    char *filename = argv[1];
    FILE *input = fopen(filename, "r");
    if (!input)
    {
      fprintf(stderr, "cannot open file %s\n", filename);
      exit(1);
    }
    parse_wrap(input);
    fclose(input);
  }
  else
  {
    usage();
  }

  exit(0);
}

void parse_wrap(FILE *input)
{
  if (yyparse(input))
    exit(1);

  if (0)
  {
    // print type check result
    expty exp = transExp(E_base_venv(), E_base_tenv(), tgroot);
    fprintTy(stdout, exp.ty);
    puts("");
  }
  else
  {
    // print AST
    Esc_findEscape(tgroot);
    printExp(tgroot);
  }
}

void usage()
{
  printf("usage: tigerc filename\n");
  exit(0);
}
