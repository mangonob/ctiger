#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
#define COUNT 4

int stringCompar(const void *lhs, const void *rhs);

int main(int argc, char *argv[])
{
  char text[COUNT][BUFFER_SIZE] = {};
  char *ptr[COUNT];

  for (int i = 0; i < COUNT; i++)
  {
    scanf("%s", text[i]);
    ptr[i] = text[i];
  }

  qsort(ptr, COUNT, sizeof(char *), stringCompar);

  for (int i = 0; i < COUNT; i++)
    puts(ptr[i]);

  return 0;
}

int stringCompar(const void *lhs, const void *rhs)
{
  char *l = *(char **)lhs;
  char *r = *(char **)rhs;
  return strcmp(l, r);
}