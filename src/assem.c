#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "assem.h"
#include "utils.h"
#include "temp.h"

AS_targets AS_Targets(Temp_labelList labels)
{
  AS_targets p = _malloc(sizeof(*p));
  p->labels = labels;
  return p;
}

AS_instr AS_Oper(string assem, Temp_tempList dst, Temp_tempList src, AS_targets jumps)
{
  AS_instr p = _malloc(sizeof(*p));
  p->kind = I_OPER;
  p->OPER.assem = assem;
  p->OPER.dst = dst;
  p->OPER.src = src;
  p->OPER.jumps = jumps;
  return p;
}

AS_instr AS_Label(string assem, Temp_label label)
{
  AS_instr p = _malloc(sizeof(*p));
  p->kind = I_LABEL;
  p->LABEL.assem = assem;
  p->LABEL.label = label;
  return p;
}

AS_instr AS_Move(string assem, Temp_tempList dst, Temp_tempList src)
{
  AS_instr p = _malloc(sizeof(*p));
  p->kind = I_MOVE;
  p->MOVE.assem = assem;
  p->MOVE.dst = dst;
  p->MOVE.src = src;
  return p;
}

AS_instr AS_Call(AS_instr oper, int formals_cnt)
{
  AS_instr p = _malloc(sizeof(*p));
  p->kind = I_CALL;
  p->CALL.oper = oper;
  p->CALL.formals_cnt = formals_cnt;
  return p;
}

Temp_temp nthTemp(Temp_tempList list, int n)
{
  assert(list);
  return n ? nthTemp(list->tail, n - 1) : list->head;
}

Temp_label nthLabel(Temp_labelList list, int n)
{
  assert(list);
  return n ? nthLabel(list->tail, n - 1) : list->head;
}

static void format(char *buff, string assem, Temp_tempList dst, Temp_tempList src, AS_targets jumps, Temp_map m)
{
  char *p = assem;

  while (p && *p != '\0')
  {
    if (*p == '`')
    {
      p++;
      switch (*(p++))
      {
      case 's':
      {
        Temp_temp t = nthTemp(src, atoi(p++));
        string s = Temp_look(m, t);
        if (!s)
          s = Format("<t%d>", t->num);
        strcpy(buff, s);
        buff += strlen(s);
        break;
      }
      case 'd':
      {
        Temp_temp t = nthTemp(dst, atoi(p++));
        string s = Temp_look(m, t);
        if (!s)
          s = Format("<t%d>", t->num);
        strcpy(buff, s);
        buff += strlen(s);
        break;
      }
      case 'j':
      {
        int n = atoi(p++);
        string s = Temp_labelstring(nthLabel(jumps->labels, n));
        strcpy(buff, s);
        buff += strlen(s);
        break;
      }
      case '`':
        *(buff++) = '`';
        break;
      default:
        assert(0);
      }
    }
    else
      *(buff++) = *(p++);
  }
  *buff = '\0';
}

void AS_print(FILE *out, AS_instr i, Temp_map m)
{
  char r[4096];
  switch (i->kind)
  {
  case I_OPER:
    format(r, i->OPER.assem, i->OPER.dst, i->OPER.src, i->OPER.jumps, m);
    fprintf(out, "%s", r);
    break;
  case I_LABEL:
    format(r, i->LABEL.assem, NULL, NULL, NULL, m);
    fprintf(out, "%s", r);
    break;
  case I_MOVE:
    format(r, i->MOVE.assem, i->MOVE.dst, i->MOVE.src, NULL, m);
    fprintf(out, "%s", r);
    break;
  case I_CALL:
    AS_print(out, i->CALL.oper, m);
    break;
  }
}

AS_instrList AS_splice(AS_instrList a, AS_instrList b)
{
  if (a)
    return AS_InstrList(a->head, AS_splice(a->tail, b));
  else
    return b ? AS_splice(AS_InstrList(b->head, NULL), b->tail) : NULL;
}

void AS_printInstrList(FILE *out, AS_instrList iList, Temp_map m)
{
  for (; iList; iList = iList->tail)
  {
    AS_instr instr = iList->head;
    if (instr->kind != I_LABEL)
      fprintf(out, "    ");
    AS_print(out, instr, m);
    fprintf(out, "\n");
  }
}

AS_instrList AS_InstrList(AS_instr head, AS_instrList tail)
{
  AS_instrList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

int AS_instrListLen(AS_instrList il)
{
  int len = 0;
  for (; il; il = il->tail)
    len++;
  return len;
}

AS_instrList mkInstrList(AS_instr head, ...)
{
  if (!head)
    return NULL;

  va_list args;
  va_start(args, head);
  AS_instrList l = AS_InstrList(head, NULL);
  AS_instrList curr = l;
  for (AS_instr next = va_arg(args, AS_instr); next; next = va_arg(args, AS_instr))
  {
    curr->tail = AS_InstrList(next, NULL);
    curr = curr->tail;
  }
  va_end(args);

  return l;
}

AS_proc AS_Proc(string prolog, AS_instrList body, string epilog)
{
  AS_proc p = _malloc(sizeof(*p));
  p->prolog = prolog;
  p->body = body;
  p->epilog = epilog;
  return p;
}

bool AS_isBranch(AS_instr instr)
{
  return instr->kind == I_OPER && strstr(instr->OPER.assem, "b ") == instr->OPER.assem;
}
