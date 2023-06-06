#include <assert.h>
#include "escape.h"
#include "utils.h"
#include "table.h"

typedef struct Esc_escapeEntry_ *Esc_escapeEntry;
struct Esc_escapeEntry_
{
  int depth;
  bool *escape;
};

Esc_escapeEntry Esc_EscapeEntry(int depth, bool *escape);

static void traverseExp(S_table env, int depth, A_exp exp);

static void traverseDec(S_table env, int depth, A_dec dec);

static void traverseVar(S_table env, int depth, A_var var);

void Esc_findEscape(A_exp exp)
{
  S_table env = S_empty();
  traverseExp(env, 0, exp);
}

Esc_escapeEntry Esc_EscapeEntry(int depth, bool *escape)
{
  Esc_escapeEntry p = _malloc(sizeof(*p));
  p->depth = depth;
  p->escape = escape;
  return p;
}

static void traverseExp(S_table env, int depth, A_exp exp)
{
  switch (exp->type)
  {
  case A_intExp:
  case A_strExp:
  case A_nilExp:
    break;
  case A_varExp:
    traverseVar(env, depth, exp->var);
    break;
  case A_assignExp:
    break;
  case A_seqExp:
    break;
  case A_callExp:
  {
    A_expseq args = exp->call.args;
    for (; args && args->head; args = args->tail)
      traverseExp(env, depth, args->head);
    break;
  }
  case A_opExp:
    traverseExp(env, depth, exp->op.lhs);
    traverseExp(env, depth, exp->op.rhs);
    break;
  case A_recordExp:
  {
    A_record_list records = exp->record.record_list;
    for (; records && records->head; records = records->tail)
      traverseExp(env, depth, records->head->value);
    break;
  }
  case A_arrayExp:
    traverseExp(env, depth, exp->array.capcity);
    traverseExp(env, depth, exp->array.element);
    break;
  case A_ifExp:
    traverseExp(env, depth, exp->iff.condition);
    traverseExp(env, depth, exp->iff.then);
    if (exp->iff.els)
      traverseExp(env, depth, exp->iff.els);
    break;
  case A_whileExp:
    traverseExp(env, depth, exp->whil.condition);
    traverseExp(env, depth, exp->whil.body);
    break;
  case A_forExp:
    traverseExp(env, depth, exp->forr.from);
    traverseExp(env, depth, exp->forr.to);
    traverseExp(env, depth, exp->forr.body);
    break;
  case A_breakExp:
    break;
  case A_letExp:
  {
    A_decs decs = exp->let.decs;
    for (; decs && decs->head; decs = decs->tail)
      traverseDec(env, depth, decs->head);

    A_expseq seq = exp->let.body;
    for (; seq && seq->head; seq = seq->tail)
      traverseExp(env, depth, seq->head);

    break;
  }
  }
}

static void traverseDec(S_table env, int depth, A_dec dec)
{
  switch (dec->type)
  {
  case A_typeDec:
    break;
  case A_funcDec:
    S_beginScope(env);
    {
      A_tyfields parameters = dec->funcdec.parameters;
      for (; parameters && parameters->head; parameters = parameters->tail)
        S_insert(env, parameters->head->name->id, Esc_EscapeEntry(depth + 1, &parameters->head->escape));
      traverseExp(env, depth + 1, dec->funcdec.body);
    }
    S_endScope(env);

    break;
  case A_varDec:
    traverseExp(env, depth, dec->vardec.exp);
    S_insert(env, dec->vardec.var->id, Esc_EscapeEntry(depth, &dec->vardec.escape));
    break;
  }
}

static void traverseVar(S_table env, int depth, A_var var)
{
  switch (var->type)
  {
  case A_simpleVar:
  {
    Esc_escapeEntry entry = S_lookup(env, var->simple->id);
    if (entry && depth > entry->depth)
      *entry->escape = true;
    break;
  }
  case A_fieldVar:
    traverseVar(env, depth, var->field.var);
    break;
  case A_subscriptVar:
    traverseExp(env, depth, var->subscript.exp);
    traverseVar(env, depth, var->subscript.var);
    break;
  }
}
