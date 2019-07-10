/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/syntactic.y" /* yacc.c:339  */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "y.tab.h"
#include "errorCount.h"
#include "semantic.h"


void yyerror(const char *   msg);
int yylex();


#define YYERROR_VERBOSE



#line 85 "src/y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_SRC_Y_TAB_H_INCLUDED
# define YY_YY_SRC_Y_TAB_H_INCLUDED
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
    OP_OR_LOGICO = 258,
    OP_AND_LOGICO = 259,
    OP_OR_BIT = 260,
    OP_EXC_OR = 261,
    OP_IGUALDAD = 262,
    OP_RELACION = 263,
    SIGNO = 264,
    OP_MULTIPLICATIVO = 265,
    OP_UNARIO = 266,
    OP_CONCATENAR = 267,
    OP_MAS_MAS = 268,
    OP_MENOS_MENOS = 269,
    OP_ARR = 270,
    OP_ES = 271,
    OP_INICIO_LISTA = 272,
    OP_LONGITUD_LISTA = 273,
    OP_ELEMENTO_LISTA = 274,
    PRINCIPAL = 275,
    ASIGNACION = 276,
    PROCEDIMIENTO = 277,
    LISTA_DE = 278,
    INI_CORCHETE = 279,
    FIN_CORCHETE = 280,
    INI_LLAVES = 281,
    FIN_LLAVES = 282,
    MIENTRAS = 283,
    SI = 284,
    SINO = 285,
    HACER = 286,
    HASTA = 287,
    DESDE = 288,
    INI_VARIABLES = 289,
    FIN_VARIABLES = 290,
    LEER = 291,
    ESCRIBIR = 292,
    INI_PARENTESIS = 293,
    FIN_PARENTESIS = 294,
    COMA = 295,
    CONST_BOOLEANO = 296,
    CONST_CARACTER = 297,
    CONST_ENTERO = 298,
    CONST_REAL = 299,
    IDENTIFICADOR = 300,
    PUNTO_Y_COMA = 301,
    CADENA = 302,
    TIPO_BASICO = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 185 "src/y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   470

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    78,    78,    80,    80,    82,    83,    86,    87,    89,
      89,    92,    92,    94,    95,    96,    97,   100,   100,   100,
     102,   102,   104,   105,   104,   105,   107,   108,   109,   111,
     112,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   125,   127,   141,   142,   145,   147,   149,   151,   152,
     154,   155,   157,   160,   165,   165,   176,   177,   180,   181,
     182,   183,   194,   202,   210,   218,   226,   234,   242,   250,
     268,   286,   295,   301,   312,   313,   320,   321,   322,   324,
     324,   326,   328,   329,   330,   331,   334,   335,   338,   339,
     342,   343,   346,   347,   350,   351,   352,   353,   355,   355
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OP_OR_LOGICO", "OP_AND_LOGICO",
  "OP_OR_BIT", "OP_EXC_OR", "OP_IGUALDAD", "OP_RELACION", "SIGNO",
  "OP_MULTIPLICATIVO", "OP_UNARIO", "OP_CONCATENAR", "OP_MAS_MAS",
  "OP_MENOS_MENOS", "OP_ARR", "OP_ES", "OP_INICIO_LISTA",
  "OP_LONGITUD_LISTA", "OP_ELEMENTO_LISTA", "PRINCIPAL", "ASIGNACION",
  "PROCEDIMIENTO", "LISTA_DE", "INI_CORCHETE", "FIN_CORCHETE",
  "INI_LLAVES", "FIN_LLAVES", "MIENTRAS", "SI", "SINO", "HACER", "HASTA",
  "DESDE", "INI_VARIABLES", "FIN_VARIABLES", "LEER", "ESCRIBIR",
  "INI_PARENTESIS", "FIN_PARENTESIS", "COMA", "CONST_BOOLEANO",
  "CONST_CARACTER", "CONST_ENTERO", "CONST_REAL", "IDENTIFICADOR",
  "PUNTO_Y_COMA", "CADENA", "TIPO_BASICO", "$accept", "programa", "bloque",
  "$@1", "contenido_bloque", "declar_de_subprogs", "declar_subprog", "$@2",
  "cabecera_subprog", "$@3", "parametros", "declar_de_variables_locales",
  "$@4", "variables_locales", "cuerpo_declar_variables", "$@5", "$@6",
  "variables", "sentencias", "sentencia", "sentencia_comienzo",
  "sentencia_asignacion", "sentencia_if", "sentencia_while",
  "sentencia_entrada", "sentencia_salida", "expresion_cadena",
  "expresiones_salida", "sentencia_mover_lista", "sentencia_for",
  "llamada_proced", "$@7", "expresiones", "expresion", "tipo_dato",
  "lista_constantes", "valores_lista", "lista_constantes_reales",
  "lista_constantes_enteros", "lista_constantes_booleanos",
  "lista_constantes_caracteres", "constante", "signo", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -66

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-66)))

