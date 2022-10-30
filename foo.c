#include "foo.h"
#include <stdio.h>

int FOO_MAGIC_NUMBER = 42;

void foo()
{
  printf("Foo: %d\n", FOO_MAGIC_NUMBER);
}