%{
#include <math.h>
#include <stdio.h>
#include "absyn.h"
#define YYERROR_VERBOSE
#define YYPARSE_PARAM input
#define YYLEX_PARAM input
#define LOC(x) ((A_Pos){ .column = (x).first_column, .row = (x).first_line})

int yylex(FILE *input);

void yyerror(char *s) {
    printf("parser error: %s\n", s);
}
%}

%locations

/* BISON Declarations */
%union {
    long ival;
    char *sval;
    char *idval;
    A_exp       exp;
    A_var       lvalue;
    A_expseq    expseq;
    A_expseq    arg_list;
    A_record_list   record_list;
    A_decs  decs;
    A_dec   dec;
    A_ty    ty;
    A_tyfields  tyfields;
    A_tyfield   tyfield;
    A_id    id;
}

%token WHILE        "while"
%token FOR          "for"
%token TO           "to"
%token BREAK        "break"
%token LET          "let"
%token IN           "in"
%token END          "end"
%token FUNCTION     "function"
%token VAR          "var"
%token TYPE         "type"
%token ARRAY        "array"
%token IF           "if"
%token THEN         "then"
%token ELSE         "else"
%token DO           "do"
%token OF           "of"
%token NIL          "nil"
%token COMMA        ","
%token COLON        ":"
%token SEMICOLON    ";"
%token LPAREN       "("
%token RPAREN       ")"
%token LBRACE       "{"
%token RBRACE       "}"
%token LRACKET      "["
%token RRACKET      "]"
%token DOT          "."
%token PLUS         "+"
%token MINUS        "-"
%token TIMES        "*"
%token DIVIDE       "/"
%token EQ           "="
%token NOTEQ        "<>"
%token LT           "<"
%token LE           "<="
%token GT           ">"
%token GE           ">="
%token AND          "&"
%token OR           "|"
%token ASSIGN       ":="
%token <sval>   STRING
%token <ival> INT
%token <idval> ID

%nonassoc LVALUE ":=" "then" "do"
%nonassoc "else" "of" "["
%left "|"
%left "&"
%nonassoc "=" ">" ">=" "<" "<=" "<>"
%left "+" "-"
%left "*" "/"
%left UMINUS

%type <id> id

/* Grammar follows */
%%

exp:        INT
            | STRING
            | NIL
            | lvalue
            | lvalue ":=" exp
            | "(" ")"
            | "(" expseq ")"
            | "-" exp %prec UMINUS
            | id "(" ")"
            | id "(" arg_list ")"
            | exp "+" exp
            | exp "-" exp
            | exp "*" exp
            | exp "/" exp
            | exp "=" exp
            | exp "<>" exp
            | exp ">" exp
            | exp "<" exp
            | exp ">=" exp
            | exp "<=" exp
            | exp "&" exp
            | exp "|" exp
            | id "{" "}"
            | id "{" record_list "}"
            | id "[" exp "]" "of" exp
            | IF exp THEN exp ELSE exp
            | IF exp THEN exp
            | WHILE exp DO exp
            | FOR id ":=" exp TO exp DO exp
            | BREAK
            | LET decs IN END
            | LET decs IN expseq END

lvalue:     id %prec LVALUE
            | lvalue "." id
            | lvalue "[" exp "]"

expseq:     exp
            | expseq ";" exp

arg_list:   exp
            | arg_list "," exp

record_list:    id "=" exp
            | record_list "," id "=" exp

decs:       /* empty */
            | decs dec

dec:        typedec
            | vardec
            | funcdec

typedec:    "type" id "=" ty

ty:         id
            | "array" "of" id
            | "{" tyfields "}"

tyfields:   /* empty */
            | id ":" id
            | tyfields "," id ":" id

vardec:     "var" id ":=" exp
            | "var" id ":" id ":=" exp

funcdec:    "function" id "(" tyfields ")" "=" exp
            | "function" id "(" tyfields ")" ":" id "=" exp

id:         ID              { $$ = A_Id(LOC(@1), $1); }

%%
