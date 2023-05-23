#include <stdio.h>
#include "print_tree.h"
#define changeLineIfNeeded(depth) \
  do                              \
  {                               \
    if (!depth)                   \
      printf("\n");               \
  } while (0);

void printStmList(T_stmList stms, int depth);
void printBinOp(T_binOp binOp);
void printStm(T_stm stm, int depth);

void printTreeExp(T_exp exp, int depth)
{
  switch (exp->kind)
  {
  case T_BINOP:
    printf("BINOP(");
    printBinOp(exp->BINOP.op);
    printTreeExp(exp->BINOP.left, depth + 1);
    printf(", ");
    printTreeExp(exp->BINOP.right, depth + 1);
    printf(")");
    changeLineIfNeeded(depth);
    break;
  case T_MEM:
    printf("MEM(");
    printTreeExp(exp->MEM, depth + 1);
    printf(")");
    changeLineIfNeeded(depth);
    break;
  case T_TEMP:
    printf("TEMP(t%d)", exp->TEMP->num);
    changeLineIfNeeded(depth);
    break;
  case T_ESEQ:
    printStm(exp->ESEQ.stm, depth);
    printTreeExp(exp->ESEQ.exp, depth);
    break;
  case T_NAME:
    printf("NAME(%s)", exp->NAME->name);
    changeLineIfNeeded(depth);
    break;
  case T_CONST:
    printf("CONST(%d)", exp->CONST);
    changeLineIfNeeded(depth);
    break;
  case T_CALL:
    printf("CALL(");
    printTreeExp(exp->CALL.fun, depth + 1);
    T_expList exps = exp->CALL.args;
    for (; exps && exps->head; exps = exps->tail)
    {
      printf(", ");
      printTreeExp(exps->head, depth + 1);
    }
    printf(")");
    changeLineIfNeeded(depth);
    break;
  }
}

void printStmList(T_stmList stms, int depth)
{
  for (; stms && stms->head; stms = stms->tail)
    printStm(stms->head, depth);
}

void printRelOp(T_relOp relOp);
void printBinOp(T_binOp relOp);

void printStm(T_stm stm, int depth)
{
  switch (stm->kind)
  {
  case T_SEQ:
    printStm(stm->SEQ.left, depth);
    printStm(stm->SEQ.right, depth);
    break;
  case T_LABEL:
    printf("LABEL(%s)", stm->LABEL->name);
    changeLineIfNeeded(depth);
    break;
  case T_JUMP:
  {
    printf("JUMP(");
    printTreeExp(stm->JUMP.exp, depth + 1);
    printf(" -> ");

    Temp_labelList labels = stm->JUMP.jumps;
    for (; labels && labels->head; labels = labels->tail)
    {
      printf("%s", labels->head->name);

      if (labels->tail && labels->tail->head)
        printf(", ");
    }

    printf(")");
    changeLineIfNeeded(depth);
    break;
  }
  case T_CJUMP:
    printf("CJUMP(");
    printRelOp(stm->CJUMP.op);
    printf(", ");
    printTreeExp(stm->CJUMP.lhs, depth + 1);
    printf(", ");
    printTreeExp(stm->CJUMP.rhs, depth + 1);
    printf(", %s, %s)", stm->CJUMP.trueLabel->name, stm->CJUMP.falseLabel->name);
    changeLineIfNeeded(depth);
    break;
  case T_MOVE:
    printf("MOVE(");
    printTreeExp(stm->MOVE.dst, depth + 1);
    printf(", ");
    printTreeExp(stm->MOVE.src, depth + 1);
    printf(")");
    changeLineIfNeeded(depth);
    break;
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
    printf("T_eq");
    break;
  case T_ne:
    printf("T_ne");
    break;
  case T_lt:
    printf("T_lt");
    break;
  case T_gt:
    printf("T_gt");
    break;
  case T_le:
    printf("T_le");
    break;
  case T_ge:
    printf("T_ge");
    break;
  case T_ult:
    printf("T_ult");
    break;
  case T_ule:
    printf("T_ule");
    break;
  case T_ugt:
    printf("T_ugt");
    break;
  case T_uge:
    printf("T_uge");
    break;
  }
}

void printBinOp(T_binOp binOp)
{
  switch (binOp)
  {
  case T_plus:
    printf("T_plus");
    break;
  case T_minus:
    printf("T_minus");
    break;
  case T_mul:
    printf("T_mul");
    break;
  case T_div:
    printf("T_div");
    break;
  case T_and:
    printf("T_and");
    break;
  case T_or:
    printf("T_or");
    break;
  case T_lshift:
    printf("T_lshift");
    break;
  case T_rshift:
    printf("T_rshift");
    break;
  case T_arshift:
    printf("T_arshift");
    break;
  case T_xor:
    printf("T_xor");
    break;
  }
}
