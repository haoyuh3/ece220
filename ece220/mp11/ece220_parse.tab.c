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
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse ece220parse
#define yylex   ece220lex
#define yyerror ece220error
#define yylval  ece220lval
#define yychar  ece220char
#define yydebug ece220debug
#define yynerrs ece220nerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     C220_KEY_IDENT = 258,
     C220_KEY_INT = 259,
     C220_KEY_MAIN = 260,
     C220_KEY_INT_TYPE = 261,
     C220_KEY_STRING = 262,
     C220_KEY_ELSE = 263,
     C220_KEY_FOR = 264,
     C220_KEY_IF = 265,
     C220_KEY_RETURN = 266,
     C220_KEY_PRINTF = 267,
     C220_KEY_RAND = 268,
     C220_KEY_SCANF = 269,
     C220_KEY_SRAND = 270,
     C220_KEY_INCR = 271,
     C220_KEY_DECR = 272,
     C220_KEY_UNARY_NEG = 273,
     C220_KEY_DEBUG_MARKER = 274,
     C220_KEY_OR = 275,
     C220_KEY_AND = 276,
     C220_KEY_NE = 277,
     C220_KEY_EQ = 278,
     C220_KEY_GE = 279,
     C220_KEY_LE = 280,
     C220_KEY_POST_ID = 281
   };
#endif
/* Tokens.  */
#define C220_KEY_IDENT 258
#define C220_KEY_INT 259
#define C220_KEY_MAIN 260
#define C220_KEY_INT_TYPE 261
#define C220_KEY_STRING 262
#define C220_KEY_ELSE 263
#define C220_KEY_FOR 264
#define C220_KEY_IF 265
#define C220_KEY_RETURN 266
#define C220_KEY_PRINTF 267
#define C220_KEY_RAND 268
#define C220_KEY_SCANF 269
#define C220_KEY_SRAND 270
#define C220_KEY_INCR 271
#define C220_KEY_DECR 272
#define C220_KEY_UNARY_NEG 273
#define C220_KEY_DEBUG_MARKER 274
#define C220_KEY_OR 275
#define C220_KEY_AND 276
#define C220_KEY_NE 277
#define C220_KEY_EQ 278
#define C220_KEY_GE 279
#define C220_KEY_LE 280
#define C220_KEY_POST_ID 281




