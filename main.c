#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/lexer.h"
#include "lexer/token.h"

int main(int argc, char *argv[])
{
  Token tk;
  while ((tk = yylex()) != EOF)
    printf("Token %d\n", tk);
  return 0;
}