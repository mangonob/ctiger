/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_USERS_MANGONOB_DEVELOPER_CTIGER_INCLUDE_PARSER_H_INCLUDED
# define YY_YY_USERS_MANGONOB_DEVELOPER_CTIGER_INCLUDE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    WHILE = 258,                   /* "while"  */
    FOR = 259,                     /* "for"  */
    TO = 260,                      /* "to"  */
    BREAK = 261,                   /* "break"  */
    LET = 262,                     /* "let"  */
    IN = 263,                      /* "in"  */
    END = 264,                     /* "end"  */
    FUNCTION = 265,                /* "function"  */
    VAR = 266,                     /* "var"  */
    TYPE = 267,                    /* "type"  */
    ARRAY = 268,                   /* "array"  */
    IF = 269,                      /* "if"  */
    THEN = 270,                    /* "then"  */
    ELSE = 271,                    /* "else"  */
    DO = 272,                      /* "do"  */
    OF = 273,                      /* "of"  */
    NIL = 274,                     /* "nil"  */
    COMMA = 275,                   /* ","  */
    COLON = 276,                   /* ":"  */
    SEMICOLON = 277,               /* ";"  */
    LPAREN = 278,                  /* "("  */
    RPAREN = 279,                  /* ")"  */
    LBRACE = 280,                  /* "{"  */
    RBRACE = 281,                  /* "}"  */
    LRACKET = 282,                 /* "["  */
    RRACKET = 283,                 /* "]"  */
    DOT = 284,                     /* "."  */
    PLUS = 285,                    /* "+"  */
    MINUS = 286,                   /* "-"  */
    TIMES = 287,                   /* "*"  */
    DIVIDE = 288,                  /* "/"  */
    EQ = 289,                      /* "="  */
    NOTEQ = 290,                   /* "<>"  */
    LT = 291,                      /* "<"  */
    LE = 292,                      /* "<="  */
    GT = 293,                      /* ">"  */
    GE = 294,                      /* ">="  */
    AND = 295,                     /* "&"  */
    OR = 296,                      /* "|"  */
    ASSIGN = 297,                  /* ":="  */
    STRING = 298,                  /* STRING  */
    INT = 299,                     /* INT  */
    ID = 300,                      /* ID  */
    LVALUE = 301,                  /* LVALUE  */
    UMINUS = 302                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "/Users/mangonob/Developer/ctiger/src/parser.yy"

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

#line 129 "/Users/mangonob/Developer/ctiger/include/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (FILE *input);


#endif /* !YY_YY_USERS_MANGONOB_DEVELOPER_CTIGER_INCLUDE_PARSER_H_INCLUDED  */
