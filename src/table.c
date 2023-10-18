#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "table.h"
#include "utils.h"

static binder Binder(void *key, void *value, binder next, void *prevtop)
{
  binder p = _malloc(sizeof(*p));
  p->key = key;
  p->value = value;
  p->next = next;
  p->prevtop = prevtop;
  return p;
}

TAB_table TAB_empty()
{
  TAB_table p = _malloc(sizeof(*p));
  p->top = NULL;
  memset(p->table, 0, sizeof(p->table));
  return p;
}

void TAB_push(TAB_table t, void *key, void *value)
{
  assert(t && key);
  uintptr_t index;
  index = ((uintptr_t)key) % TABLE_SIZE;
  t->table[index] = Binder(key, value, t->table[index], t->top);
  t->top = key;
}

void *TAB_lookup(TAB_table t, void *key)
{
  assert(t && key);
  binder curr;
  uintptr_t index = ((uintptr_t)key) % TABLE_SIZE;

  for (curr = t->table[index]; curr; curr = curr->next)
    if (curr->key == key)
      return curr->value;

  return NULL;
}

void *TAB_pop(TAB_table t)
{
  assert(t);
  void *key = t->top;
  assert(key);
  uintptr_t index = ((uintptr_t)key) % TABLE_SIZE;
  binder b = t->table[index];
  assert(b);
  t->table[index] = b->next;
  t->top = b->prevtop;
  return b->key;
}

void TAB_dump(FILE *out, TAB_table t, void (*show)(FILE *out, void *key, void *value))
{
  void *key = t->top;
  uintptr_t index = ((uintptr_t)key) % TABLE_SIZE;
  binder b = t->table[index];

  if (b != NULL)
  {
    t->table[index] = b->next;
    t->top = b->prevtop;
    show(out, b->key, b->value);
    TAB_dump(out, t, show);
    assert(t->top == b->prevtop && t->table[index] == b->next);
    t->top = key;
    t->table[index] = b;
  }
}
