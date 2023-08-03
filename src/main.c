#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "absyn.h"
#include "parser.h"
#include "print_tree.h"
#include "translate.h"
#include "semant.h"
#include "env.h"
#include "types.h"
#include "escape.h"
#include "canon.h"
#define TRACE
#define CODEGEN

#ifdef CODEGEN
#include "codegen.h"
#endif

extern int yyparse(FILE *input);
extern A_exp tgroot;

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
      printf(".asciiz ");
      for (char *ch = frag->stringg.str; *ch; ++ch)
        printf("%02x ", *ch);
      printf("\n");
      break;
    case F_procFrag:
      printf("======== Procedure ========\n");
      printf("%s:\n", F_name(frag->proc.frame)->name);
      if (0)
        printStmList(T_StmList(frag->proc.body, NULL), 0);
      else
      {
        T_stmList linear = C_linearize(frag->proc.body);
        C_block block = C_basicBlocks(linear);

#ifdef TRACE
        T_stmList trace = C_traceSchedule(block);
#ifdef CODEGEN
        AS_instrList iList = F_codegen(frag->proc.frame, trace);
        AS_printInstrList(stdout, iList, Temp_empty());
#else
        printStmList(trace, 0);
#endif
#else
        C_stmListList stmLists = block.stmLists;
        for (; stmLists; stmLists = stmLists->tail)
        {
          printStmList(stmLists->head, 0);
          // separate line of block
          if (stmLists->tail)
            printf("--------------------------------\n");
        }
#endif
      }
      break;
    }
  }
}

void usage()
{
  printf("usage: tigerc filename\n");
  exit(0);
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    FILE *test = NULL;
    test = fopen("testcases/hello.tig", "r");
    parse_wrap(test ? test : stdin);
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
