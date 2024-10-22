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

#ifndef YY_TT_USERS_MANGONOB_DEVELOPER_CTIGER_INCLUDE_TREE_TILING_H_INCLUDED
# define YY_TT_USERS_MANGONOB_DEVELOPER_CTIGER_INCLUDE_TREE_TILING_H_INCLUDED
/* Debug traces.  */
#ifndef TT_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define TT_DEBUG 1
#  else
#   define TT_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define TT_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined TT_DEBUG */
#if TT_DEBUG
extern int Tt_debug;
#endif

/* Token kinds.  */
#ifndef TT_TOKENTYPE
# define TT_TOKENTYPE
  enum Tt_tokentype
  {
    TOK_TT_EMPTY = -2,
    TOK_YYEOF = 0,                 /* "end of file"  */
    TOK_TT_error = 256,            /* error  */
    TOK_TT_UNDEF = 257,            /* "invalid token"  */
    TOK_PLUS = 258,                /* PLUS  */
    TOK_MINUS = 259,               /* MINUS  */
    TOK_MUL = 260,                 /* MUL  */
    TOK_DIV = 261,                 /* DIV  */
    TOK_AND = 262,                 /* AND  */
    TOK_OR = 263,                  /* OR  */
    TOK_LSHIFT = 264,              /* LSHIFT  */
    TOK_RSHIFT = 265,              /* RSHIFT  */
    TOK_ARSHIFT = 266,             /* ARSHIFT  */
    TOK_XOR = 267,                 /* XOR  */
    TOK_EQ = 268,                  /* EQ  */
    TOK_NE = 269,                  /* NE  */
    TOK_LT = 270,                  /* LT  */
    TOK_GT = 271,                  /* GT  */
    TOK_LE = 272,                  /* LE  */
    TOK_GE = 273,                  /* GE  */
    TOK_ULT = 274,                 /* ULT  */
    TOK_ULE = 275,                 /* ULE  */
    TOK_UGT = 276,                 /* UGT  */
    TOK_UGE = 277,                 /* UGE  */
    TOK_LABEL = 278,               /* LABEL  */
    TOK_JUMP = 279,                /* JUMP  */
    TOK_CJUMP = 280,               /* CJUMP  */
    TOK_MOVE = 281,                /* MOVE  */
    TOK_MEM = 282,                 /* MEM  */
    TOK_TEMP = 283,                /* TEMP  */
    TOK_CONST = 284,               /* CONST  */
    TOK_CALL = 285                 /* CALL  */
  };
  typedef enum Tt_tokentype Tt_token_kind_t;
#endif

/* Value type.  */
#if ! defined TT_STYPE && ! defined TT_STYPE_IS_DECLARED
typedef int TT_STYPE;
# define TT_STYPE_IS_TRIVIAL 1
# define TT_STYPE_IS_DECLARED 1
#endif


extern TT_STYPE Tt_lval;


int Tt_parse (void);


#endif /* !YY_TT_USERS_MANGONOB_DEVELOPER_CTIGER_INCLUDE_TREE_TILING_H_INCLUDED  */
