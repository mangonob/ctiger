#ifndef TEMP_H_
#define TEMP_H_
#include <stdio.h>
#include "symbol.h"

typedef struct Temp_temp_ *Temp_temp;
struct Temp_temp_
{
  int num;
};

Temp_temp Temp_newtemp();

typedef struct Temp_tempList_ *Temp_tempList;
struct Temp_tempList_
{
  Temp_temp head;
  Temp_tempList tail;
};
Temp_tempList Temp_TempList(Temp_temp head, Temp_tempList tail);
int Temp_listLen(Temp_tempList list);
Temp_tempList Temp_take(Temp_tempList list, int n);
Temp_tempList Temp_drop(Temp_tempList list, int n);
Temp_tempList Temp_takeLast(Temp_tempList list, int n);
Temp_tempList mkTempList(Temp_temp head, ...);
Temp_tempList Temp_listSplice(Temp_tempList l1, Temp_tempList l2);

typedef S_symbol Temp_label;
Temp_label Temp_newLabel();
Temp_label Temp_namedLabel(string name);
Temp_label Temp_newProcLabel(string name);
string Temp_labelstring(Temp_label s);

typedef struct Temp_labelList_ *Temp_labelList;
struct Temp_labelList_
{
  Temp_label head;
  Temp_labelList tail;
};
Temp_labelList Temp_LabelList(Temp_label head, Temp_labelList tail);

typedef struct Temp_map_ *Temp_map;
Temp_map Temp_empty();
Temp_map Temp_layerMap(Temp_map over, Temp_map under);
void Temp_enter(Temp_map m, Temp_temp t, string s);
string Temp_look(Temp_map m, Temp_temp t);
void Temp_dumpMap(FILE *out, Temp_map m);

Temp_map Temp_name();

#endif
