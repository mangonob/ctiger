#ifndef __TABLE__HEADER
#define __TABLE__HEADER

#define TABLE_SIZE 127

typedef struct TAB_table_ *TAB_table;
typedef struct binder_ *binder;

struct binder_
{
  void *key;
  void *value;
  binder next;
  void *prevtop;
};

struct TAB_table_
{
  binder table[TABLE_SIZE];
  void *top;
};

static binder Binder(void *key, void *value, binder next, void *prevtop);

TAB_table TAB_empty();
void TAB_push(TAB_table t, void *key, void *value);
void *TAB_pop(TAB_table t);
void *TAB_lookup(TAB_table t, void *key);
void TAB_dump(TAB_table t, void (*show)(void *key, void *value));

#endif
