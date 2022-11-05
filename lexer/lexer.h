#ifndef __LEXER_HEADER__
#define __LEXER_HEADER__

int yylex();

typedef struct
{
  int col;
  int row;
} Pos;

#endif