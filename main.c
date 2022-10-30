#include <stdio.h>
#include "foo.h"

extern int FOO_MAGIC_NUMBER;

int main(int argc, char *argv[])
{
  FOO_MAGIC_NUMBER = 43;
  printf("Foo by main: %d\n", FOO_MAGIC_NUMBER);
  foo();
  return 0;
}
