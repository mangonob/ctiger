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
#include "flowgraph.h"
#include "argv.h"
#define TRACE
#define CODEGEN

#ifdef CODEGEN
#include "codegen.h"
#endif

extern int yyparse(FILE *input);
extern A_exp tgroot;

typedef enum
{
  PS_CODE_GEN,
  PS_FLOW,
} ProcStep;

void doProc(FILE *out, F_frame frame, T_stm body, ProcStep step)
{
  T_stmList linear = C_linearize(body);
  C_block block = C_basicBlocks(linear);
  T_stmList trace = C_traceSchedule(block);
  AS_instrList iList = F_codegen(frame, trace);

  iList = F_procEntryExit2(frame, iList);
  AS_proc proc = F_procEntryExit3(frame, iList);

  switch (step)
  {
  case PS_CODE_GEN:
    fprintf(out, "%s\n", proc->prolog);
    AS_printInstrList(out, proc->body, F_initialRegisters(frame));
    fprintf(out, "%s\n", proc->epilog);
    break;
  case PS_FLOW:
  {
    G_graph fg = FG_AssemFlowGraph(proc->body);
    FG_show(out, fg, proc->body, F_initialRegisters(frame));
    break;
  }
  }
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

void usage()
{
  printf("usage: tigerc [-o <output>] [-f|--flow] [filename]\n");
  exit(0);
}

int main(int argc, char *argv[])
{
  Arg_result argresult = parse_argv(argc, argv);
  bool showHelp = S_lookup(argresult->named, S_Symbol("h")) != NULL || S_lookup(argresult->named, S_Symbol("help")) != NULL;

  if (C_StrLength(argresult->nonamed) > 1 || showHelp)
    usage();

  bool has_input = argresult->nonamed;
  string input_filename = has_input ? argresult->nonamed->head : NULL;
  string output_filename = S_lookup(argresult->named, S_Symbol("o"));
  output_filename = output_filename ? output_filename : S_lookup(argresult->named, S_Symbol("output"));
  bool isBuildFlow = S_lookup(argresult->named, S_Symbol("f")) != NULL || S_lookup(argresult->named, S_Symbol("flow")) != NULL;
  ProcStep step = isBuildFlow ? PS_FLOW : PS_CODE_GEN;

  FILE *input = NULL;
  FILE *output = NULL;

  if (input_filename)
  {
    FILE *f = fopen(input_filename, "r");
    if (!f)
    {
      fprintf(stderr, "cannot open file %s.\n", input_filename);
      exit(1);
    }
    input = f;
  }
  else
  {
    input = stdin;
  }

  if (output_filename)
  {
    FILE *f = fopen(output_filename, "w+");
    if (!f)
    {
      fprintf(stderr, "cannot open file %s.\n", output_filename);
      exit(1);
    }
    output = f;
  }
  else
  {
    output = stdout;
  }

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
      doStr(output, frag->stringg.str, frag->stringg.label);
      break;
    case F_procFrag:
      doProc(output, frag->proc.frame, frag->proc.body, step);
      break;
    }
  }

  if (input != stdin)
    fclose(input);
  if (output != stdout)
    fclose(output);

  exit(0);
}
