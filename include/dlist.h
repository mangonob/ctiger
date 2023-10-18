#ifndef DLIST_H_
#define DLIST_H_
#include <stdio.h>

#define mkDList(...) _mkDList(__VA_ARGS__, NULL)

typedef struct DList_list_ *DList_list;
struct DList_list_
{
  void *v;
  DList_list prev;
  DList_list next;
};

DList_list DList_List(void *v, DList_list prev, DList_list next);
DList_list DList_dump(DList_list list);
DList_list DList_reverse(DList_list *list);
DList_list DList_reversed(DList_list list);
DList_list DList_concat(DList_list l1, DList_list l2);
DList_list DList_concated(DList_list l1, DList_list l2);
DList_list DList_find(DList_list list, void *v);
void DList_insert(DList_list *list, void *v);
void DList_append(DList_list *list, void *v);
void DList_remove(DList_list *list, void *v);
void DList_removeNode(DList_list *list, DList_list node);
DList_list DList_first(DList_list list);
DList_list DList_last(DList_list list);
void *DList_top(DList_list list);
void DList_push(DList_list list);
void *DList_pop(DList_list *list);
void DList_enqueue(DList_list *list);
void *DList_dequeue(DList_list *list);
int DList_length(DList_list list);

void DList_show(FILE *out, DList_list l, void show(FILE *, void *));
DList_list _mkDList(void *head, ...);
#endif
