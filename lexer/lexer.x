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

Digth		[0-9]
%%

[ \t]       pos.col += 1;
\n          pos.col = 0; pos.row += 1;
[^ \t\n]+   {
    pos.col += yyleng; yy_push_state(string); 
    pos.col += yyleng; printf("content %s length %ld\n", yytext, yyleng);
}

%%