/* Copy the first part of user declarations.  */
#line 37 "ece220_parse.y"

    #include <stdio.h>
    #include <stdlib.h>

    #include "ece220_lex.h"
    #include "ece220_parse.h"
    #include "ece220_symtab.h"
    #define YYSTYPE ast220_t*

    extern int ece220lex ();

    void parse_program ();

    static void var_create (ast220_t* name, ast220_t* a_len);
    static void start_main ();
    static ast220_t* new_ast_node ();
    static ast220_t* new_ast_num (int32_t value);
    static ast220_t* new_ast_str (char* str);
    static ast220_t* new_ast_func (ast220_builtin_func_t id);
    static ast220_t* new_ast_op (ast220_type_t type, ast220_t* left, 
    				 ast220_t* right);

    static int32_t reading_globals;
    static int32_t global_offset;
    static int32_t local_offset;
    static int32_t has_main;

    static ast220_t* ece220_main;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 196 "ece220_parse.tab.c"

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
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   324

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   281

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,     2,     2,    33,    34,     2,
      43,    44,    31,    29,    40,    30,     2,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    39,
      25,    20,    26,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    38,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,    42,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    21,    22,    23,    24,    27,
      28,    36
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    11,    14,    18,    20,
      22,    26,    29,    31,    32,    36,    38,    44,    49,    50,
      53,    55,    57,    60,    67,    77,    81,    86,    87,    90,
      94,    95,    97,   101,   104,   107,   110,   113,   115,   118,
     120,   123,   126,   130,   134,   138,   142,   146,   150,   154,
     158,   162,   166,   170,   174,   178,   180,   184,   187,   188,
     192,   194,   199,   201,   203,   205,   207,   208,   210,   212,
     216,   218,   220
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    -1,    46,    48,    -1,    46,    55,    -1,
      -1,    47,    48,    -1,    49,    50,    39,    -1,     6,    -1,
      51,    -1,    50,    40,    51,    -1,    52,    53,    -1,     3,
      -1,    -1,    37,    54,    38,    -1,     4,    -1,    56,    41,
      47,    57,    42,    -1,    49,     5,    43,    44,    -1,    -1,
      57,    58,    -1,    59,    -1,    61,    -1,    62,    39,    -1,
      10,    43,    63,    44,    61,    60,    -1,     9,    43,    62,
      39,    63,    39,    62,    44,    61,    -1,    11,    63,    39,
      -1,    19,    43,    54,    44,    -1,    -1,     8,    61,    -1,
      41,    57,    42,    -1,    -1,    63,    -1,    66,    20,    63,
      -1,    66,    16,    -1,    66,    17,    -1,    16,    66,    -1,
      17,    66,    -1,    64,    -1,    34,    66,    -1,    67,    -1,
      30,    63,    -1,    35,    63,    -1,    63,    29,    63,    -1,
      63,    30,    63,    -1,    63,    31,    63,    -1,    63,    32,
      63,    -1,    63,    33,    63,    -1,    63,    23,    63,    -1,
      63,    25,    63,    -1,    63,    28,    63,    -1,    63,    24,
      63,    -1,    63,    27,    63,    -1,    63,    26,    63,    -1,
      63,    22,    63,    -1,    63,    21,    63,    -1,    54,    -1,
      43,    63,    44,    -1,    52,    65,    -1,    -1,    37,    63,
      38,    -1,    64,    -1,    68,    43,    69,    44,    -1,    12,
      -1,    13,    -1,    14,    -1,    15,    -1,    -1,    70,    -1,
      71,    -1,    70,    40,    71,    -1,    63,    -1,    72,    -1,
       7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    88,    88,    89,    90,    93,    94,    97,    99,   101,
     102,   105,   107,   109,   110,   113,   115,   121,   123,   124,
     138,   139,   142,   143,   150,   159,   164,   170,   171,   174,
     176,   177,   184,   190,   193,   196,   199,   202,   203,   208,
     209,   212,   215,   218,   221,   224,   227,   230,   233,   236,
     239,   242,   245,   248,   251,   254,   255,   258,   275,   276,
     279,   281,   288,   289,   290,   291,   294,   295,   298,   299,
     305,   306,   309
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "C220_KEY_IDENT", "C220_KEY_INT",
  "C220_KEY_MAIN", "C220_KEY_INT_TYPE", "C220_KEY_STRING", "C220_KEY_ELSE",
  "C220_KEY_FOR", "C220_KEY_IF", "C220_KEY_RETURN", "C220_KEY_PRINTF",
  "C220_KEY_RAND", "C220_KEY_SCANF", "C220_KEY_SRAND", "C220_KEY_INCR",
  "C220_KEY_DECR", "C220_KEY_UNARY_NEG", "C220_KEY_DEBUG_MARKER", "'='",
  "C220_KEY_OR", "C220_KEY_AND", "C220_KEY_NE", "C220_KEY_EQ", "'<'",
  "'>'", "C220_KEY_GE", "C220_KEY_LE", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'&'", "'!'", "C220_KEY_POST_ID", "'['", "']'", "';'", "','", "'{'",
  "'}'", "'('", "')'", "$accept", "program", "declarations", "one_decl",
  "type", "var_list", "variable", "ident", "array_sizes", "number", "main",
  "main_open", "statements", "stmt", "simple_stmt", "maybe_else",
  "compound_stmt", "maybe_expr", "expr", "var_ref", "array_index", "lval",
  "fn_call", "fn_name", "maybe_args", "arg_list", "str_or_expr", "string", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
      61,   275,   276,   277,   278,    60,    62,   279,   280,    43,
      45,    42,    47,    37,    38,    33,   281,    91,    93,    59,
      44,   123,   125,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    46,    46,    47,    47,    48,    49,    50,
      50,    51,    52,    53,    53,    54,    55,    56,    57,    57,
      58,    58,    59,    59,    59,    59,    59,    60,    60,    61,
      62,    62,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    65,    65,
      66,    67,    68,    68,    68,    68,    69,    69,    70,    70,
      71,    71,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     0,     2,     3,     1,     1,
       3,     2,     1,     0,     3,     1,     5,     4,     0,     2,
       1,     1,     2,     6,     9,     3,     4,     0,     2,     3,
       0,     1,     3,     2,     2,     2,     2,     1,     2,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     2,     0,     3,
       1,     4,     1,     1,     1,     1,     0,     1,     1,     3,
       1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     8,     3,     0,     4,     0,    12,     0,
       0,     9,    13,     5,     0,     7,     0,     0,    11,    18,
      17,    10,    15,     0,     6,     0,    30,    14,     0,     0,
       0,    62,    63,    64,    65,     0,     0,     0,     0,     0,
       0,    18,    16,     0,    58,    55,    19,    20,    21,     0,
      31,    37,     0,    39,     0,    30,     0,     0,    60,    35,
      36,     0,    40,    38,    41,    30,     0,     0,    57,    22,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,    34,     0,    66,     0,     0,    25,
       0,    29,    56,     0,    54,    53,    47,    50,    48,    52,
      51,    49,    42,    43,    44,    45,    46,    32,    72,    70,
       0,    67,    68,    71,     0,     0,    26,    59,    61,     0,
       0,    27,    69,    30,     0,    23,     0,    28,     0,    24
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,    19,     4,     5,    10,    11,    44,    18,    45,
       6,     7,    26,    46,    47,   125,    48,    49,    50,    51,
      68,    52,    53,    54,   110,   111,   112,   113
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -114
static const yytype_int16 yypact[] =
{
    -114,     6,  -114,  -114,  -114,    33,  -114,   -34,  -114,   -19,
     -35,  -114,    17,  -114,    -5,  -114,    59,    75,  -114,    77,
    -114,  -114,  -114,    48,  -114,    59,    61,  -114,    44,    45,
     153,  -114,  -114,  -114,  -114,    59,    59,    47,   153,    59,
     153,  -114,  -114,   153,    55,  -114,  -114,  -114,  -114,    54,
     280,     5,    41,  -114,    51,   153,   153,   224,  -114,  -114,
    -114,    75,  -114,  -114,  -114,    96,   176,   153,  -114,  -114,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,  -114,  -114,   153,   129,    58,   200,  -114,
      57,  -114,  -114,   262,   291,   291,     2,     2,   -13,   -13,
     -13,   -13,    35,    35,  -114,  -114,  -114,   280,  -114,   280,
      70,    76,  -114,  -114,   153,    78,  -114,  -114,  -114,   129,
     243,    90,  -114,   153,    78,  -114,    73,  -114,    78,  -114
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -114,  -114,  -114,    99,   101,  -114,   105,    -2,  -114,    -8,
    -114,  -114,    81,  -114,  -114,  -114,  -113,   -54,   -30,    24,
    -114,    46,  -114,  -114,  -114,  -114,     4,  -114
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -61
static const yytype_int16 yytable[] =
{
      57,    87,   121,    12,    15,    16,     2,    13,    62,    23,
      64,   127,     3,    66,    12,   129,    78,    79,    80,    81,
      82,   -60,   -60,    12,    14,   -60,    88,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     8,    93,     9,    20,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,    90,    17,   107,   109,    83,    84,    58,
      58,    85,     8,    58,     8,    22,    80,    81,    82,   126,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    22,
      37,    59,    60,     3,   120,    63,    27,    55,    56,   109,
      61,    38,    67,    69,    86,    39,    40,   114,   124,     8,
      22,   116,    41,    42,    43,    28,    29,    30,    31,    32,
      33,    34,    35,    36,   118,    37,   119,   128,    24,    41,
      25,    21,    65,   122,     0,     0,    38,     0,     0,     0,
      39,    40,     8,    22,     0,     0,   108,    41,    91,    43,
       0,    31,    32,    33,    34,    35,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,    22,     0,    38,
       0,     0,     0,    39,    40,    31,    32,    33,    34,    35,
      36,     0,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,     0,     0,     0,    39,    40,     0,
       0,     0,     0,     0,     0,     0,    43,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,     0,     0,
       0,     0,     0,    89,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     0,     0,     0,
       0,     0,   123,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
     117,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
      30,    55,   115,     5,    39,    40,     0,    41,    38,    17,
      40,   124,     6,    43,    16,   128,    29,    30,    31,    32,
      33,    16,    17,    25,    43,    20,    56,    25,    26,    27,
      28,    29,    30,    31,    32,    33,     3,    67,     5,    44,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    61,    37,    85,    86,    16,    17,    35,
      36,    20,     3,    39,     3,     4,    31,    32,    33,   123,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     4,
      19,    35,    36,     6,   114,    39,    38,    43,    43,   119,
      43,    30,    37,    39,    43,    34,    35,    39,     8,     3,
       4,    44,    41,    42,    43,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    44,    19,    40,    44,    19,    41,
      19,    16,    41,   119,    -1,    -1,    30,    -1,    -1,    -1,
      34,    35,     3,     4,    -1,    -1,     7,    41,    42,    43,
      -1,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    30,
      -1,    -1,    -1,    34,    35,    12,    13,    14,    15,    16,
      17,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    -1,    -1,
      -1,    -1,    -1,    39,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    -1,    -1,    -1,
      -1,    -1,    39,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    -1,    -1,    -1,    -1,
      38,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    46,     0,     6,    48,    49,    55,    56,     3,     5,
      50,    51,    52,    41,    43,    39,    40,    37,    53,    47,
      44,    51,     4,    54,    48,    49,    57,    38,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    19,    30,    34,
      35,    41,    42,    43,    52,    54,    58,    59,    61,    62,
      63,    64,    66,    67,    68,    43,    43,    63,    64,    66,
      66,    43,    63,    66,    63,    57,    63,    37,    65,    39,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    16,    17,    20,    43,    62,    63,    39,
      54,    42,    44,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,     7,    63,
      69,    70,    71,    72,    39,    44,    44,    38,    44,    40,
      63,    61,    71,    39,     8,    60,    62,    61,    44,    61
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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
        case 4:
#line 90 "ece220_parse.y"
    {ece220_main = (yyvsp[(2) - (2)]);;}
    break;

  case 11:
#line 105 "ece220_parse.y"
    { var_create ((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); (yyval) = NULL;;}
    break;

  case 12:
#line 107 "ece220_parse.y"
    {(yyval) = new_ast_str (ece220token.name);;}
    break;

  case 13:
#line 109 "ece220_parse.y"
    {(yyval) = new_ast_num (0);;}
    break;

  case 14:
#line 110 "ece220_parse.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 15:
#line 113 "ece220_parse.y"
    { (yyval) = new_ast_num (ece220token.ival); ;}
    break;

  case 16:
#line 115 "ece220_parse.y"
    {
		    reading_globals = 0;
		    (yyval) = (yyvsp[(4) - (5)]);
		;}
    break;

  case 17:
#line 121 "ece220_parse.y"
    {start_main ();;}
    break;

  case 18:
#line 123 "ece220_parse.y"
    {(yyval) = NULL;;}
    break;

  case 19:
#line 124 "ece220_parse.y"
    {
		    /* slow for long code, but simple... */
		    if (NULL == (yyvsp[(1) - (2)])) {
		        (yyval) = (yyvsp[(2) - (2)]);
		    } else {
			ast220_t* find;

			for (find = (yyvsp[(1) - (2)]); NULL != find->next; find = find->next);
			find->next = (yyvsp[(2) - (2)]);
			(yyval) = (yyvsp[(1) - (2)]);
		    }
		;}
    break;

  case 20:
#line 138 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 21:
#line 139 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 22:
#line 142 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (2)]);;}
    break;

  case 23:
#line 143 "ece220_parse.y"
    {
	            (yyval) = new_ast_node ();
		    (yyval)->type = AST220_IF_STMT;
		    (yyval)->test = (yyvsp[(3) - (6)]);
		    (yyval)->left = (yyvsp[(5) - (6)]);
		    (yyval)->right = (yyvsp[(6) - (6)]);
		;}
    break;

  case 24:
#line 151 "ece220_parse.y"
    { 
	            (yyval) = new_ast_node ();
		    (yyval)->type = AST220_FOR_STMT;
		    (yyval)->test = (yyvsp[(5) - (9)]);
		    (yyval)->left = (yyvsp[(3) - (9)]);
		    (yyval)->middle = (yyvsp[(9) - (9)]);
		    (yyval)->right = (yyvsp[(7) - (9)]);
		;}
    break;

  case 25:
#line 159 "ece220_parse.y"
    {
	            (yyval) = new_ast_node ();
		    (yyval)->type = AST220_RETURN_STMT;
		    (yyval)->left = (yyvsp[(2) - (3)]);
	        ;}
    break;

  case 26:
#line 164 "ece220_parse.y"
    {
	            (yyval) = (yyvsp[(3) - (4)]);
		    (yyval)->type = AST220_DEBUG_MARKER;
	        ;}
    break;

  case 27:
#line 170 "ece220_parse.y"
    {(yyval) = NULL;;}
    break;

  case 28:
#line 171 "ece220_parse.y"
    {(yyval) = (yyvsp[(2) - (2)]);;}
    break;

  case 29:
#line 174 "ece220_parse.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 30:
#line 176 "ece220_parse.y"
    {(yyval) = NULL;;}
    break;

  case 31:
#line 177 "ece220_parse.y"
    {
	      	    (yyval) = new_ast_node (); 
		    (yyval)->type = AST220_POP_STACK; 
		    (yyval)->left = (yyvsp[(1) - (1)]);
		;}
    break;

  case 32:
#line 184 "ece220_parse.y"
    {
	            (yyval) = new_ast_node ();
		    (yyval)->type = AST220_OP_ASSIGN;
		    (yyval)->left = (yyvsp[(1) - (3)]);
		    (yyval)->right = (yyvsp[(3) - (3)]);
		;}
    break;

  case 33:
#line 190 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_POST_INCR, (yyvsp[(1) - (2)]), NULL);
	        ;}
    break;

  case 34:
#line 193 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_POST_DECR, (yyvsp[(1) - (2)]), NULL);
	        ;}
    break;

  case 35:
#line 196 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_PRE_INCR, (yyvsp[(2) - (2)]), NULL);
	        ;}
    break;

  case 36:
