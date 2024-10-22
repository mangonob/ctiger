/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/Users/mangonob/Developer/ctiger/src/parser.yy"

#include <math.h>
#include <stdio.h>
#include "absyn.h"
#define LOC(x) ((A_Pos){ .column = (x).first_column, .row = (x).first_line})

int yylex(FILE *input);
void yyerror(FILE *input, const char *s);
A_exp tgroot;

#line 82 "/Users/mangonob/Developer/ctiger/src/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_WHILE = 3,                      /* "while"  */
  YYSYMBOL_FOR = 4,                        /* "for"  */
  YYSYMBOL_TO = 5,                         /* "to"  */
  YYSYMBOL_BREAK = 6,                      /* "break"  */
  YYSYMBOL_LET = 7,                        /* "let"  */
  YYSYMBOL_IN = 8,                         /* "in"  */
  YYSYMBOL_END = 9,                        /* "end"  */
  YYSYMBOL_FUNCTION = 10,                  /* "function"  */
  YYSYMBOL_VAR = 11,                       /* "var"  */
  YYSYMBOL_TYPE = 12,                      /* "type"  */
  YYSYMBOL_ARRAY = 13,                     /* "array"  */
  YYSYMBOL_IF = 14,                        /* "if"  */
  YYSYMBOL_THEN = 15,                      /* "then"  */
  YYSYMBOL_ELSE = 16,                      /* "else"  */
  YYSYMBOL_DO = 17,                        /* "do"  */
  YYSYMBOL_OF = 18,                        /* "of"  */
  YYSYMBOL_NIL = 19,                       /* "nil"  */
  YYSYMBOL_COMMA = 20,                     /* ","  */
  YYSYMBOL_COLON = 21,                     /* ":"  */
  YYSYMBOL_SEMICOLON = 22,                 /* ";"  */
  YYSYMBOL_LPAREN = 23,                    /* "("  */
  YYSYMBOL_RPAREN = 24,                    /* ")"  */
  YYSYMBOL_LBRACE = 25,                    /* "{"  */
  YYSYMBOL_RBRACE = 26,                    /* "}"  */
  YYSYMBOL_LRACKET = 27,                   /* "["  */
  YYSYMBOL_RRACKET = 28,                   /* "]"  */
  YYSYMBOL_DOT = 29,                       /* "."  */
  YYSYMBOL_PLUS = 30,                      /* "+"  */
  YYSYMBOL_MINUS = 31,                     /* "-"  */
  YYSYMBOL_TIMES = 32,                     /* "*"  */
  YYSYMBOL_DIVIDE = 33,                    /* "/"  */
  YYSYMBOL_EQ = 34,                        /* "="  */
  YYSYMBOL_NOTEQ = 35,                     /* "<>"  */
  YYSYMBOL_LT = 36,                        /* "<"  */
  YYSYMBOL_LE = 37,                        /* "<="  */
  YYSYMBOL_GT = 38,                        /* ">"  */
  YYSYMBOL_GE = 39,                        /* ">="  */
  YYSYMBOL_AND = 40,                       /* "&"  */
  YYSYMBOL_OR = 41,                        /* "|"  */
  YYSYMBOL_ASSIGN = 42,                    /* ":="  */
  YYSYMBOL_STRING = 43,                    /* STRING  */
  YYSYMBOL_INT = 44,                       /* INT  */
  YYSYMBOL_ID = 45,                        /* ID  */
  YYSYMBOL_LVALUE = 46,                    /* LVALUE  */
  YYSYMBOL_UMINUS = 47,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 48,                  /* $accept  */
  YYSYMBOL_prog = 49,                      /* prog  */
  YYSYMBOL_exp = 50,                       /* exp  */
  YYSYMBOL_lvalue = 51,                    /* lvalue  */
  YYSYMBOL_expseq = 52,                    /* expseq  */
  YYSYMBOL_expseq_ = 53,                   /* expseq_  */
  YYSYMBOL_arg_list = 54,                  /* arg_list  */
  YYSYMBOL_arg_list_ = 55,                 /* arg_list_  */
  YYSYMBOL_record_list = 56,               /* record_list  */
  YYSYMBOL_record_list_ = 57,              /* record_list_  */
  YYSYMBOL_record = 58,                    /* record  */
  YYSYMBOL_decs = 59,                      /* decs  */
  YYSYMBOL_decs_ = 60,                     /* decs_  */
  YYSYMBOL_dec = 61,                       /* dec  */
  YYSYMBOL_typedec = 62,                   /* typedec  */
  YYSYMBOL_ty = 63,                        /* ty  */
  YYSYMBOL_tyfields = 64,                  /* tyfields  */
  YYSYMBOL_tyfields_ = 65,                 /* tyfields_  */
  YYSYMBOL_tyfield = 66,                   /* tyfield  */
  YYSYMBOL_vardec = 67,                    /* vardec  */
  YYSYMBOL_funcdec = 68,                   /* funcdec  */
  YYSYMBOL_id = 69                         /* id  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  138

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   302


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"while\"", "\"for\"",
  "\"to\"", "\"break\"", "\"let\"", "\"in\"", "\"end\"", "\"function\"",
  "\"var\"", "\"type\"", "\"array\"", "\"if\"", "\"then\"", "\"else\"",
  "\"do\"", "\"of\"", "\"nil\"", "\",\"", "\":\"", "\";\"", "\"(\"",
  "\")\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\".\"", "\"+\"", "\"-\"",
  "\"*\"", "\"/\"", "\"=\"", "\"<>\"", "\"<\"", "\"<=\"", "\">\"",
  "\">=\"", "\"&\"", "\"|\"", "\":=\"", "STRING", "INT", "ID", "LVALUE",
  "UMINUS", "$accept", "prog", "exp", "lvalue", "expseq", "expseq_",
  "arg_list", "arg_list_", "record_list", "record_list_", "record", "decs",
  "decs_", "dec", "typedec", "ty", "tyfields", "tyfields_", "tyfield",
  "vardec", "funcdec", "id", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
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

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,     0,   -43,    41,   -43,   -43,   -43,   -43,   -43,
      -1,   -43,   -43,   -43,   -43,   -43,   -20,   -43,   -25,   -43,
     -43,    10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    12,    21,    14,    22,    23,    73,    74,    75,    76,
      77,    18,    19,    50,    51,   115,   107,   108,   109,    52,
      53,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    48,    49,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    51,    51,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    58,    59,    60,
      60,    61,    61,    61,    62,    63,    63,    63,    64,    64,
      65,    65,    66,    67,    67,    68,    68,    69
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     3,     3,     2,
       4,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     6,     6,     4,     4,     8,     1,
       5,     1,     4,     3,     4,     0,     1,     1,     3,     0,
       1,     1,     3,     0,     1,     1,     3,     3,     1,     0,
       2,     1,     1,     1,     4,     1,     3,     3,     0,     1,
       1,     3,     3,     4,     6,     7,     9,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (input, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, input); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, FILE *input)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (input);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, FILE *input)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, input);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, FILE *input)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), input);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, input); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, FILE *input)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (input);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (FILE *input)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (input);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* prog: exp  */
