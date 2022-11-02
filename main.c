#include <stdio.h>
#define ARR_SIZE 100

typedef struct
{
  int elements[ARR_SIZE];
} Array;

int main(int argc, char *argv[])
{
  Array s1 = {{1, 2, 3, 4, 5, 6, 7}};
  Array s2 = s1;

  for (int i = 0; i < ARR_SIZE; i++)
  {
    printf("%d, ", s2.elements[i]);
  }

  puts("");
  return 0;
}