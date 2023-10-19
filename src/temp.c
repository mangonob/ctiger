#include <stdio.h>
#include <assert.h>
#include <stdarg.h>
#include "temp.h"
#include "table.h"
#include "utils.h"

struct Temp_map_
{
  TAB_table tab;
  Temp_map under;
};

static int temps = 100;
Temp_temp Temp_newtemp(void)
{
  Temp_temp p = _malloc(sizeof(*p));
  p->num = temps++;
  return p;
}

Temp_tempList Temp_TempList(Temp_temp head, Temp_tempList tail)
{
  Temp_tempList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

int Temp_listLen(Temp_tempList list)
{
  int len = 0;
  for (; list; list = list->tail)
    len++;
  return len;
}

Temp_tempList Temp_take(Temp_tempList list, int n)
{
  Temp_tempList l = NULL;
  Temp_tempList last = NULL;
  for (int i = 0; i < n && list; list = list->tail, ++i)
  {
    Temp_tempList nl = Temp_TempList(list->head, NULL);
    if (l)
    {
      last = last->tail = nl;
    }
    else
    {
      l = last = nl;
    }
  }
  return l;
}

Temp_tempList Temp_drop(Temp_tempList list, int n)
{
  assert(n >= 0);

  if (n == 0)
    return list;

  for (int i = 0; i < n; ++i)
    list = list->tail;
  return list;
}

Temp_tempList Temp_takeLast(Temp_tempList list, int n)
{
  return Temp_drop(list, Temp_listLen(list) - n);
}

Temp_tempList mkTempList(Temp_temp head, ...)
{
  if (!head)
    return NULL;

  va_list args;
  va_start(args, head);
  Temp_tempList l = Temp_TempList(head, NULL);
  Temp_tempList curr = l;
  for (Temp_temp next = va_arg(args, Temp_temp); next; next = va_arg(args, Temp_temp))
  {
    curr->tail = Temp_TempList(next, NULL);
    curr = curr->tail;
  }
  va_end(args);

  return l;
}

Temp_tempList Temp_listSplice(Temp_tempList l1, Temp_tempList l2)
{
  Temp_tempList l = NULL;
  Temp_tempList last = NULL;

  for (; l1; l1 = l1->tail)
  {
    Temp_tempList n = Temp_TempList(l1->head, NULL);
    if (l)
      last = last->tail = n;
    else
      l = last = n;
  }

  for (; l2; l2 = l2->tail)
  {
    Temp_tempList n = Temp_TempList(l2->head, NULL);
    if (l)
      last = last->tail = n;
    else
      l = last = n;
  }

  return l;
}

static int labels = 0;
Temp_label Temp_newLabel()
{
  char buf[100];
  sprintf(buf, "L%d", labels++);
  return Temp_namedLabel(String(buf));
}

Temp_label Temp_namedLabel(string name)
{
  return S_Symbol(name);
}

Temp_label Temp_newProcLabel(string name)
{
  char buf[100];
  sprintf(buf, "__%s_L%d", name, labels++);
  return Temp_namedLabel(String(buf));
}

string Temp_labelstring(Temp_label s)
{
  return S_name(s);
}

Temp_labelList Temp_LabelList(Temp_label head, Temp_labelList tail)
{
  Temp_labelList p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

int Temp_labelListLen(Temp_labelList l)
{
  int len = 0;
  for (; l; l = l->tail)
    len++;
  return len;
}

Temp_map Temp_Map(TAB_table tab, Temp_map under)
{
  Temp_map p = _malloc(sizeof(*p));
  p->tab = tab;
  p->under = under;
  return p;
}

Temp_map Temp_empty()
{
  return Temp_Map(TAB_empty(), NULL);
}

Temp_map Temp_layerMap(Temp_map over, Temp_map under)
{
  if (over)
    return Temp_Map(over->tab, Temp_layerMap(over->under, under));
  else
    return under;
}

void Temp_enter(Temp_map m, Temp_temp t, string s)
{
  assert(m && m->tab);
  TAB_push(m->tab, t, s);
}

string Temp_look(Temp_map m, Temp_temp t)
{
  string s;
  assert(m && m->tab);
  s = TAB_lookup(m->tab, t);
  if (s)
    return s;
  else if (m->under)
    return Temp_look(m->under, t);
  else
    return NULL;
}

Temp_map Temp_name()
{
  static Temp_map m = NULL;
  if (!m)
    m = Temp_empty();
  return m;
}

static void show_it(FILE *out, Temp_temp t, string s)
{
  fprintf(out, "t%d -> %s\n", t->num, s);
}

void Temp_dumpMap(FILE *out, Temp_map m)
{
  TAB_dump(out, m->tab, (void (*)(FILE *out, void *, void *))show_it);
  if (m->under)
    Temp_dumpMap(out, m->under);
}
