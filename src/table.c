#include <string.h>
#include <assert.h>
#include <stdint.h>
#include "table.h"
#include "utils.h"

#define TABLE_SIZE 127

typedef struct binder_ *binder;

struct binder_
{
  void *key;
  void *value;
  binder next;
  void *prevtop;
};

static binder Binder(void *key, void *value, binder next, void *prevtop)
{
  binder p = _malloc(sizeof(*p));
  p->key = key;
  p->value = value;
  p->next = next;
  p->prevtop = prevtop;
  return p;
}

struct TAB_table_
{
  binder TABLE[TABLE_SIZE];
  void *top;
};

TAB_table TAB_empty()
{
  TAB_table p = _malloc(sizeof(*p));
  p->top = NULL;
  memset(p->TABLE, 0, sizeof(p->TABLE));
  return p;
}

void TAB_enter(TAB_table t, void *key, void *value)
{
  assert(t && key);
  uintptr_t index;
  index = ((uintptr_t)key) % TABLE_SIZE;
  t->TABLE[index] = Binder(key, value, t->TABLE[index], t->top);
  t->top = key;
}

void *TAB_look(TAB_table t, void *key)
{
  assert(t && key);
  binder curr;
  uintptr_t index = ((uintptr_t)key) % TABLE_SIZE;

  for (curr = t->TABLE[index]; curr; curr = curr->next)
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
  binder b = t->TABLE[index];
  assert(b);
  t->TABLE[index] = b->next;
  t->top = b->prevtop;
  return b->key;
}

void TAB_dump(TAB_table t, void (*show)(void *key, void *value))
{
  void *key = t->top;
  uintptr_t index = ((uintptr_t)key) % TABLE_SIZE;
  binder b = t->TABLE[index];

  if (b != NULL)
  {
    t->TABLE[index] = b->next;
    t->top = b->prevtop;
    show(b->key, b->value);
    TAB_dump(t, show);
    assert(t->top == b->prevtop && t->TABLE[index] == b->prevtop);
    t->top = key;
    t->TABLE[index] = b;
  }
}
