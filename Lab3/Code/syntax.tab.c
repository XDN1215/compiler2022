/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "./syntax.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>

void yyerror(char* msg, ...);
#include "lex.yy.c"

int syntaxerror=0;
struct TreeNode* root = NULL;

#line 84 "./syntax.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    SEMI = 259,
    COMMA = 260,
    LC = 261,
    RC = 262,
    INT = 263,
    OCTAL = 264,
    HEXAL = 265,
    illegal_INT = 266,
    illegal_OCTAL = 267,
    illegal_HEXAL = 268,
    FLOAT = 269,
    expFLOAT = 270,
    illegal_FLOAT = 271,
    illegal_expFLOAT = 272,
    TYPE = 273,
    STRUCT = 274,
    RETURN = 275,
    IF = 276,
    ELSE = 277,
    WHILE = 278,
    ASSIGNOP = 279,
    OR = 280,
    AND = 281,
    RELOP = 282,
    PLUS = 283,
    MINUS = 284,
    STAR = 285,
    DIV = 286,
    NOT = 287,
    DOT = 288,
    LP = 289,
    RP = 290,
    LB = 291,
    RB = 292,
    HIGHER_THAN_MINUS = 293,
    LOWER_THAN_ELSE = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "./syntax.y"

    struct TreeNode* nodep;

#line 180 "./syntax.tab.c"

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
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   745

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  193

