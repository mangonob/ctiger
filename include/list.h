#ifndef LIST_H_
#define LIST_H_
#include <stdio.h>

#define mkList(...) _mkList(__VA_ARGS__, NULL)

typedef struct List_list_ *List_list;
struct List_list_
{
  void *head;
  List_list tail;
};

List_list List_List(void *head, List_list tail);
List_list List_dump(List_list list);
List_list List_reversed(List_list list);
List_list List_concat(List_list l1, List_list l2);
List_list List_concated(List_list l1, List_list l2);
int List_length(List_list list);

void List_show(FILE *out, List_list l, void show(FILE *, void *));
List_list _mkList(void *head, ...);

#endif
