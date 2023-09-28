#include <stdarg.h>
#include "list.h"
#include "utils.h"

List_list List_List(void *head, List_list tail)
{
  List_list p = _malloc(sizeof(*p));
  p->head = head;
  p->tail = tail;
  return p;
}

List_list List_dump(List_list list)
{
  List_list r = NULL;
  List_list last = NULL;
  for (; list; list = list->tail)
  {
    List_list n = List_List(list->head, NULL);
    if (r)
      last = last->tail = n;
    else
      r = last = n;
  }
  return r;
}

List_list List_reversed(List_list list)
{
  List_list r = NULL;
  for (; list; list = list->tail)
    r = List_List(list->head, r);
  return r;
}

List_list List_concat(List_list l1, List_list l2)
{
  if (!l2)
    return l1;

  if (!l1)
    return l2;

  List_list last = NULL;
  for (List_list l = l1; l; l = l->tail)
    last = l;

  last->tail = l2;
  return l1;
}

void *List_top(List_list list)
{
  return list ? list->head : NULL;
}

void List_push(List_list *list, void *top)
{
  *list = List_List(top, *list);
}

void *List_pop(List_list *list)
{
  void *top = List_top(*list);
  if (*list)
    *list = (*list)->tail;
  return top;
}

List_list List_concated(List_list l1, List_list l2)
{
  return List_concat(List_dump(l1), List_dump(l2));
}

int List_length(List_list list)
{
  int l = 0;
  for (; list; list = list->tail)
    l++;
  return l;
}

void List_show(FILE *out, List_list l, void show(FILE *, void *))
{
  fprintf(out, "[");

  for (; l; l = l->tail)
  {
    show(out, l->head);
    if (l->tail)
      fprintf(out, ", ");
  }

  fprintf(out, "]");
}

List_list _mkList(void *head, ...)
{
  if (!head)
    return NULL;

  va_list args;
  va_start(args, head);
  List_list l = List_List(head, NULL);
  List_list curr = l;
  for (void *next = va_arg(args, void *); next; next = va_arg(args, void *))
  {
    curr->tail = List_List(next, NULL);
    curr = curr->tail;
  }
  va_end(args);

  return l;
}
