#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "print_absyn.h"

void printExp_(A_exp exp);
void printIndent(int indent);
void printVar(A_var var);
void printDecs(A_decs decs);
void printDec(A_dec dec);
void printTyFields(A_tyfields fields);
void printTyField(A_tyfield field);
void printTy(A_ty ty);
void printExpSeq(A_expseq expseq);
void printArgList(A_expseq expseq);
void printRecordList(A_record_list records);
void printRecord(A_record record);
void printOper(A_oper oper);
void printStr(char *str);
bool is_exp_verbose(A_exp exp);

static int _indent = 0;
static bool _inline = false;
void changeLine();
void indent();
void unindent();
void useinline();
void uninline();
bool is_inline();

void printExp(A_exp exp)
{
  _indent = 0;
  _inline = false;
  printExp_(exp);
  _indent = 0;
  _inline = false;
  printf("\n");
}

void printExp_(A_exp exp)
{
  switch (exp->type)
  {
  case A_intExp:
    printf("%d", exp->int_value);
    return;
  case A_strExp:
    printStr(exp->str);
    return;
  case A_nilExp:
    printf("nil");
    break;
  case A_varExp:
    printVar(exp->var);
    break;
  case A_assignExp:
    printVar(exp->assign.var);
    printf(" := ");
    printExp_(exp->assign.exp);
    break;
  case A_seqExp:
    printf("(");
    indent();
    changeLine();
    printExpSeq(exp->seq);
    unindent();
    changeLine();
    printf(")");
    break;
  case A_callExp:
    printf("%s(", exp->call.func->id);
    useinline();
    printArgList(exp->call.args);
    uninline();
    printf(")");
    break;
  case A_opExp:
    printExp_(exp->op.lhs);
    printf(" ");
    printOper(exp->op.oper);
    printf(" ");
    printExp_(exp->op.rhs);
    break;
  case A_recordExp:
    printf("%s {", exp->record.type_id->id);
    if (exp->record.record_list)
    {
      printf(" ");
      printRecordList(exp->record.record_list);
      printf(" ");
    }
    printf("}");
    break;
  case A_arrayExp:
    printf("%s [ ", exp->array.type_id->id);
    printExp_(exp->array.capcity);
    printf(" ] of ");
    printExp_(exp->array.element);
    break;
  case A_ifExp:
    printf("if ");
    printExp_(exp->if_exp.condition);
    printf(" then");
    indent();
    changeLine();
    printExp_(exp->if_exp.body);
    unindent();

    if (exp->if_exp.els)
    {
      changeLine();
      printf("else");
      indent();
      changeLine();
      printExp_(exp->if_exp.els);
      unindent();
    }

    break;
  case A_whileExp:
    printf("while ");
    printExp_(exp->whil.condition);
    printf(" do");
    indent();
    changeLine();
    printExp_(exp->whil.body);
    unindent();
    break;
  case A_forExp:;
    printf("for %s := ", exp->forr.var->id);
    printExp_(exp->forr.from);
    printf(" to ");
    printExp_(exp->forr.to);
    printf(" do");
    if (is_exp_verbose(exp->forr.body))
    {
      indent();
      changeLine();
      printExp_(exp->forr.body);
      unindent();
    }
    else
    {
      printf(" ");
      printExp_(exp->forr.body);
    }
    break;
  case A_breakExp:
    printf("break");
    break;
  case A_letExp:
    printf("let");
    indent();
    changeLine();
    printDecs(exp->let.decs);
    unindent();
    changeLine();
    printf("in");
    indent();
    changeLine();
    printExpSeq(exp->let.body);
    unindent();
    if (exp->let.body)
      changeLine();
    printf("end");
    break;
  }
}

void printVar(A_var var)
{
  switch (var->type)
  {
  case A_simpleVar:
    printf("%s", var->simple->id);
    break;
  case A_fieldVar:
    printVar(var->field.var);
    printf(".%s", var->field.sym->id);
    break;
  case A_subscriptVar:
    printVar(var->subscript.var);
    printf("[");
    printExp_(var->subscript.exp);
    printf("]");
    break;
  }
}

void printDecs(A_decs decs)
{
  if (!decs)
    return;

  if (decs->tail)
  {
    printDecs(decs->tail);
    changeLine();
  }

  if (decs->head)
    printDec(decs->head);
}

