%{
#include "token.h"
#include "lexer.h"
#define YY_DECL int yylex()

Pos pos;
%}

%option noyywrap
%option stack

/* Start conditions */
%s string
%s comment 

DIGIT		[0-9]
%%

[ \t\n]     pos.col += 1;
{DIGIT}+    return INT;
\+          return PLUS;
<<EOF>>     return EOF;

%%