#define YYTABLE_NINF -27

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -3,    -2,    37,   -66,   -66,   -66,    -6,   -66,    13,   -66,
      12,   -66,   125,   -66,    -5,   -66,    11,   -66,   -66,   -66,
     250,   250,   250,   250,   250,     2,     0,    15,    19,    45,
       7,   239,   -66,   -66,   -66,   -66,     6,   -66,   -66,   -66,
     163,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   366,   -66,   -66,   -66,   -66,   -66,    45,   250,    82,
      90,    90,   394,   -66,   -66,   -66,   -66,    58,    61,    92,
     -66,   -66,   -66,   -66,   -21,   250,   250,    18,    74,   -66,
     -66,   -25,   380,   250,   106,   250,   250,   -66,    -2,   -66,
     250,   250,   250,   250,   250,   250,   250,   250,   250,   250,
      77,   -66,   -66,    66,    86,    87,   -66,    91,    95,   293,
     307,    45,    45,   -66,     7,   -66,   321,   -66,   114,    79,
     250,   -66,   407,   419,   430,   440,   449,   454,    20,    90,
      90,   352,   -66,    93,    -9,   -66,   -66,   128,   128,   107,
     201,   -66,   -66,   -66,   250,   -66,    41,   380,   250,   -66,
      28,    96,   -66,   103,   -66,   104,   201,   120,   335,   109,
     250,   114,    -9,   -66,    -9,   -66,   -66,   201,   201,   -66,
     380,   111,   112,   -66,   119,   -66,   -66,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     2,     1,    19,    17,     0,     8,
       0,     4,     0,    25,     0,    79,     0,    21,    22,    78,
       0,     0,     0,     0,     0,     0,    98,     0,     0,     0,
       0,     0,    97,    96,    95,    94,    75,    31,     7,     9,
       0,    30,    39,    32,    33,    34,    35,    36,    38,    40,
      37,     0,    77,    76,    80,    18,    20,     0,     0,    75,
      68,    61,    41,    58,    60,    11,    99,    90,    92,     0,
      82,    83,    84,    85,     0,     0,     0,     0,     0,    49,
      51,     0,    48,     0,     0,     0,     0,    54,     0,    29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      59,    23,    59,     0,     0,     0,    81,    88,    86,     0,
       0,     0,     0,    46,     0,    47,     0,    74,    73,     0,
       0,    10,    62,    63,    64,    65,    66,    67,    69,    70,
      71,     0,    52,     0,    16,    91,    93,    98,    98,     0,
       0,    28,    27,    50,     0,    42,     0,    57,     0,    24,
       0,     0,    89,     0,    87,     0,     0,    44,     0,     0,
       0,    72,     0,    12,     0,    15,    45,     0,     0,    55,
      56,     0,     0,    43,     0,    14,    13,    53
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -66,   -66,     5,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   143,   -66,   -66,   -50,   -66,   -35,
     -66,   -66,   -66,   -66,   -66,   -66,    46,   -66,   -66,   -66,
     -66,   -66,   -66,   -20,   -65,   -66,   -66,    27,    34,    69,
      70,   -66,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    37,     6,     8,    12,    38,    88,    39,   103,
     150,     9,    10,    16,    17,    57,   133,    78,    40,    41,
      42,    43,    44,    45,    46,    47,    80,    81,    48,    49,
      50,   120,   146,    51,    18,    52,    69,    70,    71,    72,
      73,    53,    74
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      60,    61,    62,    63,    64,    89,     4,   101,    19,    66,
      82,    84,    13,    13,    14,   114,    20,     1,    21,   111,
      85,   115,   107,   108,     3,    23,    24,    86,     7,   162,
      97,    26,    98,    99,    14,    14,   102,     5,    84,    15,
      11,    67,    68,    54,    87,    58,    55,    65,    32,    33,
      34,    35,    59,    75,    79,   109,   110,    76,   112,    15,
      15,   141,   142,   116,   -26,   118,   119,   163,   164,   151,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     159,   160,    90,    91,    92,    93,    94,    95,    96,    97,
      77,    98,    99,   121,    82,   102,    85,   171,   104,   172,
     147,   105,    98,    99,   134,   157,   102,   153,   155,    90,
      91,    92,    93,    94,    95,    96,    97,   106,    98,    99,
     113,   166,   102,   132,   158,   145,    19,    67,   161,    68,
     102,   137,   173,   174,    20,   138,    21,    66,   156,   149,
     170,   165,    22,    23,    24,   117,   107,    25,   108,    26,
     167,     3,    -6,    27,    28,   169,   175,   176,   177,    56,
     143,    29,    30,    31,    19,   154,    32,    33,    34,    35,
      36,   152,    20,   135,    21,   136,     0,     0,     0,     0,
      22,    23,    24,     0,     0,     0,     0,    26,     0,     3,
      -5,    27,    28,     0,     0,     0,     0,     0,     0,    29,
      30,    31,    19,     0,    32,    33,    34,    35,    36,     0,
      20,     0,    21,     0,     0,     0,     0,     0,    22,    23,
      24,     0,     0,     0,     0,    26,     0,     3,     0,    27,
      28,     0,     0,     0,     0,     0,     0,    29,    30,    31,
      19,     0,    32,    33,    34,    35,    36,     0,    20,     0,
      21,    19,     0,     0,     0,     0,     0,    23,    24,    20,
       0,    21,     0,    26,     0,     0,     0,     0,    23,    24,
       0,     0,    83,     0,    26,     0,     0,    58,     0,     0,
      32,    33,    34,    35,    59,     0,     0,     0,    58,     0,
       0,    32,    33,    34,    35,    59,    90,    91,    92,    93,
      94,    95,    96,    97,     0,    98,    99,     0,     0,   102,
      90,    91,    92,    93,    94,    95,    96,    97,     0,    98,
      99,     0,     0,   102,    90,    91,    92,    93,    94,    95,
      96,    97,   139,    98,    99,     0,     0,   102,    90,    91,
      92,    93,    94,    95,    96,    97,   140,    98,    99,     0,
       0,   102,     0,   144,     0,    90,    91,    92,    93,    94,
      95,    96,    97,     0,    98,    99,   168,   148,   102,    90,
      91,    92,    93,    94,    95,    96,    97,     0,    98,    99,
       0,     0,   100,    90,    91,    92,    93,    94,    95,    96,
      97,     0,    98,    99,     0,     0,   102,    90,    91,    92,
      93,    94,    95,     0,    97,     0,    98,    99,     0,     0,
     102,    91,    92,    93,    94,    95,    96,    97,     0,    98,
      99,     0,     0,   102,    92,    93,    94,    95,    96,    97,
       0,    98,    99,     0,     0,   102,    93,    94,    95,    96,
      97,     0,    98,    99,     0,     0,   102,    94,    95,    96,
      97,     0,    98,    99,     0,     0,   102,    95,    96,    97,
       0,    98,    99,    96,    97,   102,    98,    99,     0,     0,
     102
};

