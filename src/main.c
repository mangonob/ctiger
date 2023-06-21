#include <stdio.h>
#include <stdlib.h>
#include "absyn.h"
#include "parser.h"
#include "print_tree.h"
#include "translate.h"
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

  Esc_findEscape(tgroot);
  F_fragList frag_list = SEM_transProg(tgroot);
  for (; frag_list; frag_list = frag_list->tail)
  {
    F_frag frag = frag_list->head;
    switch (frag->kind)
    {
    case F_stringFrag:
      printf("======== String Data ========\n");
      printf("%s:\n", frag->stringg.label->name);
      printf("%s\n", frag->stringg.str);
      break;
    case F_procFrag:
      printf("======== Procedure ========\n");
      printf("%s:\n", F_name(frag->proc.frame)->name);
      printStmList(T_StmList(frag->proc.body, NULL), 0);
      break;
    }
  }
}

void usage()
{
  printf("usage: tigerc filename\n");
  exit(0);
}
