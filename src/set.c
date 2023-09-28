#include <string.h>
#include <assert.h>
#include "set.h"
#include "utils.h"

#define SET_SIZE 127

typedef struct node_ *node;
struct node_
{
  void *v;
  node prev;
  node next;
};

static node Node(void *v, node prev, node next)
{
  node p = _malloc(sizeof(*p));
  p->v = v;
  p->prev = prev;
  p->next = next;
  return p;
}

struct SET_set_
{
  List_list table[SET_SIZE];
  node head;
  int size;
};

static uintptr_t hash(void *p)
{
  return ((uintptr_t)p) % SET_SIZE;
}

SET_set SET_empty(void)
{
  SET_set p = _malloc(sizeof(*p));
  memset(p->table, 0, sizeof(p->table));
  p->head = NULL;
  p->size = 0;
  return p;
}

bool SET_isEmpty(SET_set s)
{
  return s->head == NULL;
}

bool SET_contains(SET_set s, void *v)
{
  uintptr_t key = hash(v);
  List_list vl = s->table[key];

  for (; vl; vl = vl->tail)
    if (((node)vl->head)->v == v)
      return true;

  return false;
}

void nodeInsert(node *head_ptr, node n)
{
  if (!n)
    return;

  if (*head_ptr)
  {
    n->next = (*head_ptr);
    n->prev = (*head_ptr)->prev;
    n->next->prev = n;
    n->prev->next = n;
  }
  else
  {
    n->prev = n->next = n;
  }

  *head_ptr = n;
}

void nodeRemove(node *head_ptr, node n)
{
  if (*head_ptr == NULL || n == NULL)
  {
    return;
  }
  else if (n == n->prev)
  {
    *head_ptr = NULL;
  }
  else
  {
    n->prev->next = n->next;
    n->next->prev = n->prev;

    if (n == *head_ptr)
      *head_ptr = n->next;
  }
}

bool SET_enter(SET_set s, void *v)
{
  if (SET_contains(s, v))
    return false;

  node n = Node(v, NULL, NULL);
  nodeInsert(&s->head, n);

  uintptr_t key = hash(v);
  List_list vl = s->table[key];
  vl = List_List(n, vl);
  s->table[key] = vl;

  s->size++;
  return true;
}

bool SET_remove(SET_set s, void *v)
{
  if (!SET_contains(s, v))
    return false;

  uintptr_t key = hash(v);
  List_list vl = s->table[key];
  for (List_list prev = NULL; vl; vl = vl->tail)
  {
    node n = vl->head;
    if (n->v == v)
    {
      nodeRemove(&s->head, n);
      if (prev)
      {
        prev->tail = vl->tail;
      }
      else
        s->table[key] = vl->tail;

      s->size--;
      return true;
    }
    prev = vl;
  }

  assert(false);
}

SET_set SET_copy(SET_set s)
{
  SET_set new_s = SET_empty();

  for (List_list vl = SET_elements(s); vl; vl = vl->tail)
    SET_enter(new_s, vl->head);

  return new_s;
}

void *SET_first(SET_set s)
{
  return s->head ? s->head->prev->v : NULL;
}

void *SET_last(SET_set s)
{
  return s->head ? s->head->v : NULL;
}

void *SET_pop(SET_set s)
{
  void *l = SET_last(s);
  SET_remove(s, l);
  return l;
}

void *SET_dequeue(SET_set s)
{
  void *l = SET_first(s);
  SET_remove(s, l);
  return l;
}

SET_set SET_intersection(SET_set s1, SET_set s2)
{
  SET_set s = SET_empty();

  for (List_list vl = SET_elements(s1); vl; vl = vl->tail)
    if (SET_contains(s2, vl->head))
      SET_enter(s, vl->head);

  return s;
}

void SET_intersectionWith(SET_set s1, SET_set s2)
{
  for (List_list vl = SET_elements(s1); vl; vl = vl->tail)
    if (SET_contains(s2, vl->head))
      SET_enter(s1, vl->head);
}

SET_set SET_union(SET_set s1, SET_set s2)
{
  SET_set s = SET_copy(s1);

  for (List_list vl = SET_elements(s2); vl; vl = vl->tail)
    SET_enter(s, vl->head);

  return s;
}

void SET_unionWith(SET_set s1, SET_set s2)
{
  for (List_list vl = SET_elements(s2); vl; vl = vl->tail)
    SET_enter(s1, vl->head);
}

SET_set SET_subtracting(SET_set s1, SET_set s2)
{
  SET_set s = SET_empty();

  for (List_list vl = SET_elements(s1); vl; vl = vl->tail)
    if (!SET_contains(s2, vl->head))
      SET_enter(s, vl->head);

  return s;
}

void SET_subtractingWith(SET_set s1, SET_set s2)
{
  for (List_list vl = SET_elements(s1); vl; vl = vl->tail)
    if (!SET_contains(s2, vl->head))
      SET_enter(s1, vl->head);
}

bool SET_equals(SET_set s1, SET_set s2)
{
  for (List_list vl = SET_elements(s1); vl; vl = vl->tail)
    if (!SET_contains(s2, vl->head))
      return false;

  for (List_list vl = SET_elements(s2); vl; vl = vl->tail)
    if (!SET_contains(s1, vl->head))
      return false;

  return true;
}

int SET_size(SET_set s)
{
  return s->size;
}

List_list SET_elements(SET_set s)
{
  List_list vl = NULL;
  node tail = s->head ? s->head->prev : NULL;
  for (node head = s->head; head; head = head->next)
  {
    vl = List_List(head->v, vl);
    if (head == tail)
      break;
  }
  return vl;
}

void SET_show(FILE *out, SET_set s, void show(FILE *, void *))
{
  fprintf(out, "{ ");
  for (List_list vl = SET_elements(s); vl; vl = vl->tail)
  {
    show(out, vl->head);

    if (vl->tail)
      fprintf(out, ", ");
    else
      fprintf(out, " ");
  }
  fprintf(out, "}");
}
