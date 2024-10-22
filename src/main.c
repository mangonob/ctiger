#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
#include "liveness.h"
#include "regalloc.h"
#include "codegen.h"

extern int yyparse(FILE *input);
extern A_exp tgroot;

// TODO: [removeable]
string do_sym = NULL;
bool raw = false;

static void doProc(FILE *out, F_frame frame, T_stm body)
{
  if (do_sym && strcmp(F_name(frame)->name, do_sym) != 0)
    return;

  T_stmList linear = C_linearize(body);
  C_block block = C_basicBlocks(linear);
  T_stmList trace = C_traceSchedule(block);
  AS_instrList iList = F_codegen(frame, trace);

  RA_result ra = RA_regAlloc(frame, iList);
  iList = F_procEntryExit2(frame, ra.il);
  AS_proc proc = F_procEntryExit3(frame, iList);

  fprintf(out, "%s\n", proc->prolog);
  if (raw)
    AS_printInstrList(out, proc->body, F_initialRegisters(frame));
  else
    AS_printInstrList(out, proc->body, ra.coloring);
  fprintf(out, "%s\n", proc->epilog);
}

static void doStr(FILE *out, string str, Temp_label label)
{
  fprintf(out, "%s:\n", label->name);
  fprintf(out, ".asciiz ");
  for (char *ch = str; *ch; ++ch)
  {
    fprintf(out, "%02X", *ch);
    if (*(ch + 1))
      fprintf(out, " ");
    else
      fprintf(out, "\n");
  }
}

static void usage()
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
  if (!output_filename)
    output_filename = S_lookup(argresult->named, S_Symbol("output"));
  if (!output_filename)
    output_filename = "a.s";

  do_sym = S_lookup(argresult->named, S_Symbol("symbol"));
  raw = S_lookup(argresult->named, S_Symbol("raw")) != NULL;
  if (raw && output_filename)
    output_filename = Format("%s%s", "raw_", output_filename);

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
      doProc(output, frag->proc.frame, frag->proc.body);
      break;
    }
  }

  if (input != stdin)
    fclose(input);
  if (output != stdout)
    fclose(output);

  exit(0);
}
