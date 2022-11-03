#include <stdio.h>

typedef char Byte;
typedef char *String;

int main(int argc, char *argv[])
{
  String message = "Hello World!";
  printf("%s\n", message);
  return 0;
}