#define YYUNDEFTOK  2
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    57,    57,    60,    61,    64,    65,    66,    67,    69,
      70,    71,    73,    75,    76,    77,    81,    82,    84,    90,
      91,    94,    95,    98,   103,   104,   107,   111,   112,   114,
     118,   119,   121,   122,   122,   126,   127,   130,   134,   137,
     140,   141,   144,   145,   146,   147,   148,   149,   153,   154,
     155,   156,   157,   161,   162,   163,   164,   165,   166,   167,
     171,   172,   175,   178,   179,   183,   184,   188,   191,   192,
     196,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   244,   245
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "SEMI", "COMMA", "LC", "RC", "INT",
  "OCTAL", "HEXAL", "illegal_INT", "illegal_OCTAL", "illegal_HEXAL",
  "FLOAT", "expFLOAT", "illegal_FLOAT", "illegal_expFLOAT", "TYPE",
  "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "ASSIGNOP", "OR", "AND",
  "RELOP", "PLUS", "MINUS", "STAR", "DIV", "NOT", "DOT", "LP", "RP", "LB",
  "RB", "HIGHER_THAN_MINUS", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "$@1", "VarList", "ParamDec",
  "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp",
  "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF (-90)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-62)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     117,   644,   -90,    15,    24,   -90,   117,   191,   -90,   -90,
     -90,   -90,    50,   123,   133,   -90,   -90,   -90,    22,    52,
     -90,    57,    27,   159,   -90,   646,   152,   -90,    53,    53,
     -90,    20,   -90,   -90,   164,     9,   -90,   126,   -90,   -90,
     179,   165,   180,    53,   -90,   141,   164,   158,   167,   178,
     -90,   185,   -90,   162,   184,   -90,   -90,    65,    -9,   137,
     240,   -90,   -90,   210,   214,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   222,     0,    32,   249,   276,
     303,   -90,   246,   141,    49,   211,   -90,    53,   -90,   -90,
     -90,   -90,   -90,   225,   627,   627,   -90,   -90,   225,   -90,
     111,   251,    80,   168,   330,    29,   357,   -90,   186,   -90,
     186,   232,   659,   -90,   -90,   264,   -90,   384,   411,   438,
     465,   492,   519,   546,   573,   266,   600,   -90,   -90,    17,
     -90,   698,   698,   -90,     5,   -90,   595,   235,   -90,   -90,
     -90,   195,   -90,   236,   672,   -90,   195,   237,   685,   -90,
     -90,   -90,   -90,   698,   -90,   709,   -90,   213,   -90,    66,
     -90,   101,   -90,   101,   -90,   186,   -90,   186,   -90,    55,
     645,   -90,   -90,   627,   -90,   -90,   195,   195,   -90,   195,
     195,   -90,   -90,   -90,   -90,   252,   253,   -90,   -90,   195,
     195,   -90,   -90
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    19,    25,     0,     2,     0,     0,    20,    11,
      15,    14,     0,    26,     0,    22,     1,     3,     0,    27,
       6,     0,    16,     0,    10,     0,     0,     9,    61,     0,
      13,     0,     5,    27,     0,     0,    18,     0,     8,     7,
       0,     0,     0,    61,    39,     0,     0,     0,    36,     0,
      31,     0,    17,     0,     0,    12,    23,     0,    68,     0,
      65,    21,    60,     0,    86,    87,    89,    90,    94,    92,
      93,    88,    91,    95,    96,     0,     0,     0,     0,     0,
       0,    43,     0,     0,     0,    37,    33,     0,    32,    30,
      29,    28,    63,     0,     0,     0,    64,    62,     0,    49,
       0,     0,     0,     0,     0,     0,     0,   106,    80,   107,
      81,     0,     0,    38,    40,    48,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    34,    35,     0,
      67,    70,    69,    66,     0,    83,   113,     0,    51,    52,
      44,     0,    55,     0,     0,    59,     0,     0,     0,   105,
      79,    50,    97,    71,    99,    73,    98,    72,   100,    74,
     101,    75,   102,    76,   103,    77,   104,    78,    85,     0,
       0,   109,   108,     0,    82,    56,     0,     0,    58,     0,
       0,   111,   110,    84,   112,    53,    45,    57,    47,     0,
       0,    54,    46
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   267,   -90,    81,     6,   -90,   -90,   -90,   -33,
     -90,   -90,   -29,   -90,    -7,   193,   -89,    40,   -90,   -31,
     -90,   -75,   107
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,     5,     6,    21,    41,     8,    14,    15,    22,
      23,   127,    47,    48,    81,    82,    83,    42,    43,    59,
      60,    84,   137
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     102,   103,    51,   108,   110,   112,     7,    12,    58,   171,
      53,    30,     7,    85,   142,    95,    39,    54,    13,   131,
     132,    49,    93,    26,    16,   136,    27,    35,    28,   144,
      33,   148,    34,   105,   104,    46,   145,    46,     2,     3,
     172,    94,   153,   155,   157,   159,   161,   163,   165,   167,
     115,   170,   175,   116,    24,    50,    29,   178,   128,   181,
      58,    32,   130,    35,   146,    58,   106,   133,    45,    92,
      93,     2,     3,   117,   118,   119,   120,   121,   122,   123,
     124,   139,   125,    62,   140,   126,    31,   185,   186,    94,
     187,   188,   182,    46,   121,   122,   123,   124,   136,   125,
     191,   192,   126,    36,   117,   118,   119,   120,   121,   122,
     123,   124,   134,   125,    64,    52,   126,    -4,     1,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,   -24,
      55,   123,   124,    44,   125,     2,     3,   126,    96,    25,
      78,    97,    63,    79,    64,    80,   135,    28,   -41,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    44,
      37,    75,    76,    38,    77,    28,    57,    33,    33,    63,
      78,    64,    87,    79,    28,    80,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    56,    61,    75,    76,
     141,    77,    18,    86,    19,    20,    63,    78,    64,    90,
      79,    28,    80,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    88,    99,    75,    76,    44,    77,   125,
      89,    91,   126,   101,    78,    64,   129,    79,    33,    80,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     120,   121,   122,   123,   124,    98,   125,    35,   100,   126,
     107,    78,    64,   113,    79,   138,    80,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   149,   151,   168,
     174,   176,   179,    17,   189,   190,   114,   109,    78,    64,
     184,    79,     0,    80,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,    78,    64,     0,    79,     0,
      80,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   143,    78,    64,     0,    79,     0,    80,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   147,    78,
      64,     0,    79,     0,    80,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,    78,    64,     0,    79,
       0,    80,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,    78,    64,     0,    79,     0,    80,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   156,
      78,    64,     0,    79,     0,    80,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,    78,    64,     0,
      79,     0,    80,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   160,    78,    64,     0,    79,     0,    80,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     162,    78,    64,     0,    79,     0,    80,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   164,    78,    64,
       0,    79,     0,    80,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   166,    78,    64,     0,    79,     0,
      80,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   169,    78,    64,     0,    79,     0,    80,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,   117,
     118,   119,   120,   121,   122,   123,   124,     0,   125,    78,
      64,   126,    79,     0,    80,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     0,     0,    40,     9,     0,
       0,    10,     0,   -61,     0,     0,    78,     0,     0,    79,
       0,    80,     2,     3,     2,     3,     0,     0,     0,   117,
     118,   119,   120,   121,   122,   123,   124,     0,   125,    11,
       0,   126,   183,   117,   118,   119,   120,   121,   122,   123,
     124,     0,   125,     0,   150,   126,   117,   118,   119,   120,
     121,   122,   123,   124,     0,   125,     0,   177,   126,   117,
     118,   119,   120,   121,   122,   123,   124,     0,   125,     0,
     180,   126,   117,   118,   119,   120,   121,   122,   123,   124,
       0,   125,     0,     0,   126,   119,   120,   121,   122,   123,
     124,     0,   125,     0,     0,   126
};

