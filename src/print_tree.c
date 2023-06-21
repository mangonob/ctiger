#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "print_tree.h"
#include "utils.h"
#include "errormsg.h"

void printStmList(T_stmList stms, int depth);
void printBinOp(T_binOp binOp);
void printStm(T_stm stm, int depth);

struct stream_info_
{
  FILE *stream;
  char *buff;
  size_t size;
};
typedef struct stream_info_ *stream_info;

stream_info StreamInfo()
{
  stream_info p = _malloc(sizeof(*p));
  p->stream = open_memstream(&p->buff, &p->size);
  if (!p->stream)
    fatalError("create stream failure");
  return p;
}

typedef struct stream_list_ *stream_list;
struct stream_list_
{
  stream_info head;
  stream_list tail;
};

stream_list StreamList(stream_info head, stream_list tail)
{
  stream_list p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

stream_list sl = NULL;
void pushStream()
{
  sl = StreamList(StreamInfo(), sl);
}

void popStream()
{
  if (sl->head)
  {
    stream_info info = sl->head;
    fflush(info->stream);
    printf("%s", info->buff);
    fseek(info->stream, 0, SEEK_SET);
    fclose(info->stream);
    free(info->buff);
    sl = sl->tail;
  }
}

void flushStream()
{
  for (; sl && sl->head;)
    popStream();
}

int print(char *format, ...)
{
  if (sl && sl->head)
  {
    va_list args;
    va_start(args, format);
    int r = vfprintf(sl->head->stream, format, args);
    va_end(args);
    return r;
  }
  else
    return -1;
}

void split(int depth)
{
  if (depth)
    print(", ");
  else
    print("\n");
}

void printTreeExp(T_exp exp, int depth)
{
  switch (exp->kind)
  {
  case T_BINOP:
    print("BINOP(");
    printBinOp(exp->BINOP.op);
    print(", ");
    printTreeExp(exp->BINOP.left, depth + 1);
    print(", ");
    printTreeExp(exp->BINOP.right, depth + 1);
    print(")");
    break;
  case T_MEM:
    print("MEM(");
    printTreeExp(exp->MEM, depth + 1);
    print(")");
    break;
  case T_TEMP:
    print("TEMP(t%d)", exp->TEMP->num);
    break;
  case T_ESEQ:
    pushStream();
    printStm(exp->ESEQ.stm, 0);
    split(0);
    popStream();
    printTreeExp(exp->ESEQ.exp, depth);
    break;
  case T_NAME:
    print("NAME(%s)", exp->NAME->name);
    break;
  case T_CONST:
    print("CONST(%d)", exp->CONST);
    break;
  case T_CALL:
    print("CALL(");
    printTreeExp(exp->CALL.fun, depth + 1);
    T_expList exps = exp->CALL.args;
    for (; exps && exps->head; exps = exps->tail)
    {
      print(", ");
      printTreeExp(exps->head, depth + 1);
    }
    print(")");
    break;
  }
}

void printStmList(T_stmList stms, int depth)
{
  pushStream();
  for (; stms && stms->head; stms = stms->tail)
    printStm(stms->head, depth);
  print("\n");
  popStream();
}

void printRelOp(T_relOp relOp);
void printBinOp(T_binOp relOp);

void printStm(T_stm stm, int depth)
{
  switch (stm->kind)
  {
  case T_SEQ:
    if (stm->SEQ.left)
    {
      printStm(stm->SEQ.left, depth);
      if (stm->SEQ.right)
        split(depth);
    }
    if (stm->SEQ.right)
      printStm(stm->SEQ.right, depth);
    break;
  case T_LABEL:
    if (depth == 0)
      print("%s:", stm->LABEL->name);
    else
      print("LABEL(%s)", stm->LABEL->name);
    break;
  case T_JUMP:
  {
    print("JUMP(");
    printTreeExp(stm->JUMP.exp, depth + 1);
    print(" -> ");

    Temp_labelList labels = stm->JUMP.jumps;
    for (; labels && labels->head; labels = labels->tail)
    {
      print("%s", labels->head->name);

      if (labels->tail && labels->tail->head)
        print(", ");
    }

    print(")");
    break;
  }
  case T_CJUMP:
  {
    print("CJUMP(");
    printRelOp(stm->CJUMP.op);
    print(", ");
    printTreeExp(stm->CJUMP.lhs, depth + 1);
    print(", ");
    printTreeExp(stm->CJUMP.rhs, depth + 1);
    print(", %s, %s)", stm->CJUMP.trueLabel->name, stm->CJUMP.falseLabel->name);

    break;
  }
  case T_MOVE:
  {
    print("MOVE(");
    printTreeExp(stm->MOVE.dst, depth + 1);
    print(", ");
    printTreeExp(stm->MOVE.src, depth + 1);
    print(")");
    break;
  }
  case T_EXP:
    printTreeExp(stm->EXP, depth);
    break;
  }
}

void printRelOp(T_relOp relOp)
{
  switch (relOp)
  {
  case T_eq:
    print("T_eq");
    break;
  case T_ne:
    print("T_ne");
    break;
  case T_lt:
    print("T_lt");
    break;
  case T_gt:
    print("T_gt");
    break;
  case T_le:
    print("T_le");
    break;
  case T_ge:
    print("T_ge");
    break;
  case T_ult:
    print("T_ult");
    break;
  case T_ule:
    print("T_ule");
    break;
  case T_ugt:
    print("T_ugt");
    break;
  case T_uge:
    print("T_uge");
    break;
  }
}

void printBinOp(T_binOp binOp)
{
  switch (binOp)
  {
  case T_plus:
    print("T_plus");
    break;
  case T_minus:
    print("T_minus");
    break;
  case T_mul:
    print("T_mul");
    break;
  case T_div:
    print("T_div");
    break;
  case T_and:
    print("T_and");
    break;
  case T_or:
    print("T_or");
    break;
  case T_lshift:
    print("T_lshift");
    break;
  case T_rshift:
    print("T_rshift");
    break;
  case T_arshift:
    print("T_arshift");
    break;
  case T_xor:
    print("T_xor");
    break;
  }
}