static const yytype_int16 yycheck[] =
{
      20,    21,    22,    23,    24,    40,     1,    57,     1,     9,
      30,    31,     1,     1,    23,    40,     9,    20,    11,     1,
      14,    46,    43,    44,    26,    18,    19,    21,    34,     1,
      10,    24,    12,    13,    23,    23,    16,     0,    58,    48,
      27,    41,    42,    48,    38,    38,    35,    45,    41,    42,
      43,    44,    45,    38,    47,    75,    76,    38,    40,    48,
      48,   111,   112,    83,    46,    85,    86,    39,    40,   134,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
      39,    40,     3,     4,     5,     6,     7,     8,     9,    10,
      45,    12,    13,    88,   114,    16,    14,   162,    40,   164,
     120,    40,    12,    13,    38,   140,    16,   137,   138,     3,
       4,     5,     6,     7,     8,     9,    10,    25,    12,    13,
      46,   156,    16,    46,   144,    46,     1,    41,   148,    42,
      16,    40,   167,   168,     9,    40,    11,     9,    31,    46,
     160,    45,    17,    18,    19,    39,    43,    22,    44,    24,
      30,    26,    27,    28,    29,    46,    45,    45,    39,    16,
     114,    36,    37,    38,     1,   138,    41,    42,    43,    44,
      45,   137,     9,   104,    11,   105,    -1,    -1,    -1,    -1,
      17,    18,    19,    -1,    -1,    -1,    -1,    24,    -1,    26,
      27,    28,    29,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,     1,    -1,    41,    42,    43,    44,    45,    -1,
       9,    -1,    11,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    -1,    -1,    -1,    -1,    24,    -1,    26,    -1,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
       1,    -1,    41,    42,    43,    44,    45,    -1,     9,    -1,
      11,     1,    -1,    -1,    -1,    -1,    -1,    18,    19,     9,
      -1,    11,    -1,    24,    -1,    -1,    -1,    -1,    18,    19,
      -1,    -1,    33,    -1,    24,    -1,    -1,    38,    -1,    -1,
      41,    42,    43,    44,    45,    -1,    -1,    -1,    38,    -1,
      -1,    41,    42,    43,    44,    45,     3,     4,     5,     6,
       7,     8,     9,    10,    -1,    12,    13,    -1,    -1,    16,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    -1,    -1,    16,     3,     4,     5,     6,     7,     8,
       9,    10,    39,    12,    13,    -1,    -1,    16,     3,     4,
       5,     6,     7,     8,     9,    10,    39,    12,    13,    -1,
      -1,    16,    -1,    32,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    -1,    12,    13,    31,    15,    16,     3,
       4,     5,     6,     7,     8,     9,    10,    -1,    12,    13,
      -1,    -1,    16,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    -1,    -1,    16,     3,     4,     5,
       6,     7,     8,    -1,    10,    -1,    12,    13,    -1,    -1,
      16,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    -1,    -1,    16,     5,     6,     7,     8,     9,    10,
      -1,    12,    13,    -1,    -1,    16,     6,     7,     8,     9,
      10,    -1,    12,    13,    -1,    -1,    16,     7,     8,     9,
      10,    -1,    12,    13,    -1,    -1,    16,     8,     9,    10,
      -1,    12,    13,     9,    10,    16,    12,    13,    -1,    -1,
      16
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    20,    50,    26,    51,     0,    52,    34,    53,    60,
      61,    27,    54,     1,    23,    48,    62,    63,    83,     1,
       9,    11,    17,    18,    19,    22,    24,    28,    29,    36,
      37,    38,    41,    42,    43,    44,    45,    51,    55,    57,
      67,    68,    69,    70,    71,    72,    73,    74,    77,    78,
      79,    82,    84,    90,    48,    35,    63,    64,    38,    45,
      82,    82,    82,    82,    82,    45,     9,    41,    42,    85,
      86,    87,    88,    89,    91,    38,    38,    45,    66,    47,
      75,    76,    82,    33,    82,    14,    21,    38,    56,    68,
       3,     4,     5,     6,     7,     8,     9,    10,    12,    13,
      16,    66,    16,    58,    40,    40,    25,    43,    44,    82,
      82,     1,    40,    46,    40,    46,    82,    39,    82,    82,
      80,    51,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    46,    65,    38,    88,    89,    40,    40,    39,
      39,    66,    66,    75,    32,    46,    81,    82,    15,    46,
      59,    83,    87,    91,    86,    91,    31,    68,    82,    39,
      40,    82,     1,    39,    40,    45,    68,    30,    31,    46,
      82,    83,    83,    68,    68,    45,    45,    39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    52,    51,    53,    53,    54,    54,    56,
      55,    58,    57,    59,    59,    59,    59,    61,    60,    60,
      62,    62,    64,    65,    63,    63,    66,    66,    66,    67,
      67,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    70,    71,    71,    72,    73,    74,    75,    75,
      76,    76,    77,    78,    80,    79,    81,    81,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      83,    84,    85,    85,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    90,    90,    91,    91
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     4,     3,     2,     2,     0,     0,
       3,     0,     6,     4,     4,     2,     0,     0,     4,     0,
       2,     1,     0,     0,     5,     1,     1,     3,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     4,     7,     5,     6,     3,     3,     1,     1,
       3,     1,     3,     8,     0,     6,     3,     1,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     5,     3,     3,     1,     1,     1,     1,     1,
       2,     3,     1,     1,     1,     1,     2,     4,     2,     4,
       1,     3,     1,     3,     1,     1,     1,     1,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 80 "src/syntactic.y" /* yacc.c:1646  */
    {tsPushMark();}
#line 1459 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 80 "src/syntactic.y" /* yacc.c:1646  */
    {tsPopMark();}
#line 1465 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 89 "src/syntactic.y" /* yacc.c:1646  */
    {subProg=1;}
#line 1471 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 89 "src/syntactic.y" /* yacc.c:1646  */
    {subProg=0; cleanNamesParam();}
#line 1477 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 92 "src/syntactic.y" /* yacc.c:1646  */
    {tsPushProc((yyvsp[0]));}
#line 1483 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 94 "src/syntactic.y" /* yacc.c:1646  */
    {tsPushParam((yyvsp[0]));}
#line 1489 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 96 "src/syntactic.y" /* yacc.c:1646  */
    {tsPushParam((yyvsp[0]));}
#line 1495 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 100 "src/syntactic.y" /* yacc.c:1646  */
    { decVar = 1; }
#line 1501 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 100 "src/syntactic.y" /* yacc.c:1646  */
    { decVar = 0; }
#line 1507 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 104 "src/syntactic.y" /* yacc.c:1646  */
    {TMPtype=(yyvsp[0]).type; if(TMPtype==LIST)TMPlistType=(yyvsp[0]).listType;}
#line 1513 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 105 "src/syntactic.y" /* yacc.c:1646  */
    {TMPtype=NONE; TMPlistType=NONE;}
#line 1519 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 107 "src/syntactic.y" /* yacc.c:1646  */
    {if(decVar==1){tsPushVar((yyvsp[0]));}}
#line 1525 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 108 "src/syntactic.y" /* yacc.c:1646  */
    {if(decVar==1){tsPushVar((yyvsp[-2]));}}
#line 1531 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 125 "src/syntactic.y" /* yacc.c:1646  */
    {isList((yyvsp[0]));}
#line 1537 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 127 "src/syntactic.y" /* yacc.c:1646  */
    {
		(yyvsp[-3]).type = getType((yyvsp[-3]));
		if((yyvsp[-3]).type == LIST){
			(yyvsp[-3]).listType = getTypeList((yyvsp[-3]));
		}

		checkAssign((yyvsp[-3]),(yyvsp[-1]));
		(yyval).type = getType((yyvsp[-3]));
		if(getType((yyvsp[-3])) == LIST){
			(yyval).listType = getTypeList((yyvsp[-3]));
		}
}
#line 1554 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 141 "src/syntactic.y" /* yacc.c:1646  */
    {checkCondition((yyvsp[-4]));}
#line 1560 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 142 "src/syntactic.y" /* yacc.c:1646  */
    {checkCondition((yyvsp[-2]));}
#line 1566 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 145 "src/syntactic.y" /* yacc.c:1646  */
    {checkCondition((yyvsp[-3]));}
#line 1572 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 151 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = getType((yyvsp[0]));}
#line 1578 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 152 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = CHAR;}
#line 1584 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 157 "src/syntactic.y" /* yacc.c:1646  */
    {isList((yyvsp[-2]));}
#line 1590 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 160 "src/syntactic.y" /* yacc.c:1646  */
    {
    checkCondition((yyvsp[-3]));
  }
#line 1598 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 165 "src/syntactic.y" /* yacc.c:1646  */
    {
    nParam = 0;
		isProcDeclared((yyvsp[-1]));
		currentFunction = tsSearchEntry((yyvsp[-1]),PROC);
	}
#line 1608 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 170 "src/syntactic.y" /* yacc.c:1646  */
    {
    checkNumParam();
    nParam = 0;
		currentFunction = -1;
	}
#line 1618 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 176 "src/syntactic.y" /* yacc.c:1646  */
    {nParam++; checkParam((yyvsp[0]), nParam);}
#line 1624 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 177 "src/syntactic.y" /* yacc.c:1646  */
    {nParam++; checkParam((yyvsp[0]), nParam);}
#line 1630 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 180 "src/syntactic.y" /* yacc.c:1646  */
    {checkDataType((yyvsp[0]),LIST);}
#line 1636 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 181 "src/syntactic.y" /* yacc.c:1646  */
    {checkDataType((yyvsp[-1]),LIST);}
#line 1642 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 182 "src/syntactic.y" /* yacc.c:1646  */
    {checkDataType((yyvsp[0]),LIST);}
#line 1648 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 183 "src/syntactic.y" /* yacc.c:1646  */
    {
				if(checkUnitaryOp((yyvsp[-1]),(yyvsp[0]))){
					(yyval).type = (yyvsp[0]).type;
					if((yyvsp[0]).type == LIST){
						(yyval).listType = (yyvsp[0]).listType;
					}
				}
				else{
					(yyval).type = ERROR;
				}
		}
#line 1664 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 194 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkLogicOrAnd((yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = BOOL;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1677 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 202 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkLogicOrAnd((yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = BOOL;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1690 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 210 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkOrBit((yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = (yyvsp[-2]).type;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1703 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 218 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkExOr((yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = BOOL;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1716 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 226 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkRelation((yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = BOOL;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1729 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 234 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkRelation((yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = BOOL;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1742 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 242 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkSign((yyvsp[0]))){
				(yyval).type = (yyvsp[0]).type;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1755 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 250 "src/syntactic.y" /* yacc.c:1646  */
    {
				if(checkBinOp((yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]))){
					if((yyvsp[-2]).type == LIST){
						(yyval).type = LIST;
						(yyval).listType = (yyvsp[-2]).listType;
					}
					else if((yyvsp[0]).type == LIST){
						(yyval).type = LIST;
						(yyval).listType = (yyvsp[0]).listType;
					}
					else{
						(yyval).type = (yyvsp[-2]).type;
					}
				}
				else{
					(yyval).type = ERROR;
				}
		}