#line 199 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_PRE_DECR, (yyvsp[(2) - (2)]), NULL);
	        ;}
    break;

  case 37:
#line 202 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 38:
#line 203 "ece220_parse.y"
    {
	            (yyval) = new_ast_node ();
		    (yyval)->type = AST220_GET_ADDRESS;
		    (yyval)->left = (yyvsp[(2) - (2)]);
		;}
    break;

  case 39:
#line 208 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 40:
#line 209 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_NEGATE, (yyvsp[(2) - (2)]), NULL);
	        ;}
    break;

  case 41:
#line 212 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_LOG_NOT, (yyvsp[(2) - (2)]), NULL);
	        ;}
    break;

  case 42:
#line 215 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_ADD, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 43:
#line 218 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_SUB, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 44:
#line 221 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_MULT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 45:
#line 224 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_DIV, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 46:
#line 227 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_MOD, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 47:
#line 230 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_CMP_NE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 48:
#line 233 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_CMP_LESS, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 49:
#line 236 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_CMP_LE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 50:
#line 239 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_CMP_EQ, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 51:
#line 242 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_CMP_GE, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 52:
#line 245 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_CMP_GREATER, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 53:
#line 248 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_LOG_AND, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 54:
#line 251 "ece220_parse.y"
    {
	            (yyval) = new_ast_op (AST220_OP_LOG_OR, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	        ;}
    break;

  case 55:
#line 254 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->type = AST220_PUSH_INT;;}
    break;

  case 56:
#line 255 "ece220_parse.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 57:
#line 258 "ece220_parse.y"
    {
		    symtab_entry_t* entry = symtab_lookup ((yyvsp[(1) - (2)])->name);

		    if (NULL == entry ||
			(0 == entry->array_len && NULL != (yyvsp[(2) - (2)])) ||
			(0 != entry->array_len && NULL == (yyvsp[(2) - (2)]))) {
			ece220errorf ("invalid variable access");
			/* should discard AST nodes here... */
			(yyval) = NULL;
		    } else {
			(yyval) = (yyvsp[(1) - (2)]); 
			(yyval)->type = AST220_VARIABLE;
			(yyval)->left = (yyvsp[(2) - (2)]);
		    }
		;}
    break;

  case 58:
#line 275 "ece220_parse.y"
    {(yyval) = NULL;;}
    break;

  case 59:
#line 276 "ece220_parse.y"
    {(yyval) = (yyvsp[(2) - (3)]);;}
    break;

  case 60:
#line 279 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 61:
#line 281 "ece220_parse.y"
    {
		    (yyval) = (yyvsp[(1) - (4)]); 
		    (yyval)->type = AST220_FUNC_CALL;
		    (yyval)->left = (yyvsp[(3) - (4)]);
		;}
    break;

  case 62:
#line 288 "ece220_parse.y"
    {(yyval) = new_ast_func (AST220_PRINTF);;}
    break;

  case 63:
#line 289 "ece220_parse.y"
    {(yyval) = new_ast_func (AST220_RAND);;}
    break;

  case 64:
#line 290 "ece220_parse.y"
    {(yyval) = new_ast_func (AST220_SCANF);;}
    break;

  case 65:
#line 291 "ece220_parse.y"
    {(yyval) = new_ast_func (AST220_SRAND);;}
    break;

  case 66:
#line 294 "ece220_parse.y"
    {(yyval) = NULL;;}
    break;

  case 67:
#line 295 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 68:
#line 298 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 69:
#line 299 "ece220_parse.y"
    {
	            (yyvsp[(3) - (3)])->next = (yyvsp[(1) - (3)]);
		    (yyval) = (yyvsp[(3) - (3)]);
		;}
    break;

  case 70:
#line 305 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]);;}
    break;

  case 71:
#line 306 "ece220_parse.y"
    {(yyval) = (yyvsp[(1) - (1)]); (yyval)->type = AST220_PUSH_STR;;}
    break;

  case 72:
#line 309 "ece220_parse.y"
    {(yyval) = new_ast_str (ece220token.name);;}
    break;


/* Line 1267 of yacc.c.  */
#line 1968 "ece220_parse.tab.c"
      default: break;
    }
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
		      yytoken, &yylval);
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

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
		 yytoken, &yylval);
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


