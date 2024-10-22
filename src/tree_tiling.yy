%{
    #include <stdio.h>
    int Tt_lex();
    void Tt_error(const char *);
%}

%define 	api.token.prefix {TOK_}
%define     api.prefix {Tt_}

/* binary operations */
%token PLUS
%token MINUS
%token MUL
%token DIV
%token AND
%token OR
%token LSHIFT
%token RSHIFT
%token ARSHIFT
%token XOR
/* relative operations */
%token EQ
%token NE
%token LT
%token GT
%token LE
%token GE
%token ULT
%token ULE
%token UGT
%token UGE
/* statement */
%token LABEL
%token JUMP
%token CJUMP
%token MOVE
/* expression */
%token MEM
%token TEMP
%token NAME
%token CONST
%token CALL

%%
P:      %empty
%%

int Tt_lex() {
    return TOK_YYEOF;
}

void Tt_error(const char *msg) {
    fprintf(stderr, "%s", msg);
}
