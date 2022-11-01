#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdatomic.h>
#include "foo.h"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s filename\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  FILE *f;
  if ((f = fopen(argv[1], "r")) == NULL)
  {
    printf("Error: cannot open file %s", argv[1]);
    exit(EXIT_FAILURE);
  }

  int s = fseek(f, 0, SEEK_END);
  while (fseek(f, -1, SEEK_CUR) == 0)
  {
    char ch = fgetc(f);
    putchar(ch);
    ungetc(ch, f);
  }
  putchar('\n');

  return 0;
}
