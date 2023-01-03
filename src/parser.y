%{
#include <math.h>
#include <stdio.h>
#include "absyn.h"
#define YYERROR_VERBOSE
#define YYPARSE_PARAM input
#define YYLEX_PARAM input
#define LOC(x) ((A_Pos){ .column = (x).first_column, .row = (x).first_line})

int yylex(FILE *input);
void yyerror(char *s);
A_exp tgroot;
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
    A_record    record;
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

%type <exp> exp prog
%type <lvalue> lvalue
%type <expseq> expseq expseq_
%type <arg_list> arg_list arg_list_
%type <record_list> record_list record_list_
%type <decs> decs
%type <dec> dec typedec vardec funcdec
%type <ty> ty
%type <tyfields> tyfields tyfields_
%type <tyfield> tyfield
%type <record> record
%type <id> id

/* Grammar follows */
%%

prog:       exp                                 { $$ = $1; tgroot = $1; }

exp:        INT                                 { $$ = A_IntExp(LOC(@1), $1); }
            | STRING                            { $$ = A_StrExp(LOC(@1), $1); }
            | NIL                               { $$ = A_NilExp(LOC(@1)); }
            | lvalue                            { $$ = A_VarExp($1); }
            | lvalue ":=" exp                   { $$ = A_AssignExp(LOC(@2), $1, $3); }
            | "(" expseq ")"                    { $$ = A_SeqExp(LOC(@1), $2); }
            | "-" exp %prec UMINUS              { $$ = A_OpExp(LOC(@1), A_minusOp, A_IntExp(LOC(@1), 0), $2); }
            | id "(" arg_list ")"               { $$ = A_CallExp(LOC(@1), $1, $3); }
            | exp "+" exp                       { $$ = A_OpExp(LOC(@2), A_plusOp, $1, $3); }
            | exp "-" exp                       { $$ = A_OpExp(LOC(@2), A_minusOp, $1, $3); }
            | exp "*" exp                       { $$ = A_OpExp(LOC(@2), A_timesOp, $1, $3); }
            | exp "/" exp                       { $$ = A_OpExp(LOC(@2), A_divideOp, $1, $3); }
            | exp "=" exp                       { $$ = A_OpExp(LOC(@2), A_eqOp, $1, $3); }
            | exp "<>" exp                      { $$ = A_OpExp(LOC(@2), A_neqOp, $1, $3); } 
            | exp ">" exp                       { $$ = A_OpExp(LOC(@2), A_gtOp, $1, $3); }
            | exp "<" exp                       { $$ = A_OpExp(LOC(@2), A_ltOp, $1, $3); }
            | exp ">=" exp                      { $$ = A_OpExp(LOC(@2), A_geOp, $1, $3); }
            | exp "<=" exp                      { $$ = A_OpExp(LOC(@2), A_leOp, $1, $3); }
            | exp "&" exp                       { $$ = A_OpExp(LOC(@2), A_andOp, $1, $3); }
            | exp "|" exp                       { $$ = A_OpExp(LOC(@2), A_orOp, $1, $3); }
            | id "{" record_list "}"            { $$ = A_RecordExp(LOC(@1), $1, $3); }
            | id "[" exp "]" "of" exp           { $$ = A_ArrayExp(LOC(@1), $1, $3, $6); }
            | IF exp THEN exp ELSE exp          { $$ = A_IfExp(LOC(@1), $2, $4, $6); }
            | IF exp THEN exp                   { $$ = A_IfExp(LOC(@1), $2, $4, NULL); }
            | WHILE exp DO exp                  { $$ = A_WhileExp(LOC(@1), $2, $4); }
            | FOR id ":=" exp TO exp DO exp     { $$ = A_ForExp(LOC(@1), $2, $4, $6, $8); }
            | BREAK                             { $$ = A_BreakExp(LOC(@1)); }
            | LET decs IN expseq END            { $$ = A_LetExp(LOC(@1), $2, $4); }

lvalue:     id %prec LVALUE                     { $$ = A_SimpleVar(LOC(@1), $1); }
            | id "[" exp "]"                    { $$ = A_SubscriptVar(LOC(@1), A_SimpleVar(LOC(@1), $1), $3); }
            | lvalue "." id                     { $$ = A_FieldVar(LOC(@1), $1, $3); }
            | lvalue "[" exp "]"                { $$ = A_SubscriptVar(LOC(@1), $1, $3); }

expseq:     /* empty */                         { $$ = NULL; }
            | expseq_                           { $$ = $1; }

expseq_:    exp                                 { $$ = A_ExpSeq($1, NULL); }
            | expseq_ ";" exp                   { $$ = A_ExpSeq($3, $1); }

arg_list:   /* empty */                         { $$ = NULL; }
            | arg_list_                         { $$ = $1; }

arg_list_:  exp                                 { $$ = A_ExpSeq($1, NULL); }
            | arg_list_ "," exp                 { $$ = A_ExpSeq($3, $1); }


record_list:    /* empty */                     { $$ = NULL; }
            | record_list_                      { $$ = $1; }

record_list_:   record                          { $$ = A_RecordList($1, NULL); }
            | record_list_ "," record           { $$ = A_RecordList($3, $1); }

record:     id "=" exp                          { $$ = A_Record(LOC(@1), $1, $3); }

decs:       /* empty */                         { $$ = NULL; }
            | decs dec                          { $$ = A_Decs($2, $1); }

dec:        typedec                             { $$ = $1; }
            | vardec                            { $$ = $1; }
            | funcdec                           { $$ = $1; }

typedec:    "type" id "=" ty                    { $$ = A_TypeDec(LOC(@1), $2, $4); }

ty:         id                                  { $$ = A_NamedTy(LOC(@1), $1); }
            | "array" "of" id                   { $$ = A_ArrayTy(LOC(@1), $3); }
            | "{" tyfields "}"                  { $$ = A_RecordTy(LOC(@1), $2); }

tyfields:   /* empty */                         { $$ = NULL; }
            | tyfields_                         { $$ = $1; }

tyfields_:  tyfield                             { $$ = A_TyFields($1, NULL); }
            | tyfields_ "," tyfield             { $$ = A_TyFields($3, $1); }

tyfield:    id ":" id                           { $$ = A_TyField(LOC(@1), $1, $3); }

vardec:     "var" id ":=" exp                   { $$ = A_VarDec(LOC(@1), $2, NULL, $4); }
            | "var" id ":" id ":=" exp          { $$ = A_VarDec(LOC(@1), $2, $4, $6); }

funcdec:    "function" id "(" tyfields ")" "=" exp
                                                { $$ = A_FuncDec(LOC(@1), $2, $4, NULL, $7); }
            | "function" id "(" tyfields ")" ":" id "=" exp
                                                { $$ = A_FuncDec(LOC(@1), $2, $4, $7, $9); }

id:         ID                                  { $$ = A_Id(LOC(@1), $1); @$ = @1; }

%%

void yyerror(char *s) {
    printf("parser error: %s at line: %d, column: %d\n", s, yylloc.first_line, yylloc.first_column);
}