#line 311 "ece220_parse.y"


ast220_t*
ece220_parse_program ()
{
    ece220_reset_lexer ();
    ece220_main = NULL;
    reading_globals = 1;
    global_offset = 0;
    local_offset = 0;
    has_main = 0;
    ece220parse ();
    return ece220_main;
}

static void
var_create (ast220_t* name, ast220_t* a_len)
{
    int32_t var_size;
    symtab_entry_t* entry;

    entry = symtab_create (name->name);
    if (NULL == entry) {
	ece220errorf ("can't create variable: %s", name->name);
    } else {
	entry->array_len = a_len->value;
	entry->is_global = reading_globals;
	var_size = (a_len->value == 0 ? 1 : a_len->value);
	if (reading_globals) {
	    entry->offset = global_offset;
	    global_offset += var_size;
	} else {
	    entry->offset = local_offset - (var_size - 1);
	    local_offset -= var_size;
	}
    }
    free (name->name);
    free (name);
    free (a_len);
}

static void 
start_main ()
{
    reading_globals = 0;
    if (has_main) {
        ece220errorf ("multiple main functions");
    } else {
        has_main = 1;
    }
}

static ast220_t* 
new_ast_node ()
{
    ast220_t* node;

    /* not good practice to terminate in the middle of the program... */
    if (NULL == (node = malloc (sizeof (ast220_t)))) {
        perror ("panic");
	exit (3);
    }
    return node;
}

static ast220_t* 
new_ast_num (int32_t value)
{
    ast220_t* node;

    node = new_ast_node ();
    node->value = value;
    return node;
}

static ast220_t* 
new_ast_str (char* str)
{
    ast220_t* node;

    node = new_ast_node ();
    node->name = str;
    return node;
}

static ast220_t* 
new_ast_func (ast220_builtin_func_t id)
{
    ast220_t* node;

    node = new_ast_node ();
    node->fnum = id;
    return node;
}

static ast220_t* 
new_ast_op (ast220_type_t type, ast220_t* left, ast220_t* right)
{
    ast220_t* node;

    node = new_ast_node ();
    node->type = type;
    node->left = left;
    node->right = right;
    return node;
}

int32_t
ece220_local_var_space ()
{
    return -local_offset;
}

int32_t
ece220_global_var_space ()
{
    return global_offset;
}


