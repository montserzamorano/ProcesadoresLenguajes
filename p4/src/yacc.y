%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "y.tab.h"
#include "errorCount.h"
#include "semantic.h"


void yyerror(const char *   msg);
int yylex();


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

programa: PRINCIPAL bloque ;

bloque: INI_LLAVES {tsPushMark();}
		contenido_bloque
		FIN_LLAVES {tsPopMark();};

contenido_bloque: declar_de_variables_locales declar_de_subprogs sentencias
				| declar_de_variables_locales declar_de_subprogs ;


declar_de_subprogs: declar_de_subprogs declar_subprog 
					| ;

declar_subprog: cabecera_subprog {subProg=1;} bloque {subProg=0;};

cabecera_subprog: 
	PROCEDIMIENTO IDENTIFICADOR {tsPush($2,FUNCTION); decParam = 1;}
	INI_PARENTESIS parametros FIN_PARENTESIS {
		tsUpdateNParamFunction();
		nParam = 0;
		decParam = 0;
	};

parametros: parametros COMA tipo_dato variable {
				nParam++; tsPush($4, PARAM);
			}
			| parametros error tipo_dato variable {
				nParam++; tsPush($4, PARAM);
			}
           	| tipo_dato variable {
				nParam++; actualDataType = $1.dt;  tsPush($2, PARAM);
			}
			| ;

declar_de_variables_locales: 
	INI_VARIABLES { decVar = 1; } variables_locales FIN_VARIABLES { decVar = 0; }
	|;

variables_locales: variables_locales cuerpo_declar_variables
				| cuerpo_declar_variables ;

cuerpo_declar_variables: tipo_dato variables PUNTO_Y_COMA
						| error ;

variables: variable
			| variable COMA variables
			| variable error variables ;

variable: IDENTIFICADOR {
		if (decVar == 1) tsPush($1,VAR);
		else if (decParam == 0)  tsGetIdent($1,&$$);
	};

sentencias: sentencias {decVar = 2; } sentencia
          	| {decVar = 2; } sentencia;

sentencia: bloque
          	| sentencia_asignacion
          	| sentencia_if
          	| sentencia_while
          	| sentencia_entrada
          	| sentencia_salida
          	| llamada_proced
			| sentencia_mover_lista
			| sentencia_comienzo;
			| sentencia_for;

sentencia_comienzo: OP_INICIO_LISTA expresion;

sentencia_asignacion: variable ASIGNACION expresion PUNTO_Y_COMA {
	if($1.dt != $3.dt){
		printf("\n\033[1;33mError línea %d: semantic error, Los tipos no son iguales.\033[0m\n",line);
	}
};

sentencia_if:
	SI INI_PARENTESIS expresion FIN_PARENTESIS sentencia SINO sentencia {
		checkDataType($3, BOOL);
	}
	| 
	SI INI_PARENTESIS expresion FIN_PARENTESIS sentencia {
		checkDataType($3, BOOL);
	};

sentencia_while: 
	MIENTRAS INI_PARENTESIS expresion FIN_PARENTESIS HACER sentencia {
		checkDataType($3, BOOL);
	};

sentencia_entrada: LEER variables PUNTO_Y_COMA ;

sentencia_salida: ESCRIBIR expresiones_salida PUNTO_Y_COMA ;

expresion_cadena: expresion
                	| CADENA ;

expresiones_salida: expresiones_salida COMA expresion_cadena
                   	| expresion_cadena ;

sentencia_mover_lista: 
	expresion OP_ES PUNTO_Y_COMA{
		checkIsList($1);
	};

sentencia_for: 
	INI_PARENTESIS DESDE expresion HASTA expresion HACER sentencia FIN_PARENTESIS {
		checkDataType($5, BOOL);
	};

llamada_proced:
	variable INI_PARENTESIS {nParam=0;} expresiones FIN_PARENTESIS PUNTO_Y_COMA {
		tsFunctionCall($1, &$$);
		nParam = 0;
	};

expresiones: expresiones COMA expresion {nParam++; checkParam($3); }
            	| expresion  {nParam++; checkParam($1);};

expresion:
		  OP_LONGITUD_LISTA expresion {checkIsList($2);}
		| OP_ELEMENTO_LISTA expresion {checkIsList($2);}
		| OP_UNARIO expresion { opUnary($2, &$$);}
		| expresion OP_OR_LOGICO expresion {opOrAnd($1, $3, &$$);}
		| expresion OP_AND_LOGICO expresion {opOrAnd($1, $3, &$$);}
		| expresion OP_OR_BIT expresion {opOrBinary($1, $3, &$$);}
		| expresion OP_EXC_OR expresion {opOrBinary($1, $3, &$$);}
		| expresion OP_IGUALDAD expresion {opEqual($1, $3, &$$);}
		| expresion OP_RELACION expresion {opRelation($1, $3, &$$);}
		| SIGNO expresion %prec OP_UNARIO {opSign($2, &$$);}
		| expresion SIGNO expresion {opSignAndProduct($1, $3, &$$);}
		| expresion OP_MULTIPLICATIVO expresion {opSignAndProduct($1, $3, &$$);}
		| expresion OP_CONCATENAR expresion {opMerge($1, $3, &$$);}
		| expresion OP_MAS_MAS expresion OP_ARR expresion {opAddValueList($1, $3, $5, &$$);}
		| variable OP_MENOS_MENOS {opIncrement($1, &$$);}
		| INI_PARENTESIS expresion FIN_PARENTESIS { $$.dt = $2.dt; $$.isList = $2.isList;}
		| variable {decVar = 0; $$.dt = $1.dt; $$.isList = $1.isList;}
		| constante {$$.dt = $1.dt; $$.isList = false;}
		| lista_constantes {$$.dt = $1.dt; $$.isList = true;}
		| error ;

tipo_dato: TIPO_BASICO {setType($1); setIsList(false);} | tipo_lista ;

tipo_lista: LISTA_DE TIPO_BASICO {setIsList(true); setType($2); } ;

lista_constantes: INI_CORCHETE valores_lista FIN_CORCHETE {$$.isList = true, $$.dt = $2.dt;};

valores_lista: lista_constantes_reales {$$.dt = REAL;}
                | lista_constantes_enteros {$$.dt = INT;}
                | lista_constantes_booleanos {$$.dt = BOOL;}
                | lista_constantes_caracteres {$$.dt = CHAR;};

lista_constantes_reales:
	signo CONST_REAL
	| signo CONST_REAL COMA lista_constantes_reales;

lista_constantes_enteros:
	signo CONST_ENTERO
	| signo CONST_ENTERO COMA lista_constantes_enteros;

lista_constantes_booleanos:
	CONST_BOOLEANO
	| CONST_BOOLEANO COMA lista_constantes_booleanos;

lista_constantes_caracteres:
	CONST_CARACTER
	| CONST_CARACTER COMA lista_constantes_caracteres;

constante:
	CONST_REAL {$$.dt = REAL;}
	| CONST_ENTERO {$$.dt = INT;}
	| CONST_CARACTER {$$.dt = CHAR;}
	| CONST_BOOLEANO {$$.dt = BOOL;};

signo: | SIGNO ;

%% 

#include "lex.yy.c"

void yyerror(const char *msg ){
	fprintf(stderr, "\033[1;31mError línea %d: %s\033[0m\n\n", yylineno, msg) ;
	fflush(stdout);
	errorCount++;
}
