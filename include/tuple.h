#ifndef TUPLE_H_
#define TUPLE_H_

typedef struct Tuple_2_ *Tuple_2;
struct Tuple_2_
{
  void *e1;
  void *e2;
};

Tuple_2 mkTuple_2(void *e1, void *e2);

#endif
