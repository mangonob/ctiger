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

  char ch;
  int count = 0;
  while ((ch = getc(f)) != EOF)
  {
    putc(ch, stdout);
    count++;
  }
  fclose(f);

  printf("\nTotal char count is %d\n", count);

  return 0;
}
