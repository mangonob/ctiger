#include <stdio.h>

typedef struct
{
  int a;
  int b;
} Struc;

void foo(Struc s);

int main(int argc, char *argv[])
{
  Struc s1 = {1, 2};
  foo(s1);
  printf("%d, %d\n", s1.a, s1.b);
  return 0;
}

void foo(Struc s)
{
  s.a += 1;
  s.b += 1;
}