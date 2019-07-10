/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