#line 1778 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 268 "src/syntactic.y" /* yacc.c:1646  */
    {
				if(checkMultOp((yyvsp[-2]),(yyvsp[-1]),(yyvsp[0]))){
					if((yyvsp[-2]).type == LIST){
						(yyval).type = LIST;
						(yyval).listType = (yyvsp[-2]).listType;
					}
					else if((yyvsp[0]).type == LIST){
						(yyval).type = LIST;
						(yyval).listType = (yyvsp[0]).listType;
					}
					else{
						(yyval).type = (yyvsp[-2]).type;
					}
				}
				else{
					(yyval).type = ERROR;
				}
		}
#line 1801 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 286 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkConcOp((yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = LIST;
				(yyval).listType = (yyvsp[-2]).listType;
			}
			else{
				(yyval).type = ERROR;
			}
		}
#line 1815 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 295 "src/syntactic.y" /* yacc.c:1646  */
    {
			if(checkTernOp((yyvsp[-4]),(yyvsp[-2]),(yyvsp[0]))){
				(yyval).type = LIST;
				(yyval).listType = (yyvsp[-4]).listType;
			}
		}
#line 1826 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 302 "src/syntactic.y" /* yacc.c:1646  */
    {
			(yyvsp[-2]).type = getType((yyvsp[-2]));
			if((yyvsp[-2]).type == LIST){
				(yyvsp[-2]).listType = getTypeList((yyvsp[-2]));
			}
			if(checkMinMin((yyvsp[-2]), (yyvsp[0]))){
				(yyval).type = LIST;
				(yyval).listType = getTypeList((yyvsp[-2]));
			}
		}