void printDec(A_dec dec)
{
  switch (dec->type)
  {
  case A_typeDec:
    printf("type %s = ", dec->typedec.type_id->id);
    printTy(dec->typedec.ty);
    break;
  case A_varDec:
    printf("var %s ", dec->vardec.var->id);
    if (dec->vardec.type_id)
      printf(": %s ", dec->vardec.type_id->id);
    printf(":= ");
    printExp_(dec->vardec.exp);
    break;
  case A_funcDec:
    printf("function %s(", dec->funcdec.funcname->id);
    printTyFields(dec->funcdec.parameters);
    printf(") ");
    if (dec->funcdec.return_type)
    {
      printf(": %s ", dec->funcdec.return_type->id);
    }
    printf("=");
    if (is_exp_verbose(dec->funcdec.init))
    {
      indent();
      changeLine();
      printExp_(dec->funcdec.init);
      unindent();
    }
    else
    {
      printf(" ");
      printExp_(dec->funcdec.init);
    }
    break;
  }
}

void printTyFields(A_tyfields fields)
{
  if (!fields)
    return;

  if (fields->tail)
  {
    printTyFields(fields->tail);
    printf(", ");
  }

  if (fields->head)
    printTyField(fields->head);
}

void printTyField(A_tyfield field)
{
  printf("%s : %s", field->name->id, field->type_id->id);
}

void printTy(A_ty ty)
{
  switch (ty->type)
  {
  case A_namedTy:
    printf("%s", ty->named->id);
    break;
  case A_arrayTy:
    printf("array of %s", ty->array->id);
    break;
  case A_recordTy:
    printf("{");
    printTyFields(ty->fields);
    printf("}");
    break;
  }
}

void printExpSeq(A_expseq expseq)
{
  if (!expseq)
    return;

  if (expseq->tail)
  {
    printExpSeq(expseq->tail);
    printf(";");
    changeLine();
  }

  if (expseq->head)
    printExp_(expseq->head);
}

void printArgList(A_expseq expseq)
{
  if (!expseq)
    return;

  if (expseq->tail)
  {
    printExpSeq(expseq->tail);
    printf(", ");
  }

  if (expseq->head)
    printExp_(expseq->head);
}

void printRecordList(A_record_list records)
{
  if (!records)
    return;

  if (records->tail)
  {
    printRecordList(records->tail);
    printf(", ");
  }

  if (records->head)
    printRecord(records->head);
}

void printRecord(A_record record)
{
  printf("%s = ", record->name->id);
  printExp_(record->value);
}

void printOper(A_oper oper)
{
  switch (oper)
  {
  case A_plusOp:
    printf("+");
    break;
  case A_minusOp:
    printf("-");
    break;
  case A_timesOp:
    printf("*");
    break;
  case A_divideOp:
    printf("/");
    break;
  case A_eqOp:
    printf("=");
    break;
  case A_neqOp:
    printf("<>");
    break;
  case A_ltOp:
    printf("<");
    break;
  case A_leOp:
    printf("<=");
    break;
  case A_gtOp:
    printf(">");
    break;
  case A_geOp:
    printf("<=");
    break;
  case A_andOp:
    printf("&");
    break;
  case A_orOp:
    printf("|");
    break;
  }
}

void changeLine()
{
  if (is_inline())
  {
    printf(" ");
  }
  else
  {
    printf("\n");

    for (int i = 0; i < _indent; ++i)
      printf("|   ");
  }
}

void indent()
{
  _indent += 1;
}

void unindent()
{
  _indent -= 1;
}

void useinline()
{
  _inline = true;
}

void uninline()
{
  _inline = false;
}

bool is_inline()
{
  return _inline;
}

void printStr(char *str)
{
  const char *escaped_map[][2] = {
      {"\n", "\\n"},
      {"\a", "\\a"},
      {"\b", "\\b"},
      {"\f", "\\f"},
      {"\n", "\\n"},
      {"\r", "\\r"},
      {"\t", "\\t"},
      {"\v", "\\v"},
      {"\\", "\\\\"},
      {"\'", "\\\'"},
      {"\"", "\\\""},
      {"\0", "\\0"},
  };

  const int total_escaped = sizeof(escaped_map) / sizeof(escaped_map[0]);
  int str_length = strlen(str);

  putchar('\"');

  for (int i = 0; i < str_length; ++i)
  {
    char ch = str[i];
    bool is_escaped = false;
    for (int j = 0; j < total_escaped; ++j)
    {
      const char unescaped = escaped_map[j][0][0];
      const char *escaped = escaped_map[j][1];
      if (ch == unescaped)
      {
        printf("%s", escaped);
        is_escaped = true;
        break;
      }
    }
    if (!is_escaped)
      putchar(ch);
  }

  putchar('\"');
}

bool is_exp_verbose(A_exp exp)
{
  switch (exp->type)
  {
  case A_intExp:
  case A_strExp:
  case A_nilExp:
  case A_varExp:
  case A_assignExp:
  case A_opExp:
  case A_breakExp:
    return false;
  case A_seqExp:
  case A_callExp:
  case A_recordExp:
  case A_arrayExp:
  case A_ifExp:
  case A_whileExp:
  case A_forExp:
  case A_letExp:
    return true;
  }
}