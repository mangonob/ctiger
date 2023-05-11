#include <stdio.h>
#include <assert.h>
#include "temp.h"
#include "table.h"
#include "utils.h"

struct Temp_map_
{
  TAB_table tab;
  Temp_map under;
};

Temp_temp Temp_newtemp(void)
{
  static int temps = 100;
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

Temp_label Temp_newLabel()
{
  static int labels = 0;
  char buf[100];
  sprintf(buf, "L%d", labels++);
  return Temp_namedLabel(String(buf));
}

Temp_label Temp_namedLabel(string name)
{
  return S_Symbol(name);
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
