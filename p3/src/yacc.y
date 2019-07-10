%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "errorCount.h"


void yyerror(char * msg);


#define YYERROR_VERBOSE


%}

%error-verbose

%left OP_OR_LOGICO
%left OP_AND_LOGICO
%left OP_OR_BIT
%left OP_EXC_OR
%left OP_IGUALDAD
%left OP_RELACION
%left SIGNO
%left OP_MULTIPLICATIVO

%right OP_UNARIO
%right OP_CONCATENAR
%right OP_MAS_MAS
%right OP_MENOS_MENOS
%right OP_ARR
%right OP_ES

%left OP_INICIO_LISTA
%left OP_LONGITUD_LISTA
%left OP_ELEMENTO_LISTA

%token PRINCIPAL
%token ASIGNACION
%token PROCEDIMIENTO
%token LISTA_DE
%token INI_CORCHETE
%token FIN_CORCHETE
%token INI_LLAVES
%token FIN_LLAVES
%token MIENTRAS
%token SI
%token SINO
%token HACER
%token HASTA
%token DESDE
%token INI_VARIABLES
%token FIN_VARIABLES
%token LEER
%token ESCRIBIR
%token INI_PARENTESIS
%token FIN_PARENTESIS
%token COMA
%token CONST_BOOLEANO
%token CONST_CARACTER
%token CONST_ENTERO
%token CONST_REAL
%token IDENTIFICADOR
%token PUNTO_Y_COMA
%token CADENA
%token OP_ES
%token SIGNO
%token TIPO_BASICO



%%

programa: PRINCIPAL bloque;

bloque: 	INI_LLAVES
			declar_de_variables_locales
			declar_de_subprogs
			sentencias
			FIN_LLAVES
		|
			INI_LLAVES
			declar_de_variables_locales
			declar_de_subprogs
			FIN_LLAVES ;

declar_de_subprogs: declar_de_subprogs declar_subprog
					| ;

declar_subprog: cabecera_subprog bloque;

declar_de_variables_locales: INI_VARIABLES variables_locales FIN_VARIABLES
							|;

variables_locales: variables_locales cuerpo_declar_variables
				| cuerpo_declar_variables ;

cuerpo_declar_variables: tipo_dato variables PUNTO_Y_COMA
						| error ;

variables: variable
			| variable COMA variables
			| variable error variables ;

variable: IDENTIFICADOR ;

cabecera_subprog: PROCEDIMIENTO variable INI_PARENTESIS FIN_PARENTESIS
			 | PROCEDIMIENTO variable INI_PARENTESIS parametros FIN_PARENTESIS;

parametros: parametros COMA parametro
			| parametros error parametro
           	| parametro ;

parametro: tipo_dato variable ;

sentencias: sentencias sentencia
          		|  sentencia;

sentencia: bloque
          	| sentencia_asignacion
          	| sentencia_if
          	| sentencia_while
          	| sentencia_entrada
          	| sentencia_salida
          	| llamada_proced
						| sentencia_mover_lista
						| sentencia_iniciar_lista
          	| sentencia_for
			| error;

sentencia_asignacion: variable ASIGNACION expresion PUNTO_Y_COMA 
			| variable ASIGNACION expresion error ;

sentencia_iniciar_lista : OP_INICIO_LISTA expresion PUNTO_Y_COMA ;

sentencia_if: SI INI_PARENTESIS expresion FIN_PARENTESIS sentencia SINO sentencia
        | SI INI_PARENTESIS expresion FIN_PARENTESIS sentencia;

sentencia_while: MIENTRAS INI_PARENTESIS expresion FIN_PARENTESIS HACER sentencia ;

sentencia_entrada: LEER variables PUNTO_Y_COMA ;

sentencia_salida: ESCRIBIR expresiones_salida PUNTO_Y_COMA ;

expresion_cadena: expresion
                	| CADENA ;

expresiones_salida: expresiones_salida COMA expresion_cadena
                   	| expresion_cadena ;

sentencia_mover_lista: expresion OP_ES PUNTO_Y_COMA;

sentencia_for: INI_PARENTESIS
				DESDE expresion
				HASTA expresion
				HACER
					sentencia
			FIN_PARENTESIS ;

llamada_proced: variable INI_PARENTESIS expresiones FIN_PARENTESIS PUNTO_Y_COMA ;

expresiones: expresiones COMA expresion
            	| expresion ;

expresion: OP_LONGITUD_LISTA expresion
		| OP_ELEMENTO_LISTA expresion
		| OP_UNARIO expresion
		| expresion OP_OR_LOGICO expresion
		| expresion OP_AND_LOGICO expresion
		| expresion OP_OR_BIT expresion
		| expresion OP_EXC_OR expresion
		| expresion OP_IGUALDAD expresion
		| expresion OP_RELACION expresion
		| SIGNO expresion %prec OP_UNARIO
		| expresion SIGNO expresion
		| expresion OP_MULTIPLICATIVO expresion
		| expresion OP_CONCATENAR expresion
		| expresion OP_MAS_MAS expresion OP_ARR expresion
		| expresion OP_MAS_MAS
		| expresion OP_MENOS_MENOS
		| expresion OP_ES
		| INI_PARENTESIS expresion FIN_PARENTESIS
		| variable
		| constante
		| lista_constantes;

tipo_dato: TIPO_BASICO | tipo_lista ;

tipo_lista: LISTA_DE TIPO_BASICO ;

lista_constantes: INI_CORCHETE valores_lista FIN_CORCHETE;

valores_lista: lista_constantes_reales
                | lista_constantes_enteros
                | lista_constantes_booleanos
                | lista_constantes_caracteres ;

lista_constantes_reales: constante_real
          			     | constante_real COMA lista_constantes_reales;

lista_constantes_enteros: constante_entero
										     | constante_entero COMA lista_constantes_enteros;

lista_constantes_booleanos: CONST_BOOLEANO
                			| CONST_BOOLEANO COMA lista_constantes_booleanos ;

lista_constantes_caracteres: CONST_CARACTER
                			| CONST_CARACTER COMA lista_constantes_caracteres ;

constante:  CONST_REAL
                | CONST_ENTERO
                | CONST_CARACTER
                | CONST_BOOLEANO ;

constante_real : CONST_REAL
								| SIGNO CONST_REAL ;

constante_entero : CONST_ENTERO
								| SIGNO CONST_ENTERO ;



%%

#include "lex.yy.c"

void yyerror( char *msg ){
	fprintf(stderr, "\n\033[1;31mError línea %d: %s\033[0m\n\n", yylineno, msg) ;
	fflush(stdout);
	errorCount++;

}