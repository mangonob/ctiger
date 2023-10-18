#ifndef SET_H_
#define SET_H_
#include <stdbool.h>
#include <stdio.h>
#include "list.h"

typedef struct SET_set_ *SET_set;

SET_set SET_empty(void);
SET_set SET_singleton(void *v);
bool SET_isEmpty(SET_set s);
bool SET_contains(SET_set s, void *v);
bool SET_enter(SET_set s, void *v);
bool SET_remove(SET_set s, void *v);
List_list SET_elements(SET_set s);
SET_set SET_copy(SET_set s);
SET_set SET_map(SET_set s, void *f(void *));
void *SET_first(SET_set s);
void *SET_last(SET_set s);
void *SET_pop(SET_set s);
void *SET_dequeue(SET_set s);

SET_set SET_intersection(SET_set s1, SET_set s2);
void SET_intersectionWith(SET_set s1, SET_set s2);
SET_set SET_union(SET_set s1, SET_set s2);
void SET_unionWith(SET_set s1, SET_set s2);
SET_set SET_subtracting(SET_set s1, SET_set s2);
void SET_subtractingWith(SET_set s1, SET_set s2);

bool SET_equals(SET_set s1, SET_set s2);
int SET_size(SET_set s);
void SET_show(FILE *out, SET_set s, void show(FILE *, void *));

#endif