static const yytype_int16 yycheck[] =
{
      75,     1,    31,    78,    79,    80,     0,     1,    41,     4,
       1,    18,     6,    46,   103,    24,    23,     8,     3,    94,
      95,     1,     5,     1,     0,   100,     4,    36,     6,   104,
       3,   106,     5,     1,    34,    29,     7,    31,    18,    19,
      35,    24,   117,   118,   119,   120,   121,   122,   123,   124,
       1,   126,   141,     4,     4,    35,    34,   146,    87,     4,
      93,     4,    93,    36,    35,    98,    34,    98,    28,     4,
       5,    18,    19,    24,    25,    26,    27,    28,    29,    30,
      31,     1,    33,    43,     4,    36,    34,   176,   177,    24,
     179,   180,    37,    87,    28,    29,    30,    31,   173,    33,
     189,   190,    36,    22,    24,    25,    26,    27,    28,    29,
      30,    31,     1,    33,     3,    34,    36,     0,     1,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     6,
       4,    30,    31,     7,    33,    18,    19,    36,     1,     6,
      29,     4,     1,    32,     3,    34,    35,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     7,
       1,    20,    21,     4,    23,     6,     1,     3,     3,     1,
      29,     3,     5,    32,     6,    34,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,     7,     7,    20,    21,
      22,    23,     1,    35,     3,     4,     1,    29,     3,    37,
      32,     6,    34,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    35,     4,    20,    21,     7,    23,    33,
      35,    37,    36,     1,    29,     3,     1,    32,     3,    34,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      27,    28,    29,    30,    31,     5,    33,    36,    34,    36,
       1,    29,     3,     7,    32,     4,    34,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    35,     4,     3,
      35,    35,    35,     6,    22,    22,    83,     1,    29,     3,
     173,    32,    -1,    34,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    29,     3,    -1,    32,    -1,
      34,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    29,     3,    -1,    32,    -1,    34,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    29,
       3,    -1,    32,    -1,    34,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    29,     3,    -1,    32,
      -1,    34,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    29,     3,    -1,    32,    -1,    34,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      29,     3,    -1,    32,    -1,    34,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    29,     3,    -1,
      32,    -1,    34,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    29,     3,    -1,    32,    -1,    34,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    29,     3,    -1,    32,    -1,    34,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    29,     3,
      -1,    32,    -1,    34,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    29,     3,    -1,    32,    -1,
      34,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     1,    29,     3,    -1,    32,    -1,    34,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    29,
       3,    36,    32,    -1,    34,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    -1,    -1,     1,     4,    -1,
      -1,     7,    -1,     7,    -1,    -1,    29,    -1,    -1,    32,
      -1,    34,    18,    19,    18,    19,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    35,
      -1,    36,    37,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    35,    36,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    35,    36,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    -1,
      35,    36,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    -1,    -1,    36,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    18,    19,    41,    42,    43,    45,    46,     4,
       7,    35,    45,     3,    47,    48,     0,    42,     1,     3,
       4,    44,    49,    50,     4,     6,     1,     4,     6,    34,
      54,    34,     4,     3,     5,    36,    44,     1,     4,    54,
       1,    45,    57,    58,     7,    57,    45,    52,    53,     1,
      35,    52,    44,     1,     8,     4,     7,     1,    49,    59,
      60,     7,    57,     1,     3,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    20,    21,    23,    29,    32,
      34,    54,    55,    56,    61,    49,    35,     5,    35,    35,
      37,    37,     4,     5,    24,    24,     1,     4,     5,     4,
      34,     1,    61,     1,    34,     1,    34,     1,    61,     1,
      61,     1,    61,     7,    55,     1,     4,    24,    25,    26,
      27,    28,    29,    30,    31,    33,    36,    51,    52,     1,
      59,    61,    61,    59,     1,    35,    61,    62,     4,     1,
       4,    22,    56,     1,    61,     7,    35,     1,    61,    35,
      35,     4,     1,    61,     1,    61,     1,    61,     1,    61,
       1,    61,     1,    61,     1,    61,     1,    61,     3,     1,
      61,     4,    35,     5,    35,    56,    35,    35,    56,    35,
      35,     4,    37,    37,    62,    56,    56,    56,    56,    22,
      22,    56,    56
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    44,    45,
      45,    46,    46,    46,    47,    47,    48,    49,    49,    49,
      50,    50,    50,    51,    50,    52,    52,    53,    54,    54,
      55,    55,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    58,    58,    58,    59,    59,    59,    60,    60,
      60,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     3,
       3,     2,     4,     3,     2,     2,     1,     3,     2,     1,
       1,     5,     2,     5,     1,     0,     1,     1,     4,     4,
       4,     3,     4,     0,     5,     3,     1,     2,     4,     2,
       2,     0,     2,     1,     3,     5,     7,     5,     2,     2,
       3,     3,     3,     5,     7,     3,     4,     5,     4,     3,
       2,     0,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     4,     3,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     4,     4,
       4,     4,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
  case 2:
#line 57 "./syntax.y"
                     { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Program", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));root=(yyval.nodep);}
#line 1711 "./syntax.tab.c"
    break;

  case 3:
#line 60 "./syntax.y"
                               { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDefList" , "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 2, (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1717 "./syntax.tab.c"
    break;

  case 4:
#line 61 "./syntax.y"
      { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDefList", "null", (Value)0, 2);}
#line 1723 "./syntax.tab.c"
    break;

  case 5:
#line 64 "./syntax.y"
                                   { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDef", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 3, (yyvsp[-2].nodep), (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1729 "./syntax.tab.c"
    break;

  case 6:
#line 65 "./syntax.y"
                     { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDef", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep), 2, (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1735 "./syntax.tab.c"
    break;

  case 7:
#line 66 "./syntax.y"
                              { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDef", "null", (Value)0, 3);TreeNodeInsert((yyval.nodep), 3, (yyvsp[-2].nodep), (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1741 "./syntax.tab.c"
    break;

  case 8:
#line 67 "./syntax.y"
                            { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDef", "null", (Value)0, 4);TreeNodeInsert((yyval.nodep), 3, (yyvsp[-2].nodep), (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1747 "./syntax.tab.c"
    break;

  case 9:
#line 69 "./syntax.y"
                           {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error1");}
#line 1753 "./syntax.tab.c"
    break;

  case 10:
#line 70 "./syntax.y"
                           {yyerror("Error", 0, (yylsp[-2]).first_line, "Syntax error2");}
#line 1759 "./syntax.tab.c"
    break;

  case 11:
#line 71 "./syntax.y"
                 {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error3");}
#line 1765 "./syntax.tab.c"
    break;

  case 12:
#line 73 "./syntax.y"
                                  {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error4");}
#line 1771 "./syntax.tab.c"
    break;

  case 13:
#line 75 "./syntax.y"
                             {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error5");}
#line 1777 "./syntax.tab.c"
    break;

  case 14:
#line 76 "./syntax.y"
               {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error6");}
#line 1783 "./syntax.tab.c"
    break;

  case 15:
#line 77 "./syntax.y"
               {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error7");}
#line 1789 "./syntax.tab.c"
    break;

  case 16:
#line 81 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDecList", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1795 "./syntax.tab.c"
    break;

  case 17:
#line 82 "./syntax.y"
                              { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ExtDecList", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep), 3, (yyvsp[-2].nodep), (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1801 "./syntax.tab.c"
    break;

  case 18:
#line 84 "./syntax.y"
                        {yyerror("Error", 0, (yylsp[0]).first_line, "Syntax error9");}
#line 1807 "./syntax.tab.c"
    break;

  case 19:
#line 90 "./syntax.y"
                 { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Specifier", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1813 "./syntax.tab.c"
    break;

  case 20:
#line 91 "./syntax.y"
                      { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Specifier", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1819 "./syntax.tab.c"
    break;

  case 21:
#line 94 "./syntax.y"
                                              { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "StructSpecifier", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),5,(yyvsp[-4].nodep),(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1825 "./syntax.tab.c"
    break;

  case 22:
#line 95 "./syntax.y"
                 { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "StructSpecifier", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep), 2, (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1831 "./syntax.tab.c"
    break;

  case 23:
#line 98 "./syntax.y"
                                {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error10");}
#line 1837 "./syntax.tab.c"
    break;

  case 24:
#line 103 "./syntax.y"
            { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "OptTag", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1843 "./syntax.tab.c"
    break;

  case 25:
#line 104 "./syntax.y"
      { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "OptTag", "null", (Value)0, 2);}
#line 1849 "./syntax.tab.c"
    break;

  case 26:
#line 107 "./syntax.y"
         { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Tag", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1855 "./syntax.tab.c"
    break;

  case 27:
#line 111 "./syntax.y"
            { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "VarDec", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1861 "./syntax.tab.c"
    break;

  case 28:
#line 112 "./syntax.y"
                       { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "VarDec", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep),4,(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1867 "./syntax.tab.c"
    break;

  case 29:
#line 114 "./syntax.y"
                         {yyerror("Error", 1, (yylsp[-1]).first_line, "Syntax error after \"(\": ", (yylsp[-2]).first_line);}
#line 1873 "./syntax.tab.c"
    break;

  case 30:
#line 118 "./syntax.y"
                          { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "FunDec", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),4,(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1879 "./syntax.tab.c"
    break;

  case 31:
#line 119 "./syntax.y"
               { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "FunDec", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1885 "./syntax.tab.c"
    break;

  case 32:
#line 121 "./syntax.y"
                     {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error11");}
#line 1891 "./syntax.tab.c"
    break;

  case 33:
#line 122 "./syntax.y"
                          {}
#line 1897 "./syntax.tab.c"
    break;

  case 34:
#line 122 "./syntax.y"
                            {yyerror("Error", 0, (yylsp[-4]).first_line, "Syntax error12");}
#line 1903 "./syntax.tab.c"
    break;

  case 35:
#line 126 "./syntax.y"
                                 { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "VarList", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1909 "./syntax.tab.c"
    break;

  case 36:
#line 127 "./syntax.y"
               { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "VarList", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1915 "./syntax.tab.c"
    break;

  case 37:
#line 130 "./syntax.y"
                            { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "ParamDec", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 2, (yyvsp[-1].nodep), (yyvsp[0].nodep));}
#line 1921 "./syntax.tab.c"
    break;

  case 38:
#line 134 "./syntax.y"
                                { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "CompSt", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),4,(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1927 "./syntax.tab.c"
    break;

  case 39:
#line 137 "./syntax.y"
               {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error13");}
#line 1933 "./syntax.tab.c"
    break;

  case 40:
#line 140 "./syntax.y"
                         { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "StmtList", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),2,(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1939 "./syntax.tab.c"
    break;

  case 41:
#line 141 "./syntax.y"
      { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "StmtList", "null", (Value)0, 2);}
#line 1945 "./syntax.tab.c"
    break;

  case 42:
#line 144 "./syntax.y"
                { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Stmt", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),2,(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1951 "./syntax.tab.c"
    break;

  case 43:
#line 145 "./syntax.y"
             { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Stmt", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 1957 "./syntax.tab.c"
    break;

  case 44:
#line 146 "./syntax.y"
                      { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Stmt", "null", (Value)0, 3);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1963 "./syntax.tab.c"
    break;

  case 45:
#line 147 "./syntax.y"
                                              { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Stmt", "null", (Value)0, 4);TreeNodeInsert((yyval.nodep),5,(yyvsp[-4].nodep),(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1969 "./syntax.tab.c"
    break;

  case 46:
#line 148 "./syntax.y"
                                  { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Stmt", "null", (Value)0, 5);TreeNodeInsert((yyval.nodep),7,(yyvsp[-6].nodep),(yyvsp[-5].nodep),(yyvsp[-4].nodep),(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1975 "./syntax.tab.c"
    break;

  case 47:
#line 149 "./syntax.y"
                           { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Stmt", "null", (Value)0, 6);TreeNodeInsert((yyval.nodep),5,(yyvsp[-4].nodep),(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 1981 "./syntax.tab.c"
    break;

  case 48:
#line 153 "./syntax.y"
                {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error14");}
#line 1987 "./syntax.tab.c"
    break;

  case 49:
#line 154 "./syntax.y"
                 {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error15");}
#line 1993 "./syntax.tab.c"
    break;

  case 50:
#line 155 "./syntax.y"
                     {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error16");}
#line 1999 "./syntax.tab.c"
    break;

  case 51:
#line 156 "./syntax.y"
                        {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error17");}
#line 2005 "./syntax.tab.c"
    break;

  case 52:
#line 157 "./syntax.y"
                       {yyerror("Error", 0, (yylsp[0]).first_line, "Syntax error18");}
#line 2011 "./syntax.tab.c"
    break;

  case 53:
#line 161 "./syntax.y"
                                                {yyerror("Error", 0, (yylsp[-2]).first_line, "Syntax error19");}
#line 2017 "./syntax.tab.c"
    break;

  case 54:
#line 162 "./syntax.y"
                                    {yyerror("Error", 0, (yylsp[-4]).first_line, "Syntax error20");}
#line 2023 "./syntax.tab.c"
    break;

  case 55:
#line 163 "./syntax.y"
                                          {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error21");}
#line 2029 "./syntax.tab.c"
    break;

  case 56:
#line 164 "./syntax.y"
                         {yyerror("Error", 0, (yylsp[-2]).first_line, "Syntax error22");}
#line 2035 "./syntax.tab.c"
    break;

  case 57:
#line 165 "./syntax.y"
                             {yyerror("Error", 0, (yylsp[-3]).first_line, "Syntax error23");}
#line 2041 "./syntax.tab.c"
    break;

  case 58:
#line 166 "./syntax.y"
                          {yyerror("Error", 0, (yylsp[-2]).first_line, "Syntax error24");}
#line 2047 "./syntax.tab.c"
    break;

  case 59:
#line 167 "./syntax.y"
                     {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error25");}
#line 2053 "./syntax.tab.c"
    break;

  case 60:
#line 171 "./syntax.y"
                      { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "DefList", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),2,(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2059 "./syntax.tab.c"
    break;

  case 61:
#line 172 "./syntax.y"
      { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "DefList", "null", (Value)0, 2);}
#line 2065 "./syntax.tab.c"
    break;

  case 62:
#line 175 "./syntax.y"
                             { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Def", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2071 "./syntax.tab.c"
    break;

  case 63:
#line 178 "./syntax.y"
                           {yyerror("Error", 0, (yylsp[-1]).first_line, "Syntax error26");}
#line 2077 "./syntax.tab.c"
    break;

  case 64:
#line 179 "./syntax.y"
                              {yyerror("Error", 0, (yylsp[0]).first_line, "Syntax error27");}
#line 2083 "./syntax.tab.c"
    break;

  case 65:
#line 183 "./syntax.y"
              { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "DecList", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2089 "./syntax.tab.c"
    break;

  case 66:
#line 184 "./syntax.y"
                        { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "DecList", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2095 "./syntax.tab.c"
    break;

  case 67:
#line 188 "./syntax.y"
                          {yyerror("Error", 0, (yylsp[-2]).first_line, "Syntax error28");}
#line 2101 "./syntax.tab.c"
    break;

  case 68:
#line 191 "./syntax.y"
             { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Dec", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2107 "./syntax.tab.c"
    break;

  case 69:
#line 192 "./syntax.y"
                          { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Dec", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2113 "./syntax.tab.c"
    break;

  case 70:
#line 196 "./syntax.y"
                         {yyerror("Error", 0, (yylsp[-2]).first_line, "Syntax error29");}
#line 2119 "./syntax.tab.c"
    break;

  case 71:
#line 200 "./syntax.y"
                       { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 1);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2125 "./syntax.tab.c"
    break;

  case 72:
#line 201 "./syntax.y"
                  { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 2);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2131 "./syntax.tab.c"
    break;

  case 73:
#line 202 "./syntax.y"
                 { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 3);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2137 "./syntax.tab.c"
    break;

  case 74:
#line 203 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 4);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2143 "./syntax.tab.c"
    break;

  case 75:
#line 204 "./syntax.y"
                   { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 5);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2149 "./syntax.tab.c"
    break;

  case 76:
#line 205 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 6);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2155 "./syntax.tab.c"
    break;

  case 77:
#line 206 "./syntax.y"
                   { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 7);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2161 "./syntax.tab.c"
    break;

  case 78:
#line 207 "./syntax.y"
                  { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 8);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2167 "./syntax.tab.c"
    break;

  case 79:
#line 208 "./syntax.y"
                { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 9);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2173 "./syntax.tab.c"
    break;

  case 80:
#line 209 "./syntax.y"
                                        { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 10);TreeNodeInsert((yyval.nodep),2,(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2179 "./syntax.tab.c"
    break;

  case 81:
#line 210 "./syntax.y"
              { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 11);TreeNodeInsert((yyval.nodep),2,(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2185 "./syntax.tab.c"
    break;

  case 82:
#line 211 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 12);TreeNodeInsert((yyval.nodep),4,(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2191 "./syntax.tab.c"
    break;

  case 83:
#line 212 "./syntax.y"
               { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 13);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2197 "./syntax.tab.c"
    break;

  case 84:
#line 213 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 14);TreeNodeInsert((yyval.nodep),4,(yyvsp[-3].nodep),(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2203 "./syntax.tab.c"
    break;

  case 85:
#line 214 "./syntax.y"
                 { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 15);TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2209 "./syntax.tab.c"
    break;

  case 86:
#line 215 "./syntax.y"
         { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 16);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2215 "./syntax.tab.c"
    break;

  case 87:
#line 216 "./syntax.y"
          { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 17);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2221 "./syntax.tab.c"
    break;

  case 88:
#line 217 "./syntax.y"
            { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 18);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2227 "./syntax.tab.c"
    break;

  case 89:
#line 218 "./syntax.y"
            { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 19);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2233 "./syntax.tab.c"
    break;

  case 90:
#line 219 "./syntax.y"
            { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 20);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2239 "./syntax.tab.c"
    break;

  case 91:
#line 220 "./syntax.y"
               { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 21);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2245 "./syntax.tab.c"
    break;

  case 92:
#line 221 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 22);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2251 "./syntax.tab.c"
    break;

  case 93:
#line 222 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 23);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2257 "./syntax.tab.c"
    break;

  case 94:
#line 223 "./syntax.y"
                  { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 24);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2263 "./syntax.tab.c"
    break;

  case 95:
#line 224 "./syntax.y"
                    { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 25);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2269 "./syntax.tab.c"
    break;

  case 96:
#line 225 "./syntax.y"
                       { (yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Exp", "null", (Value)0, 26);TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2275 "./syntax.tab.c"
    break;

  case 97:
#line 227 "./syntax.y"
                         {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2281 "./syntax.tab.c"
    break;

  case 98:
#line 228 "./syntax.y"
                    {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2287 "./syntax.tab.c"
    break;

  case 99:
#line 229 "./syntax.y"
                   {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2293 "./syntax.tab.c"
    break;

  case 100:
#line 230 "./syntax.y"
                      {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2299 "./syntax.tab.c"
    break;

  case 101:
#line 231 "./syntax.y"
                     {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2305 "./syntax.tab.c"
    break;

  case 102:
#line 232 "./syntax.y"
                      {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2311 "./syntax.tab.c"
    break;

  case 103:
#line 233 "./syntax.y"
                     {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2317 "./syntax.tab.c"
    break;

  case 104:
#line 234 "./syntax.y"
                    {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2323 "./syntax.tab.c"
    break;

  case 105:
#line 235 "./syntax.y"
                  {yyerror("Error", 0, (yylsp[-1]).first_line, "Illegal expression");}
#line 2329 "./syntax.tab.c"
    break;

  case 106:
#line 236 "./syntax.y"
                  {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2335 "./syntax.tab.c"
    break;

  case 107:
#line 237 "./syntax.y"
                {yyerror("Error", 0, (yylsp[0]).first_line, "Illegal expression");}
#line 2341 "./syntax.tab.c"
    break;

  case 108:
#line 238 "./syntax.y"
                     {yyerror("Error", 0, (yylsp[-1]).first_line, "Illegal expression");}
#line 2347 "./syntax.tab.c"
    break;

  case 109:
#line 239 "./syntax.y"
                       {yyerror("Error", 0, (yylsp[-1]).first_line, "Missing \")\"");}
#line 2353 "./syntax.tab.c"
    break;

  case 110:
#line 240 "./syntax.y"
                      {yyerror("Error", 0, (yylsp[-1]).first_line, "Illegal expression");}
#line 2359 "./syntax.tab.c"
    break;

  case 111:
#line 241 "./syntax.y"
                        {yyerror("Error", 0, (yylsp[-1]).first_line, "Missing \"]\"");}
#line 2365 "./syntax.tab.c"
    break;

  case 112:
#line 244 "./syntax.y"
                      {(yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Args", "null", (Value)0, 1); TreeNodeInsert((yyval.nodep),3,(yyvsp[-2].nodep),(yyvsp[-1].nodep),(yyvsp[0].nodep));}
#line 2371 "./syntax.tab.c"
    break;

  case 113:
#line 245 "./syntax.y"
          {(yyval.nodep)=TreeNodeSet(0, (yyloc).first_line, "Args", "null", (Value)0, 2); TreeNodeInsert((yyval.nodep), 1, (yyvsp[0].nodep));}
#line 2377 "./syntax.tab.c"
    break;


#line 2381 "./syntax.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, &yylloc);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 247 "./syntax.y"


void yyerror(char* msg, ...) {
    syntaxerror=1;
    if(strcmp(msg, "Error")==0){
        va_list msgs;
        va_start(msgs, msg);
        int type = (int)(va_arg(msgs, int));
        int line=(int)(va_arg(msgs, int));
        if(type==0){
            char* msg1=(char*)(va_arg(msgs, char*));
            printf("Error type B at Line %d: %s.\n", line, msg1);
        }
        else if (type==1){
            char* msg1=(char*)(va_arg(msgs, char*));
            int line2=(int)va_arg(msgs, int);
            printf("Error type B at Line %d: %s %d.\n", line, msg1, line2);
        }
        va_end(msgs);
    }
    else if(strcmp(msg, "syntax error")!=0){
        printf("%s\n", msg);
    }
}
