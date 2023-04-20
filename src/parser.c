/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



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




/* Copy the first part of user declarations.  */
#line 1 "/Users/mangonob/Developer/ctiger/src/parser.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 18 "/Users/mangonob/Developer/ctiger/src/parser.y"
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
/* Line 193 of yacc.c.  */
#line 222 "/Users/mangonob/Developer/ctiger/src/parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

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


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 247 "/Users/mangonob/Developer/ctiger/src/parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   260

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNRULES -- Number of states.  */
#define YYNSTATES  138

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    11,    13,    17,    21,
      24,    29,    33,    37,    41,    45,    49,    53,    57,    61,
      65,    69,    73,    77,    82,    89,    96,   101,   106,   115,
     117,   123,   125,   130,   134,   139,   140,   142,   144,   148,
     149,   151,   153,   157,   158,   160,   162,   166,   170,   172,
     173,   176,   178,   180,   182,   187,   189,   193,   197,   198,
     200,   202,   206,   210,   215,   222,   230,   240
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      49,     0,    -1,    50,    -1,    44,    -1,    43,    -1,    19,
      -1,    51,    -1,    51,    42,    50,    -1,    23,    52,    24,
      -1,    31,    50,    -1,    69,    23,    54,    24,    -1,    50,
      30,    50,    -1,    50,    31,    50,    -1,    50,    32,    50,
      -1,    50,    33,    50,    -1,    50,    34,    50,    -1,    50,
      35,    50,    -1,    50,    38,    50,    -1,    50,    36,    50,
      -1,    50,    39,    50,    -1,    50,    37,    50,    -1,    50,
      40,    50,    -1,    50,    41,    50,    -1,    69,    25,    56,
      26,    -1,    69,    27,    50,    28,    18,    50,    -1,    14,
      50,    15,    50,    16,    50,    -1,    14,    50,    15,    50,
      -1,     3,    50,    17,    50,    -1,     4,    69,    42,    50,
       5,    50,    17,    50,    -1,     6,    -1,     7,    59,     8,
      52,     9,    -1,    69,    -1,    69,    27,    50,    28,    -1,
      51,    29,    69,    -1,    51,    27,    50,    28,    -1,    -1,
      53,    -1,    50,    -1,    53,    22,    50,    -1,    -1,    55,
      -1,    50,    -1,    55,    20,    50,    -1,    -1,    57,    -1,
      58,    -1,    57,    20,    58,    -1,    69,    34,    50,    -1,
      60,    -1,    -1,    60,    61,    -1,    62,    -1,    67,    -1,
      68,    -1,    12,    69,    34,    63,    -1,    69,    -1,    13,
      18,    69,    -1,    25,    64,    26,    -1,    -1,    65,    -1,
      66,    -1,    65,    20,    66,    -1,    69,    21,    69,    -1,
      11,    69,    42,    50,    -1,    11,    69,    21,    69,    42,
      50,    -1,    10,    69,    23,    64,    24,    34,    50,    -1,
      10,    69,    23,    64,    24,    21,    69,    34,    50,    -1,
      45,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   105,   105,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   136,   137,   138,   139,   141,   142,   144,   145,   147,
     148,   150,   151,   154,   155,   157,   158,   160,   162,   164,
     165,   167,   168,   169,   171,   173,   174,   175,   177,   178,
     180,   181,   183,   185,   186,   188,   190,   193
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"while\"", "\"for\"", "\"to\"",
  "\"break\"", "\"let\"", "\"in\"", "\"end\"", "\"function\"", "\"var\"",
  "\"type\"", "\"array\"", "\"if\"", "\"then\"", "\"else\"", "\"do\"",
  "\"of\"", "\"nil\"", "\",\"", "\":\"", "\";\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\".\"", "\"+\"", "\"-\"", "\"*\"",
  "\"/\"", "\"=\"", "\"<>\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\"&\"", "\"|\"", "\":=\"", "STRING", "INT", "ID", "LVALUE", "UMINUS",
  "$accept", "prog", "exp", "lvalue", "expseq", "expseq_", "arg_list",
  "arg_list_", "record_list", "record_list_", "record", "decs", "decs_",
  "dec", "typedec", "ty", "tyfields", "tyfields_", "tyfield", "vardec",
  "funcdec", "id", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    58,    59,    60,
      60,    61,    61,    61,    62,    63,    63,    63,    64,    64,
      65,    65,    66,    67,    67,    68,    68,    69
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     3,     2,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     6,     6,     4,     4,     8,     1,
       5,     1,     4,     3,     4,     0,     1,     1,     3,     0,
       1,     1,     3,     0,     1,     1,     3,     3,     1,     0,
       2,     1,     1,     1,     4,     1,     3,     3,     0,     1,
       1,     3,     3,     4,     6,     7,     9,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    29,    49,     0,     5,    35,     0,     4,
       3,    67,     0,     2,     6,    31,     0,     0,     0,    48,
       0,    37,     0,    36,     9,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    39,    43,     0,     0,     0,    35,     0,     0,     0,
      50,    51,    52,    53,     0,     8,     0,    11,    12,    13,
      14,    15,    16,    18,    20,    17,    19,    21,    22,     0,
      33,     7,    41,     0,    40,     0,    44,    45,     0,     0,
      27,     0,     0,     0,     0,     0,    26,    38,    34,    10,
       0,    23,     0,     0,    32,     0,    30,    58,     0,     0,
       0,     0,    42,    46,    47,     0,     0,     0,    59,    60,
       0,     0,    63,     0,    58,    54,    55,    25,    24,     0,
       0,     0,     0,     0,     0,     0,    28,     0,     0,    61,
      62,    64,    56,    57,     0,    65,     0,    66
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    12,    21,    14,    22,    23,    73,    74,    75,    76,
      77,    18,    19,    50,    51,   115,   107,   108,   109,    52,
      53,    15
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -43
static const yytype_int16 yypact[] =
{
      69,    69,   -42,   -43,   -43,    69,   -43,    69,    69,   -43,
     -43,   -43,     6,   148,   -18,    -9,   135,   -32,     5,    67,
     123,   148,    -2,    -7,   -43,   -43,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,   -42,
      69,    69,   -42,    69,    69,    69,    69,   -42,   -42,   -42,
     -43,   -43,   -43,   -43,    69,   -43,    69,   -12,   -12,   -43,
     -43,   211,   211,   211,   211,   211,   211,   221,   200,   174,
     -43,   148,   148,     1,    22,    21,    28,   -43,    16,   188,
     148,   110,    42,    32,   -19,    19,    30,   148,   -43,   -43,
      69,   -43,   -42,    69,    56,    69,   -43,   -42,   -42,    69,
      -6,    69,   148,   -43,   148,    69,   160,    57,    60,   -43,
      61,    43,   148,    66,   -42,   -43,   -43,   148,   148,    69,
     -17,   -42,   -42,    69,   -42,    63,   148,   -42,    69,   -43,
     -43,   148,   -43,   -43,    52,   148,    69,   148
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,     0,   -43,    41,   -43,   -43,   -43,   -43,   -43,
      -1,   -43,   -43,   -43,   -43,   -43,   -20,   -43,   -25,   -43,
     -43,    10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      13,    16,    98,    11,   127,    20,    25,   113,    24,    38,
      45,    39,    17,    46,    41,    56,    42,   128,    43,   114,
      28,    29,    55,    99,    40,    89,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    11,
      71,    72,    90,    79,    80,    81,   101,    91,    92,    70,
      93,    96,    78,   100,    86,    97,    87,    83,    84,    85,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,     1,     2,   105,     3,     4,    47,    48,    49,
     121,   120,   122,     5,   124,   123,   136,    82,     6,   133,
     102,   103,     7,   104,   125,   106,   129,     0,     0,   112,
       8,   117,    78,     0,     0,   118,     0,   110,   111,     0,
     116,     0,     9,    10,    11,    95,     0,     0,     0,   126,
       0,     0,     0,   131,   110,     0,     0,     0,   135,     0,
       0,   110,   130,     0,   132,     0,   137,   134,    54,     0,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    44,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,   119,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    88,     0,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    94,     0,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    26,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

static const yytype_int16 yycheck[] =
{
       0,     1,    21,    45,    21,     5,     0,    13,     8,    27,
      42,    29,     2,     8,    23,    22,    25,    34,    27,    25,
      32,    33,    24,    42,    42,    24,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    45,
      40,    41,    20,    43,    44,    45,    16,    26,    20,    39,
      34,     9,    42,    34,    54,    23,    56,    47,    48,    49,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     3,     4,    18,     6,     7,    10,    11,    12,
      20,    24,    21,    14,    18,    42,    34,    46,    19,    26,
      90,    92,    23,    93,   114,    95,   121,    -1,    -1,    99,
      31,   101,    92,    -1,    -1,   105,    -1,    97,    98,    -1,
     100,    -1,    43,    44,    45,     5,    -1,    -1,    -1,   119,
      -1,    -1,    -1,   123,   114,    -1,    -1,    -1,   128,    -1,
      -1,   121,   122,    -1,   124,    -1,   136,   127,    15,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    17,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    17,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    28,    -1,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,    14,    19,    23,    31,    43,
      44,    45,    49,    50,    51,    69,    50,    69,    59,    60,
      50,    50,    52,    53,    50,     0,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    27,    29,
      42,    23,    25,    27,    17,    42,     8,    10,    11,    12,
      61,    62,    67,    68,    15,    24,    22,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      69,    50,    50,    54,    55,    56,    57,    58,    69,    50,
      50,    50,    52,    69,    69,    69,    50,    50,    28,    24,
      20,    26,    20,    34,    28,     5,     9,    23,    21,    42,
      34,    16,    50,    58,    50,    18,    50,    64,    65,    66,
      69,    69,    50,    13,    25,    63,    69,    50,    50,    17,
      24,    20,    21,    42,    18,    64,    50,    21,    34,    66,
      69,    50,    69,    26,    69,    50,    34,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 105 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = (yyvsp[(1) - (1)].exp); tgroot = (yyvsp[(1) - (1)].exp); }
    break;

  case 3:
#line 107 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_IntExp(LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].ival)); }
    break;

  case 4:
#line 108 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_StrExp(LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].sval)); }
    break;

  case 5:
#line 109 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_NilExp(LOC((yylsp[(1) - (1)]))); }
    break;

  case 6:
#line 110 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_VarExp((yyvsp[(1) - (1)].lvalue)); }
    break;

  case 7:
#line 111 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_AssignExp(LOC((yylsp[(2) - (3)])), (yyvsp[(1) - (3)].lvalue), (yyvsp[(3) - (3)].exp)); }
    break;

  case 8:
#line 112 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_SeqExp(LOC((yylsp[(1) - (3)])), (yyvsp[(2) - (3)].expseq)); }
    break;

  case 9:
#line 113 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(1) - (2)])), A_minusOp, A_IntExp(LOC((yylsp[(1) - (2)])), 0), (yyvsp[(2) - (2)].exp)); }
    break;

  case 10:
#line 114 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_CallExp(LOC((yylsp[(1) - (4)])), (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].arg_list)); }
    break;

  case 11:
#line 115 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_plusOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 12:
#line 116 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_minusOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 13:
#line 117 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_timesOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 14:
#line 118 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_divideOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 15:
#line 119 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_eqOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 16:
#line 120 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_neqOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 17:
#line 121 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_gtOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 18:
#line 122 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_ltOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 19:
#line 123 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_geOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 20:
#line 124 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_OpExp(LOC((yylsp[(2) - (3)])), A_leOp, (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp)); }
    break;

  case 21:
#line 125 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_IfExp(LOC((yylsp[(2) - (3)])), (yyvsp[(1) - (3)].exp), (yyvsp[(3) - (3)].exp), A_IntExp(LOC((yylsp[(3) - (3)])), 0)); }
    break;

  case 22:
#line 126 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_IfExp(LOC((yylsp[(2) - (3)])), (yyvsp[(1) - (3)].exp), A_IntExp(LOC((yylsp[(3) - (3)])), 1), (yyvsp[(3) - (3)].exp)); }
    break;

  case 23:
#line 127 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_RecordExp(LOC((yylsp[(1) - (4)])), (yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].record_list)); }
    break;

  case 24:
#line 128 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_ArrayExp(LOC((yylsp[(1) - (6)])), (yyvsp[(1) - (6)].id), (yyvsp[(3) - (6)].exp), (yyvsp[(6) - (6)].exp)); }
    break;

  case 25:
#line 129 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_IfExp(LOC((yylsp[(1) - (6)])), (yyvsp[(2) - (6)].exp), (yyvsp[(4) - (6)].exp), (yyvsp[(6) - (6)].exp)); }
    break;

  case 26:
#line 130 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_IfExp(LOC((yylsp[(1) - (4)])), (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].exp), NULL); }
    break;

  case 27:
#line 131 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_WhileExp(LOC((yylsp[(1) - (4)])), (yyvsp[(2) - (4)].exp), (yyvsp[(4) - (4)].exp)); }
    break;

  case 28:
#line 132 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_ForExp(LOC((yylsp[(1) - (8)])), (yyvsp[(2) - (8)].id), (yyvsp[(4) - (8)].exp), (yyvsp[(6) - (8)].exp), (yyvsp[(8) - (8)].exp)); }
    break;

  case 29:
#line 133 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_BreakExp(LOC((yylsp[(1) - (1)]))); }
    break;

  case 30:
#line 134 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.exp) = A_LetExp(LOC((yylsp[(1) - (5)])), (yyvsp[(2) - (5)].decs), (yyvsp[(4) - (5)].expseq)); }
    break;

  case 31:
#line 136 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.lvalue) = A_SimpleVar(LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].id)); }
    break;

  case 32:
#line 137 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.lvalue) = A_SubscriptVar(LOC((yylsp[(1) - (4)])), A_SimpleVar(LOC((yylsp[(1) - (4)])), (yyvsp[(1) - (4)].id)), (yyvsp[(3) - (4)].exp)); }
    break;

  case 33:
#line 138 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.lvalue) = A_FieldVar(LOC((yylsp[(1) - (3)])), (yyvsp[(1) - (3)].lvalue), (yyvsp[(3) - (3)].id)); }
    break;

  case 34:
#line 139 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.lvalue) = A_SubscriptVar(LOC((yylsp[(1) - (4)])), (yyvsp[(1) - (4)].lvalue), (yyvsp[(3) - (4)].exp)); }
    break;

  case 35:
#line 141 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.expseq) = NULL; }
    break;

  case 36:
#line 142 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.expseq) = A_ExpSeqReverse((yyvsp[(1) - (1)].expseq)); }
    break;

  case 37:
#line 144 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.expseq) = A_ExpSeq((yyvsp[(1) - (1)].exp), NULL); }
    break;

  case 38:
#line 145 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.expseq) = A_ExpSeq((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].expseq)); }
    break;

  case 39:
#line 147 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.arg_list) = NULL; }
    break;

  case 40:
#line 148 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.arg_list) = A_ExpSeqReverse((yyvsp[(1) - (1)].arg_list)); }
    break;

  case 41:
#line 150 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.arg_list) = A_ExpSeq((yyvsp[(1) - (1)].exp), NULL); }
    break;

  case 42:
#line 151 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.arg_list) = A_ExpSeq((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].arg_list)); }
    break;

  case 43:
#line 154 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.record_list) = NULL; }
    break;

  case 44:
#line 155 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.record_list) = A_RecordListReverse((yyvsp[(1) - (1)].record_list)); }
    break;

  case 45:
#line 157 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.record_list) = A_RecordList((yyvsp[(1) - (1)].record), NULL); }
    break;

  case 46:
#line 158 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.record_list) = A_RecordList((yyvsp[(3) - (3)].record), (yyvsp[(1) - (3)].record_list)); }
    break;

  case 47:
#line 160 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.record) = A_Record(LOC((yylsp[(1) - (3)])), (yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].exp)); }
    break;

  case 48:
#line 162 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.decs) = A_DecsReverse((yyvsp[(1) - (1)].decs)); }
    break;

  case 49:
#line 164 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.decs) = NULL; }
    break;

  case 50:
#line 165 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.decs) = A_Decs((yyvsp[(2) - (2)].dec), (yyvsp[(1) - (2)].decs)); }
    break;

  case 51:
#line 167 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = (yyvsp[(1) - (1)].dec); }
    break;

  case 52:
#line 168 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = (yyvsp[(1) - (1)].dec); }
    break;

  case 53:
#line 169 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = (yyvsp[(1) - (1)].dec); }
    break;

  case 54:
#line 171 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = A_TypeDec(LOC((yylsp[(1) - (4)])), (yyvsp[(2) - (4)].id), (yyvsp[(4) - (4)].ty)); }
    break;

  case 55:
#line 173 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.ty) = A_NamedTy(LOC((yylsp[(1) - (1)])), (yyvsp[(1) - (1)].id)); }
    break;

  case 56:
#line 174 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.ty) = A_ArrayTy(LOC((yylsp[(1) - (3)])), (yyvsp[(3) - (3)].id)); }
    break;

  case 57:
#line 175 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.ty) = A_RecordTy(LOC((yylsp[(1) - (3)])), (yyvsp[(2) - (3)].tyfields)); }
    break;

  case 58:
#line 177 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.tyfields) = NULL; }
    break;

  case 59:
#line 178 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.tyfields) = A_TyFieldsReverse((yyvsp[(1) - (1)].tyfields)); }
    break;

  case 60:
#line 180 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.tyfields) = A_TyFields((yyvsp[(1) - (1)].tyfield), NULL); }
    break;

  case 61:
#line 181 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.tyfields) = A_TyFields((yyvsp[(3) - (3)].tyfield), (yyvsp[(1) - (3)].tyfields)); }
    break;

  case 62:
#line 183 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.tyfield) = A_TyField(LOC((yylsp[(1) - (3)])), (yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].id)); }
    break;

  case 63:
#line 185 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = A_VarDec(LOC((yylsp[(1) - (4)])), (yyvsp[(2) - (4)].id), NULL, (yyvsp[(4) - (4)].exp)); }
    break;

  case 64:
#line 186 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = A_VarDec(LOC((yylsp[(1) - (6)])), (yyvsp[(2) - (6)].id), (yyvsp[(4) - (6)].id), (yyvsp[(6) - (6)].exp)); }
    break;

  case 65:
#line 189 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = A_FuncDec(LOC((yylsp[(1) - (7)])), (yyvsp[(2) - (7)].id), (yyvsp[(4) - (7)].tyfields), NULL, (yyvsp[(7) - (7)].exp)); }
    break;

  case 66:
#line 191 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.dec) = A_FuncDec(LOC((yylsp[(1) - (9)])), (yyvsp[(2) - (9)].id), (yyvsp[(4) - (9)].tyfields), (yyvsp[(7) - (9)].id), (yyvsp[(9) - (9)].exp)); }
    break;

  case 67:
#line 193 "/Users/mangonob/Developer/ctiger/src/parser.y"
    { (yyval.id) = A_Id(LOC((yylsp[(1) - (1)])), S_Symbol((yyvsp[(1) - (1)].idval))); (yyloc) = (yylsp[(1) - (1)]); }
    break;


/* Line 1267 of yacc.c.  */
#line 1941 "/Users/mangonob/Developer/ctiger/src/parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 195 "/Users/mangonob/Developer/ctiger/src/parser.y"


void yyerror(char *s) {
    printf("parser error: %s at line: %d, column: %d\n", s, yylloc.first_line, yylloc.first_column);
}