#line 1841 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 312 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval) = (yyvsp[-1]);}
#line 1847 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 313 "src/syntactic.y" /* yacc.c:1646  */
    {
				strcpy((yyval).lex,(yyvsp[0]).lex);
				(yyval).type = getType((yyvsp[0]));
				if((yyval).type == LIST){
					(yyval).listType = getTypeList((yyvsp[0]));
				}
		}
#line 1859 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 320 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = (yyvsp[0]).type;}
#line 1865 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 321 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = getType((yyvsp[0])); (yyval).listType=getTypeList((yyvsp[0]));}
#line 1871 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 324 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = (yyvsp[0]).type;}
#line 1877 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 324 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = (yyvsp[-1]).type; (yyval).listType = (yyvsp[0]).type;}
#line 1883 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 326 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = LIST; (yyval).listType = (yyvsp[-1]).listType;}
#line 1889 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 328 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = LIST; (yyval).listType = REAL;}
#line 1895 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 329 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = LIST; (yyval).listType = INT;}
#line 1901 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 330 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = LIST; (yyval).listType = BOOL;}
#line 1907 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 331 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = LIST; (yyval).listType = CHAR;}
#line 1913 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 350 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = REAL;}
#line 1919 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 351 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = INT;}
#line 1925 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 352 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = CHAR;}
#line 1931 "src/y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 353 "src/syntactic.y" /* yacc.c:1646  */
    {(yyval).type = BOOL;}
#line 1937 "src/y.tab.c" /* yacc.c:1646  */
    break;


#line 1941 "src/y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 357 "src/syntactic.y" /* yacc.c:1906  */


#include "lex.yy.c"

void yyerror(const char *msg ){
	fprintf(stderr, "\033[1;31mError sintáctico línea %d: %s\033[0m\n\n", yylineno, msg) ;
	fflush(stdout);
	syntacticErrorCount++;
}
