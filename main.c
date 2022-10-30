#include <stdio.h>
#include <time.h>
#include "foo.h"

int main(int argc, char *argv[])
{
  int n;

  printf("Input random number count: ");
  scanf("%d", &n);
  srand(time(0));

  for (int i = 0; i < n; i++)
    printf("%d\n", rand0());

  return 0;
}
