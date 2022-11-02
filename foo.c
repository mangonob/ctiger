#include "foo.h"
#include <stdio.h>

int FOO_MAGIC_NUMBER = 42;

static unsigned long int randomSeed = 1;

void srand(unsigned int seed)
{
  randomSeed = seed;
}

int rand0()
{
  randomSeed = randomSeed * 1103515245 + 12345;
  return (unsigned int)(randomSeed / 65536) % 32768;
}

double randf()
{
  return rand0() / 32768.0;
}