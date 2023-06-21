%{
#include <stdio.h>
#include <string.h>
#include "absyn.h"
#include "parser.h"
#define SBUF_SIZE   4096
#define YY_DECL int yylex(FILE *input)
#ifdef YYLTYPE_IS_DECLARED
    void position_forward();
    #define YY_USER_ACTION      do { position_forward(); } while(0);
#endif

static char str_buffer[SBUF_SIZE];
static int str_buffer_cursor = 0;

void append_char(char ch) {
    str_buffer[str_buffer_cursor++] = ch;
}
%}

%option noyywrap
%option stack
%x  STR
%x  COMMENT

DIGIT       [0-9]
ID          [a-zA-Z_][a-zA-Z0-9_]*
%%

    yyin = input ? input : stdin;

[ \t\n]                     ;
\/\/.*\n                    ;
<INITIAL,COMMENT>\/\*       { yy_push_state(COMMENT); } /* Begin comments */
<COMMENT>"*/"               { yy_pop_state(); }         /* End comments */
<COMMENT>.                  ;
<COMMENT>[ \t\n]            ;
\"                          { str_buffer_cursor = 0; yy_push_state(STR); }
<STR>\"                     {
                                yy_pop_state();
                                append_char('\0');
                                yylval.sval = strdup(str_buffer);
                                return STRING;
                            }
<STR>\\a                    append_char('\a');
<STR>\\b                    append_char('\b');
<STR>\\f                    append_char('\f');
<STR>\\n                    append_char('\n');
<STR>\\r                    append_char('\r');
<STR>\\t                    append_char('\t');
<STR>\\v                    append_char('\v');
<STR>\\\\                   append_char('\\');
<STR>\\\'                   append_char('\'');
<STR>\\\"                   append_char('\"');
<STR>\\0                    append_char('\0');
<STR>.                      append_char(yytext[0]);
"while"                     return WHILE;
"for"                       return FOR;
"to"                        return TO;
"break"                     return BREAK;
"let"                       return LET;
"in"                        return IN;
"end"                       return END;
"function"                  return FUNCTION;
"var"                       return VAR;
"type"                      return TYPE;
"array"                     return ARRAY;
"if"                        return IF;
"then"                      return THEN;
"else"                      return ELSE;
"do"                        return DO;
"of"                        return OF;
"nil"                       return NIL;
","                         return COMMA;
":"                         return COLON;
";"                         return SEMICOLON;
"("                         return LPAREN;
")"                         return RPAREN;
"{"                         return LBRACE;
"}"                         return RBRACE;
"["                         return LRACKET;
"]"                         return RRACKET;
"."                         return DOT;
"+"                         return PLUS;
"-"                         return MINUS;
"*"                         return TIMES;
"/"                         return DIVIDE;
"="                         return EQ;
"<>"                        return NOTEQ;
"<"                         return LT;
"<="                        return LE;
">"                         return GT;
">="                        return GE;
"&"                         return AND;
"|"                         return OR;
":="                        return ASSIGN;
{DIGIT}+                    { sscanf(yytext, "%ld", &yylval.ival); return INT; }
{ID}                        { yylval.idval = strdup(yytext); return ID; }
.                           { printf("bad token %s\n", yytext); exit(1); }
<<EOF>>                     return EOF;

%%

#ifdef YYLTYPE_IS_DECLARED
void position_forward() {
    if (YY_START == INITIAL) {
        yylloc.first_line = yylloc.last_line;
        yylloc.first_column = yylloc.last_column + 1;
    }

    for (int i = 0; i < yyleng; i++) {
        if (yytext[i] == '\n') {
            yylloc.last_line++;
            yylloc.last_column = 0;
        } else {
            yylloc.last_column++;
        }
    }
}
#endif