#line 105 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = (yyvsp[0].exp); tgroot = (yyvsp[0].exp); }
#line 1640 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 3: /* exp: INT  */
#line 107 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_IntExp(LOC((yylsp[0])), (yyvsp[0].ival)); }
#line 1646 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 4: /* exp: STRING  */
#line 108 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_StrExp(LOC((yylsp[0])), (yyvsp[0].sval)); }
#line 1652 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 5: /* exp: "nil"  */
#line 109 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_NilExp(LOC((yylsp[0]))); }
#line 1658 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 6: /* exp: lvalue  */
#line 110 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_VarExp((yyvsp[0].lvalue)); }
#line 1664 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 7: /* exp: lvalue ":=" exp  */
#line 111 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_AssignExp(LOC((yylsp[-1])), (yyvsp[-2].lvalue), (yyvsp[0].exp)); }
#line 1670 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 8: /* exp: "(" expseq ")"  */
#line 112 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_SeqExp(LOC((yylsp[-2])), (yyvsp[-1].expseq)); }
#line 1676 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 9: /* exp: "-" exp  */
#line 113 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_minusOp, A_IntExp(LOC((yylsp[-1])), 0), (yyvsp[0].exp)); }
#line 1682 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 10: /* exp: id "(" arg_list ")"  */
#line 114 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_CallExp(LOC((yylsp[-3])), (yyvsp[-3].id), (yyvsp[-1].arg_list)); }
#line 1688 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 11: /* exp: exp "+" exp  */
#line 115 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_plusOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1694 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 12: /* exp: exp "-" exp  */
#line 116 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_minusOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1700 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 13: /* exp: exp "*" exp  */
#line 117 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_timesOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1706 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 14: /* exp: exp "/" exp  */
#line 118 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_divideOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1712 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 15: /* exp: exp "=" exp  */
#line 119 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_eqOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1718 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 16: /* exp: exp "<>" exp  */
#line 120 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_neqOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1724 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 17: /* exp: exp ">" exp  */
#line 121 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_gtOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1730 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 18: /* exp: exp "<" exp  */
#line 122 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_ltOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1736 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 19: /* exp: exp ">=" exp  */
#line 123 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_geOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1742 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 20: /* exp: exp "<=" exp  */
#line 124 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_OpExp(LOC((yylsp[-1])), A_leOp, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1748 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 21: /* exp: exp "&" exp  */
#line 125 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_IfExp(LOC((yylsp[-1])), (yyvsp[-2].exp), (yyvsp[0].exp), A_IntExp(LOC((yylsp[0])), 0)); }
#line 1754 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 22: /* exp: exp "|" exp  */
#line 126 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_IfExp(LOC((yylsp[-1])), (yyvsp[-2].exp), A_IntExp(LOC((yylsp[0])), 1), (yyvsp[0].exp)); }
#line 1760 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 23: /* exp: id "{" record_list "}"  */
#line 127 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_RecordExp(LOC((yylsp[-3])), (yyvsp[-3].id), (yyvsp[-1].record_list)); }
#line 1766 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 24: /* exp: id "[" exp "]" "of" exp  */
#line 128 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_ArrayExp(LOC((yylsp[-5])), (yyvsp[-5].id), (yyvsp[-3].exp), (yyvsp[0].exp)); }
#line 1772 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 25: /* exp: "if" exp "then" exp "else" exp  */
#line 129 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_IfExp(LOC((yylsp[-5])), (yyvsp[-4].exp), (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1778 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 26: /* exp: "if" exp "then" exp  */
#line 130 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_IfExp(LOC((yylsp[-3])), (yyvsp[-2].exp), (yyvsp[0].exp), NULL); }
#line 1784 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 27: /* exp: "while" exp "do" exp  */
#line 131 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_WhileExp(LOC((yylsp[-3])), (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1790 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 28: /* exp: "for" id ":=" exp "to" exp "do" exp  */
#line 132 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_ForExp(LOC((yylsp[-7])), (yyvsp[-6].id), (yyvsp[-4].exp), (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1796 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 29: /* exp: "break"  */
#line 133 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_BreakExp(LOC((yylsp[0]))); }
#line 1802 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 30: /* exp: "let" decs "in" expseq "end"  */
#line 134 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.exp) = A_LetExp(LOC((yylsp[-4])), (yyvsp[-3].decs), A_SeqExp(LOC((yylsp[-1])), (yyvsp[-1].expseq))); }
#line 1808 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 31: /* lvalue: id  */
#line 136 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.lvalue) = A_SimpleVar(LOC((yylsp[0])), (yyvsp[0].id)); }
#line 1814 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 32: /* lvalue: id "[" exp "]"  */
#line 137 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.lvalue) = A_SubscriptVar(LOC((yylsp[-3])), A_SimpleVar(LOC((yylsp[-3])), (yyvsp[-3].id)), (yyvsp[-1].exp)); }
#line 1820 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 33: /* lvalue: lvalue "." id  */
#line 138 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.lvalue) = A_FieldVar(LOC((yylsp[-2])), (yyvsp[-2].lvalue), (yyvsp[0].id)); }
#line 1826 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 34: /* lvalue: lvalue "[" exp "]"  */
#line 139 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.lvalue) = A_SubscriptVar(LOC((yylsp[-3])), (yyvsp[-3].lvalue), (yyvsp[-1].exp)); }
#line 1832 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 35: /* expseq: %empty  */
#line 141 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.expseq) = NULL; }
#line 1838 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 36: /* expseq: expseq_  */
#line 142 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.expseq) = A_ExpSeqReversed((yyvsp[0].expseq)); }
#line 1844 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 37: /* expseq_: exp  */
#line 144 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.expseq) = A_ExpSeq((yyvsp[0].exp), NULL); }
#line 1850 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 38: /* expseq_: expseq_ ";" exp  */
#line 145 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.expseq) = A_ExpSeq((yyvsp[0].exp), (yyvsp[-2].expseq)); }
#line 1856 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 39: /* arg_list: %empty  */
#line 147 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.arg_list) = NULL; }
#line 1862 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 40: /* arg_list: arg_list_  */
#line 148 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.arg_list) = A_ExpSeqReversed((yyvsp[0].arg_list)); }
#line 1868 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 41: /* arg_list_: exp  */
#line 150 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.arg_list) = A_ExpSeq((yyvsp[0].exp), NULL); }
#line 1874 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 42: /* arg_list_: arg_list_ "," exp  */
#line 151 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.arg_list) = A_ExpSeq((yyvsp[0].exp), (yyvsp[-2].arg_list)); }
#line 1880 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 43: /* record_list: %empty  */
#line 154 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.record_list) = NULL; }
#line 1886 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 44: /* record_list: record_list_  */
#line 155 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.record_list) = A_RecordListReversed((yyvsp[0].record_list)); }
#line 1892 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 45: /* record_list_: record  */
#line 157 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.record_list) = A_RecordList((yyvsp[0].record), NULL); }
#line 1898 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 46: /* record_list_: record_list_ "," record  */
#line 158 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.record_list) = A_RecordList((yyvsp[0].record), (yyvsp[-2].record_list)); }
#line 1904 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 47: /* record: id "=" exp  */
#line 160 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.record) = A_Record(LOC((yylsp[-2])), (yyvsp[-2].id), (yyvsp[0].exp)); }
#line 1910 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 48: /* decs: decs_  */
#line 162 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.decs) = A_DecsReversed((yyvsp[0].decs)); }
#line 1916 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 49: /* decs_: %empty  */
#line 164 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.decs) = NULL; }
#line 1922 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 50: /* decs_: decs_ dec  */
#line 165 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.decs) = A_Decs((yyvsp[0].dec), (yyvsp[-1].decs)); }
#line 1928 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 51: /* dec: typedec  */
#line 167 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = (yyvsp[0].dec); }
#line 1934 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 52: /* dec: vardec  */
#line 168 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = (yyvsp[0].dec); }
#line 1940 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 53: /* dec: funcdec  */
#line 169 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = (yyvsp[0].dec); }
#line 1946 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 54: /* typedec: "type" id "=" ty  */
#line 171 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = A_TypeDec(LOC((yylsp[-3])), (yyvsp[-2].id), (yyvsp[0].ty)); }
#line 1952 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 55: /* ty: id  */
#line 173 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.ty) = A_NamedTy(LOC((yylsp[0])), (yyvsp[0].id)); }
#line 1958 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 56: /* ty: "array" "of" id  */
#line 174 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.ty) = A_ArrayTy(LOC((yylsp[-2])), (yyvsp[0].id)); }
#line 1964 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 57: /* ty: "{" tyfields "}"  */
#line 175 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.ty) = A_RecordTy(LOC((yylsp[-2])), (yyvsp[-1].tyfields)); }
#line 1970 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 58: /* tyfields: %empty  */
#line 177 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.tyfields) = NULL; }
#line 1976 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 59: /* tyfields: tyfields_  */
#line 178 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.tyfields) = A_TyFieldsReversed((yyvsp[0].tyfields)); }
#line 1982 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 60: /* tyfields_: tyfield  */
#line 180 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.tyfields) = A_TyFields((yyvsp[0].tyfield), NULL); }
#line 1988 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 61: /* tyfields_: tyfields_ "," tyfield  */
#line 181 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.tyfields) = A_TyFields((yyvsp[0].tyfield), (yyvsp[-2].tyfields)); }
#line 1994 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 62: /* tyfield: id ":" id  */
#line 183 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.tyfield) = A_TyField(LOC((yylsp[-2])), (yyvsp[-2].id), (yyvsp[0].id)); }
#line 2000 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 63: /* vardec: "var" id ":=" exp  */
#line 185 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = A_VarDec(LOC((yylsp[-3])), (yyvsp[-2].id), NULL, (yyvsp[0].exp)); }
#line 2006 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 64: /* vardec: "var" id ":" id ":=" exp  */
#line 186 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = A_VarDec(LOC((yylsp[-5])), (yyvsp[-4].id), (yyvsp[-2].id), (yyvsp[0].exp)); }
#line 2012 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 65: /* funcdec: "function" id "(" tyfields ")" "=" exp  */
#line 189 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = A_FuncDec(LOC((yylsp[-6])), (yyvsp[-5].id), (yyvsp[-3].tyfields), NULL, (yyvsp[0].exp)); }
#line 2018 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 66: /* funcdec: "function" id "(" tyfields ")" ":" id "=" exp  */
#line 191 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.dec) = A_FuncDec(LOC((yylsp[-8])), (yyvsp[-7].id), (yyvsp[-5].tyfields), (yyvsp[-2].id), (yyvsp[0].exp)); }
#line 2024 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;

  case 67: /* id: ID  */
#line 193 "/Users/mangonob/Developer/ctiger/src/parser.yy"
                                                { (yyval.id) = A_Id(LOC((yylsp[0])), S_Symbol((yyvsp[0].idval))); (yyloc) = (yylsp[0]); }
#line 2030 "/Users/mangonob/Developer/ctiger/src/parser.c"
    break;


#line 2034 "/Users/mangonob/Developer/ctiger/src/parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (input, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc, input);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, input);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (input, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, input);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, input);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 195 "/Users/mangonob/Developer/ctiger/src/parser.yy"


void yyerror(FILE *input, const char *s) {
    fprintf(stderr, "parser error: %s at line: %d, column: %d\n", s, yylloc.first_line, yylloc.first_column);
}
