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

void doProc(FILE *out, F_frame frame, T_stm body)
{
  T_stmList linear = C_linearize(body);
  C_block block = C_basicBlocks(linear);
  T_stmList trace = C_traceSchedule(block);
  AS_instrList iList = F_codegen(frame, trace);

  iList = F_procEntryExit2(iList);
  AS_proc proc = F_procEntryExit3(frame, iList);

  fprintf(out, "%s\n", proc->prolog);
  AS_printInstrList(out, proc->body, F_initialRegisters(frame));
  fprintf(out, "%s\n", proc->epilog);
}

void doStr(FILE *out, string str, Temp_label label)
{
  fprintf(out, "%s:\n", label->name);
  fprintf(out, ".asciiz ");
  for (char *ch = str; *ch; ++ch)
  {
    fprintf(out, "%02x", *ch);
    if (*(ch + 1))
      fprintf(out, " ");
    else
      fprintf(out, "\n");
  }
}

void parse_wrap(FILE *input, FILE *out)
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
      doStr(out, frag->stringg.str, frag->stringg.label);
      break;
    case F_procFrag:
      doProc(out, frag->proc.frame, frag->proc.body);
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
    parse_wrap(test ? test : stdin, stdout);
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
    parse_wrap(input, stdout);
    fclose(input);
  }
  else
    usage();

  exit(0);
}
