/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 2 "parser.ypp"

	#include <stdio.h>
	#include <stdlib.h>

    	#include "ast.hpp"
    	#include "primitive.hpp"
    	#include "symtab.hpp"

	#define YYDEBUG 1

    	extern Program_ptr ast;
	int yylex(void);
	void yyerror(const char *);


/* Line 268 of yacc.c  */
#line 87 "parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     COMMENT = 258,
     EQ = 259,
     DEQ = 260,
     NE = 261,
     LT = 262,
     LE = 263,
     GT = 264,
     GE = 265,
     PLUS = 266,
     MINUS = 267,
     DIVIDE = 268,
     AND = 269,
     OR = 270,
     NOT = 271,
     SEMI = 272,
     COMMA = 273,
     ABS = 274,
     OFUNC = 275,
     CFUNC = 276,
     OPAREN = 277,
     CPAREN = 278,
     OARRAY = 279,
     CARRAY = 280,
     BOOLEAN = 281,
     IF = 282,
     ELSE = 283,
     WHILE = 284,
     FOR = 285,
     FUNCTION = 286,
     INTARRAY = 287,
     RETURN = 288,
     TRUE = 289,
     FALSE = 290,
     INT = 291,
     DECIMAL = 292,
     HEX = 293,
     OCT = 294,
     BIN = 295,
     ZERO = 296,
     VAR = 297,
     MULT = 298,
     LITERAL = 299,
     NUM = 300,
     IDENT = 301,
     COLON = 302,
     UN_MINUS = 303
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 177 "parser.cpp"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   376

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  140

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    20,    22,    24,    26,
      27,    31,    33,    37,    41,    43,    48,    52,    53,    56,
      62,    64,    66,    71,    72,    75,    83,    88,    96,   107,
     109,   111,   119,   131,   132,   134,   142,   143,   146,   147,
     151,   155,   160,   164,   168,   172,   176,   180,   184,   188,
     192,   196,   200,   204,   206,   208,   211,   213,   215,   218,
     222,   224,   226,   228,   230,   232,   237
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    -1,    -1,    51,    52,    -1,    31,
      44,    22,    54,    23,    47,    53,    20,    58,    21,    -1,
      26,    -1,    36,    -1,    55,    -1,    -1,    55,    17,    56,
      -1,    56,    -1,    57,    47,    62,    -1,    57,    18,    44,
      -1,    44,    -1,    60,    51,    63,    59,    -1,    33,    70,
      17,    -1,    -1,    60,    61,    -1,    42,    57,    47,    62,
      17,    -1,    26,    -1,    36,    -1,    32,    24,    45,    25,
      -1,    -1,    63,    64,    -1,    44,     4,    44,    22,    68,
      23,    17,    -1,    44,     4,    70,    17,    -1,    44,    24,
      70,    25,     4,    70,    17,    -1,    44,    24,    70,    25,
       4,    44,    22,    68,    23,    17,    -1,    65,    -1,    67,
      -1,    27,    22,    70,    23,    20,    66,    21,    -1,    27,
      22,    70,    23,    20,    66,    21,    28,    20,    66,    21,
      -1,    -1,    63,    -1,    29,    22,    70,    23,    20,    66,
      21,    -1,    -1,    70,    69,    -1,    -1,    69,    18,    70,
      -1,    70,    11,    70,    -1,    70,    19,    19,    70,    -1,
      70,    14,    70,    -1,    70,     9,    70,    -1,    70,    10,
      70,    -1,    70,     7,    70,    -1,    70,     8,    70,    -1,
      70,     6,    70,    -1,    70,     5,    70,    -1,    70,    12,
      70,    -1,    70,    13,    70,    -1,    70,    43,    70,    -1,
      22,    70,    23,    -1,    37,    -1,    71,    -1,    12,    70,
      -1,    34,    -1,    35,    -1,    16,    70,    -1,    19,    70,
      19,    -1,    38,    -1,    39,    -1,    40,    -1,    45,    -1,
      41,    -1,    44,    24,    70,    25,    -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    90,    90,    98,    99,   107,   118,   122,   128,   133,
     138,   143,   150,   156,   161,   168,   180,   187,   190,   197,
     203,   207,   211,   218,   221,   229,   233,   237,   241,   245,
     250,   283,   287,   298,   301,   307,   332,   335,   341,   344,
     352,   356,   360,   364,   368,   372,   376,   380,   384,   388,
     392,   396,   400,   404,   408,   412,   416,   422,   426,   430,
     440,   441,   442,   443,   448,   449,   453
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMENT", "EQ", "DEQ", "NE", "LT", "LE",
  "GT", "GE", "PLUS", "MINUS", "DIVIDE", "AND", "OR", "NOT", "SEMI",
  "COMMA", "ABS", "OFUNC", "CFUNC", "OPAREN", "CPAREN", "OARRAY", "CARRAY",
  "BOOLEAN", "IF", "ELSE", "WHILE", "FOR", "FUNCTION", "INTARRAY",
  "RETURN", "TRUE", "FALSE", "INT", "DECIMAL", "HEX", "OCT", "BIN", "ZERO",
  "VAR", "MULT", "LITERAL", "NUM", "IDENT", "COLON", "UN_MINUS", "$accept",
  "Program", "Functions", "Function", "Returntype", "params", "params_",
  "param", "var_list", "bodyoffunction", "ReturnStatement", "variabledec",
  "decs", "Type", "Statements", "Statement", "if", "bodyofnested", "while",
  "expr_list", "more_expr_list", "expression", "Term", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    53,    53,    54,    54,
      55,    55,    56,    57,    57,    58,    59,    60,    60,    61,
      62,    62,    62,    63,    63,    64,    64,    64,    64,    64,
      64,    65,    65,    66,    66,    67,    68,    68,    69,    69,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,    10,     1,     1,     1,     0,
       3,     1,     3,     3,     1,     4,     3,     0,     2,     5,
       1,     1,     4,     0,     2,     7,     4,     7,    10,     1,
       1,     7,    11,     0,     1,     7,     0,     2,     0,     3,
       3,     4,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     2,     1,     1,     2,     3,
       1,     1,     1,     1,     1,     4,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,     0,     4,     0,     9,    14,     0,
       8,    11,     0,     0,     0,     0,     0,     0,    10,    13,
      20,     0,    21,    12,     6,     7,     0,     0,    17,     0,
       0,     3,    22,     5,     0,    23,    18,     0,     0,     0,
       0,     0,     0,     0,    15,    24,    29,    30,     0,     0,
       0,     0,     0,     0,     0,    56,    57,    53,    60,    61,
      62,    64,    66,    63,     0,    54,     0,     0,    19,     0,
       0,    55,    58,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,     0,    66,
       0,     0,     0,     0,    59,    52,     0,    48,    47,    45,
      46,    43,    44,    40,    49,    50,    42,     0,    51,    36,
      26,     0,    23,    23,    65,    41,     0,    38,     0,    34,
       0,     0,     0,    37,    66,     0,    31,    35,    25,     0,
      36,    27,     0,    39,     0,    23,     0,     0,    28,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,    26,     9,    10,    11,    12,    30,
      44,    31,    36,    23,   119,    45,    46,   120,    47,   116,
     123,   117,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -109
