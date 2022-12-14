#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"
#include "parser.h"
#include "print_absyn.h"

extern int yyparse(FILE *input);
extern A_exp parser_root;

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
  printExp(parser_root);
}

void usage()
{
  printf("usage: tiger filename\n");
  exit(0);
}