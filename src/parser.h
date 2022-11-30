/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     WHILE = 258,
     FOR = 259,
     TO = 260,
     BREAK = 261,
     LET = 262,
     IN = 263,
     END = 264,
     FUNCTION = 265,
     VAR = 266,
     TYPE = 267,
     ARRAY = 268,
     IF = 269,
     THEN = 270,
     ELSE = 271,
     DO = 272,
     OF = 273,
     NIL = 274,
     COMMA = 275,
     COLON = 276,
     SEMICOLON = 277,
     LPAREN = 278,
     RPAREN = 279,
     LBRACE = 280,
     RBRACE = 281,
     LRACKET = 282,
     RRACKET = 283,
     DOT = 284,
     PLUS = 285,
     MINUS = 286,
     TIMES = 287,
     DIVIDE = 288,
     EQ = 289,
     NOTEQ = 290,
     LT = 291,
     LE = 292,
     GT = 293,
     GE = 294,
     AND = 295,
     OR = 296,
     ASSIGN = 297,
     STRING = 298,
     INT = 299,
     ID = 300,
     LVALUE = 301,
     UMINUS = 302
   };
#endif
/* Tokens.  */
#define WHILE 258
#define FOR 259
#define TO 260
#define BREAK 261
#define LET 262
#define IN 263
#define END 264
#define FUNCTION 265
#define VAR 266
#define TYPE 267
#define ARRAY 268
#define IF 269
#define THEN 270
#define ELSE 271
#define DO 272
#define OF 273
#define NIL 274
#define COMMA 275
#define COLON 276
#define SEMICOLON 277
#define LPAREN 278
#define RPAREN 279
#define LBRACE 280
#define RBRACE 281
#define LRACKET 282
#define RRACKET 283
#define DOT 284
#define PLUS 285
#define MINUS 286
#define TIMES 287
#define DIVIDE 288
#define EQ 289
#define NOTEQ 290
#define LT 291
#define LE 292
#define GT 293
#define GE 294
#define AND 295
#define OR 296
#define ASSIGN 297
#define STRING 298
#define INT 299
#define ID 300
#define LVALUE 301
#define UMINUS 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 18 "./src/parser.y"
{
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
/* Line 1529 of yacc.c.  */
#line 161 "src/parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