static const yytype_int16 yypact[] =
{
    -109,    32,    17,  -109,     7,  -109,    41,    24,  -109,    49,
      60,  -109,   -17,    22,    24,    35,    52,   -23,  -109,  -109,
    -109,    56,  -109,  -109,  -109,  -109,    62,    38,  -109,    61,
      64,    47,  -109,  -109,    24,    17,  -109,   -16,    37,    52,
      80,    81,   287,    25,  -109,  -109,  -109,  -109,    88,   287,
     287,   287,   287,   287,   287,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,    83,  -109,     9,  -109,   317,   287,  -109,    48,
      87,    85,   205,   226,   106,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,  -109,    89,   287,   -18,
     126,   145,   101,   102,    89,  -109,   166,   277,   277,   244,
     244,   244,   244,    31,    31,    85,   265,   287,    85,   287,
    -109,   105,  -109,  -109,  -109,   205,   100,   205,   331,    46,
     103,   107,   109,   123,    23,   187,    99,  -109,  -109,   287,
     287,  -109,   122,   205,   121,  -109,   129,   127,  -109,  -109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -109,  -109,   116,  -109,  -109,  -109,  -109,   146,   128,  -109,
    -109,  -109,  -109,   124,   130,  -109,  -109,  -108,  -109,    36,
    -109,   -42,  -109
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      64,    15,    15,    24,   109,   121,    75,    69,    70,    71,
      72,    73,    74,    25,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    90,    91,    86,   137,    87,    66,
      16,    39,     3,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    84,   130,   108,    75,     4,    67,
      87,     6,    88,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,     7,    40,   115,    41,    87,     8,    17,
      42,    92,    13,    40,    88,    41,   125,    14,    20,    19,
      27,    43,    28,    29,    21,    33,    32,   133,    22,    34,
      43,    88,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    49,    50,    87,    68,    87,    75,   107,   118,
      93,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,   112,   113,   122,   126,    87,   128,   132,   127,    95,
      88,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,   129,   135,   110,   136,    87,   138,    35,   139,    88,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      18,     0,    37,    48,    87,    38,   134,     0,     0,    88,
     111,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,     0,     0,     0,     0,    87,     0,     0,    88,     0,
       0,   114,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,     0,     0,   131,     0,    87,     0,     0,    88,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
       0,     0,     0,     0,    87,     0,     0,     0,     0,     0,
      88,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,     0,     0,     0,     0,    94,     0,     0,    88,    76,
      77,    -1,    -1,    -1,    -1,    82,    83,    84,     0,     0,
       0,     0,     0,    87,     0,     0,     0,     0,     0,    88,
      76,    77,    78,    79,    80,    81,    82,    83,    84,     0,
       0,     0,    76,    77,    87,     0,     0,    88,    82,    83,
      84,     0,     0,     0,     0,     0,    87,     0,     0,    51,
       0,     0,     0,    52,     0,     0,    53,     0,    88,    54,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      88,    55,    56,     0,    57,    58,    59,    60,    61,    51,
       0,    62,    63,    52,     0,     0,    53,     0,     0,    54,
       0,     0,     0,    51,     0,     0,     0,    52,     0,     0,
      53,    55,    56,    54,    57,    58,    59,    60,    61,     0,
       0,    89,    63,     0,     0,    55,    56,     0,    57,    58,
      59,    60,    61,     0,     0,   124,    63
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-109))

