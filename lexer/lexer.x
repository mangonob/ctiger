%{
#include "token.h"
#include "lexer.h"

static Pos pos;
%}

%%
[ \t]				pos.col += 1;
\n					pos.col = 0; pos.row += 1;
[0-9a-zA-Z_-]+		pos.col += yyleng; printf("contents %s length %ld\n", yytext, yyleng);

%%
int main() {
	yylex();
	printf("row %d col %d\n", pos.row, pos.col);
	return 0;
}

int yywrap() { return 1; }