#define yytable_value_is_error(yytable_value) \
  ((yytable_value) == (-1))

static const yytype_int16 yycheck[] =
{
      42,    18,    18,    26,    22,   113,    24,    49,    50,    51,
      52,    53,    54,    36,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    66,    67,    17,   135,    19,     4,
      47,    47,     0,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    13,    22,    88,    24,    31,    24,
      19,    44,    43,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    22,    27,   107,    29,    19,    44,    47,
      33,    23,    23,    27,    43,    29,   118,    17,    26,    44,
      24,    44,    20,    45,    32,    21,    25,   129,    36,    42,
      44,    43,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    22,    22,    19,    17,    19,    24,    19,     4,
      23,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    20,    20,    23,    21,    19,    17,    28,    21,    23,
      43,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    18,    20,    17,    23,    19,    17,    31,    21,    43,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      14,    -1,    34,    39,    19,    35,   130,    -1,    -1,    43,
      25,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    43,    -1,
      -1,    25,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,    17,    -1,    19,    -1,    -1,    43,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,
      43,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    19,    -1,    -1,    43,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,    43,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,    -1,     5,     6,    19,    -1,    -1,    43,    11,    12,
      13,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    12,
      -1,    -1,    -1,    16,    -1,    -1,    19,    -1,    43,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      43,    34,    35,    -1,    37,    38,    39,    40,    41,    12,
      -1,    44,    45,    16,    -1,    -1,    19,    -1,    -1,    22,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    16,    -1,    -1,
      19,    34,    35,    22,    37,    38,    39,    40,    41,    -1,
      -1,    44,    45,    -1,    -1,    34,    35,    -1,    37,    38,
      39,    40,    41,    -1,    -1,    44,    45
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    51,     0,    31,    52,    44,    22,    44,    54,
      55,    56,    57,    23,    17,    18,    47,    47,    56,    44,
      26,    32,    36,    62,    26,    36,    53,    24,    20,    45,
      58,    60,    25,    21,    42,    51,    61,    57,    63,    47,
      27,    29,    33,    44,    59,    64,    65,    67,    62,    22,
      22,    12,    16,    19,    22,    34,    35,    37,    38,    39,
      40,    41,    44,    45,    70,    71,     4,    24,    17,    70,
      70,    70,    70,    70,    70,    24,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    17,    19,    43,    44,
      70,    70,    23,    23,    19,    23,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    19,    70,    22,
      17,    25,    20,    20,    25,    70,    68,    70,     4,    63,
      66,    66,    23,    69,    44,    70,    21,    21,    17,    18,
      22,    17,    28,    70,    68,    20,    23,    66,    17,    21
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
      int yyn = yypact[*yyssp];
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 91 "parser.ypp"
    {
		ast = new Program((yyvsp[(1) - (1)]).u_func_list);
		//printf("success");
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 98 "parser.ypp"
    {(yyval).u_func_list = new list<Func_ptr>();}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 100 "parser.ypp"
    {
		//$1.u_func_list -> push_back($2.u_func);
		//$$ = $1;
		(yyval).u_func_list=(yyvsp[(1) - (2)]).u_func_list; (yyval).u_func_list -> push_back((yyvsp[(2) - (2)]).u_func);
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 108 "parser.ypp"
    {
		(yyval).u_func = new Func(
		(yyvsp[(7) - (10)]).u_type,
		new SymName((yyvsp[(2) - (10)]).u_base_charptr),
		(yyvsp[(4) - (10)]).u_decl_list,
		(yyvsp[(9) - (10)]).u_function_block);
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 119 "parser.ypp"
    {
		(yyval).u_type = new TBoolean();
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 123 "parser.ypp"
    {
		(yyval).u_type = new TInteger();
	}
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 129 "parser.ypp"
    {
		 (yyval) = (yyvsp[(1) - (1)]); 
	}
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 133 "parser.ypp"
    { 
		(yyval).u_decl_list = new list<Decl_ptr>(); 
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 139 "parser.ypp"
    {
		(yyvsp[(1) - (3)]).u_decl_list -> push_back((yyvsp[(3) - (3)]).u_decl); 
		(yyval) = (yyvsp[(1) - (3)]);
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 144 "parser.ypp"
    {
		(yyval).u_decl_list = new list<Decl_ptr>();
		(yyval).u_decl_list -> push_back((yyvsp[(1) - (1)]).u_decl);
	}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 151 "parser.ypp"
    {
		(yyval).u_decl = new Decl((yyvsp[(3) - (3)]).u_type, (yyvsp[(1) - (3)]).u_symname_list);
	}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 157 "parser.ypp"
    {
		(yyvsp[(1) - (3)]).u_symname_list -> push_back(new SymName((yyvsp[(3) - (3)]).u_base_charptr));
		(yyval) = (yyvsp[(1) - (3)]);
	}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 162 "parser.ypp"
    {
		(yyval).u_symname_list = new list<SymName_ptr>();
		(yyval).u_symname_list -> push_back(new SymName((yyvsp[(1) - (1)]).u_base_charptr));
	}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 169 "parser.ypp"
    {
		(yyval).u_function_block = new Function_block(
		new list<Decl_ptr>(),
		new list<Func_ptr>(),
		new list<Stat_ptr>(),
		new Return((yyvsp[(4) - (4)]).u_expr));
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 181 "parser.ypp"
    {
		(yyval).u_expr = (yyvsp[(2) - (3)]).u_expr;
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 187 "parser.ypp"
    {
		(yyval).u_decl_list = new list<Decl_ptr>();
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 191 "parser.ypp"
    {
		(yyval).u_decl_list->push_back((yyvsp[(2) - (2)]).u_decl);
		(yyval) = (yyvsp[(1) - (2)]);
	}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 198 "parser.ypp"
    {
		(yyval).u_decl = new Decl((yyvsp[(4) - (5)]).u_type, (yyvsp[(2) - (5)]).u_symname_list);
	}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 204 "parser.ypp"
    {
		(yyval).u_type = new TBoolean();
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 208 "parser.ypp"
    {
		(yyval).u_type = new TInteger();
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 212 "parser.ypp"
    {
		(yyval).u_type = new TIntArray(new Primitive((yyvsp[(3) - (4)]).u_base_int));
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 218 "parser.ypp"
    {
		(yyval).u_stat_list = new list<Stat_ptr>();
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 222 "parser.ypp"
    {
		(yyvsp[(1) - (2)]).u_stat_list -> push_back((yyvsp[(2) - (2)]).u_stat); 
		(yyval) = (yyvsp[(1) - (2)]);
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 230 "parser.ypp"
    {
		(yyval).u_stat = new Call(new SymName((yyvsp[(1) - (7)]).u_base_charptr), new SymName((yyvsp[(3) - (7)]).u_base_charptr), (yyvsp[(5) - (7)]).u_expr_list);
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 234 "parser.ypp"
    {
		(yyval).u_stat = new Assignment(new SymName((yyvsp[(1) - (4)]).u_base_charptr), (yyvsp[(3) - (4)]).u_expr);
	}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 238 "parser.ypp"
    {
		(yyval).u_stat = new ArrayAssignment(new SymName((yyvsp[(1) - (7)]).u_base_charptr), (yyvsp[(3) - (7)]).u_expr, (yyvsp[(6) - (7)]).u_expr);
	}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 242 "parser.ypp"
    {
		(yyval).u_stat = new ArrayCall(new SymName((yyvsp[(1) - (10)]).u_base_charptr), (yyvsp[(3) - (10)]).u_expr, new SymName((yyvsp[(6) - (10)]).u_base_charptr), (yyvsp[(8) - (10)]).u_expr_list);
	}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 246 "parser.ypp"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 251 "parser.ypp"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 284 "parser.ypp"
    {
		(yyval).u_stat = new IfNoElse((yyvsp[(3) - (7)]).u_expr, (yyvsp[(6) - (7)]).u_nested_block);
	}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 288 "parser.ypp"
    {
		(yyval).u_stat = new IfWithElse((yyvsp[(3) - (11)]).u_expr, (yyvsp[(6) - (11)]).u_nested_block, (yyvsp[(10) - (11)]).u_nested_block);
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 298 "parser.ypp"
    {
		(yyval).u_nested_block = new Nested_block( new list<Stat_ptr>());
	}
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 302 "parser.ypp"
    {
		(yyval).u_nested_block = new Nested_block( (yyvsp[(1) - (1)]).u_stat_list);
	}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 308 "parser.ypp"
    {	
		(yyval).u_stat = new WhileLoop((yyvsp[(3) - (7)]).u_expr, (yyvsp[(6) - (7)]).u_nested_block);
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 332 "parser.ypp"
    {
		(yyval).u_expr_list = new list<Expr_ptr>();
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 336 "parser.ypp"
    {
		(yyval).u_expr_list = (yyvsp[(2) - (2)]).u_expr_list; (yyval).u_expr_list -> push_back((yyvsp[(1) - (2)]).u_expr);
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 341 "parser.ypp"
    {
		(yyval).u_expr_list = new list<Expr_ptr>();
	}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 345 "parser.ypp"
    {
		(yyval).u_expr_list = (yyvsp[(1) - (3)]).u_expr_list; (yyval).u_expr_list -> push_back((yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 353 "parser.ypp"
    {
		(yyval).u_expr = new Plus((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 357 "parser.ypp"
    {
		(yyval).u_expr = new Or((yyvsp[(1) - (4)]).u_expr, (yyvsp[(4) - (4)]).u_expr);
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 361 "parser.ypp"
    {
	       (yyval).u_expr = new And((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 365 "parser.ypp"
    {
                (yyval).u_expr = new Gt((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 369 "parser.ypp"
    {
                (yyval).u_expr = new Gteq((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 373 "parser.ypp"
    {
                (yyval).u_expr = new Lt((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 377 "parser.ypp"
    {
                (yyval).u_expr = new Lteq((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 381 "parser.ypp"
    {
                (yyval).u_expr = new Noteq((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 385 "parser.ypp"
    {
                (yyval).u_expr = new Compare((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 389 "parser.ypp"
    {
		(yyval).u_expr = new Minus((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 393 "parser.ypp"
    {
		(yyval).u_expr = new Div((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 397 "parser.ypp"
    {
		(yyval).u_expr = new Times((yyvsp[(1) - (3)]).u_expr, (yyvsp[(3) - (3)]).u_expr);
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 401 "parser.ypp"
    {
		(yyval).u_expr = (yyvsp[(2) - (3)]).u_expr;
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 405 "parser.ypp"
    { 
		(yyval).u_expr = new IntLit(new Primitive((yyvsp[(1) - (1)]).u_base_int));
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 409 "parser.ypp"
    {
		(yyval) = (yyvsp[(1) - (1)]);
	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 413 "parser.ypp"
    {	
		(yyval).u_expr = new Uminus((yyvsp[(1) - (2)]).u_expr);
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 417 "parser.ypp"
    {

		(yyval).u_expr = new BoolLit(new Primitive(1));
	 	//printf("got to TRURE");
	}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 423 "parser.ypp"
    {
		(yyval).u_expr = new BoolLit(new Primitive(0)); 
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 427 "parser.ypp"
    {
		(yyval).u_expr = new Not((yyvsp[(2) - (2)]).u_expr);
	}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 431 "parser.ypp"
    {
		(yyval).u_expr = new Magnitude((yyvsp[(2) - (3)]).u_expr);
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 444 "parser.ypp"
    {
		(yyval).u_expr = new IntLit(new Primitive((yyvsp[(1) - (1)]).u_base_int));
		//printf("got to int");
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 450 "parser.ypp"
    {
		(yyval).u_expr = new ArrayAccess(new SymName((yyvsp[(1) - (4)]).u_base_charptr), (yyvsp[(3) - (4)]).u_expr);
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 454 "parser.ypp"
    {
		(yyval).u_expr = new Ident(new SymName((yyvsp[(1) - (1)]).u_base_charptr));
	}
    break;



/* Line 1806 of yacc.c  */
#line 2134 "parser.cpp"
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
		      yytoken, &yylval);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 2067 of yacc.c  */
#line 467 "parser.ypp"


/*You shouldn't have to do anything past this*/

extern int yylineno;

void yyerror(const char *s) {
	fprintf(stderr, "%s at line %d\n", s, yylineno);
	exit(0);
}





