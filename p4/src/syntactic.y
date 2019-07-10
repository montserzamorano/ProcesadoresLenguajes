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

programa: PRINCIPAL bloque;

bloque: INI_LLAVES {tsPushMark();} contenido_bloque FIN_LLAVES {tsPopMark();};

contenido_bloque: declar_de_variables_locales declar_de_subprogs sentencias
				| declar_de_variables_locales declar_de_subprogs ;


declar_de_subprogs: declar_de_subprogs declar_subprog
					| ;

declar_subprog: cabecera_subprog {subProg=1;} bloque {subProg=0; cleanNamesParam();};

cabecera_subprog:
	PROCEDIMIENTO IDENTIFICADOR {tsPushProc($2);} INI_PARENTESIS parametros FIN_PARENTESIS ;

parametros: parametros COMA tipo_dato IDENTIFICADOR {tsPushParam($4);}
			| parametros error tipo_dato IDENTIFICADOR
      | tipo_dato IDENTIFICADOR {tsPushParam($2);}
			| ;

declar_de_variables_locales:
	INI_VARIABLES { decVar = 1; } variables_locales FIN_VARIABLES { decVar = 0; } |;

variables_locales: variables_locales cuerpo_declar_variables | cuerpo_declar_variables ;

cuerpo_declar_variables: tipo_dato {TMPtype=$1.type; if(TMPtype==LIST)TMPlistType=$1.listType;}
													variables {TMPtype=NONE; TMPlistType=NONE;} PUNTO_Y_COMA | error ;

variables: IDENTIFICADOR {if(decVar==1){tsPushVar($1);}}
			| IDENTIFICADOR COMA variables {if(decVar==1){tsPushVar($1);}}
			| IDENTIFICADOR error variables ;

sentencias: sentencias sentencia
          	| sentencia;

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

sentencia_comienzo: OP_INICIO_LISTA expresion {isList($2);};

sentencia_asignacion: IDENTIFICADOR ASIGNACION expresion PUNTO_Y_COMA {
		$1.type = getType($1);
		if($1.type == LIST){
			$1.listType = getTypeList($1);
		}

		checkAssign($1,$3);
		$$.type = getType($1);
		if(getType($1) == LIST){
			$$.listType = getTypeList($1);
		}
};

sentencia_if:
	SI INI_PARENTESIS expresion FIN_PARENTESIS sentencia SINO sentencia {checkCondition($3);}
	| SI INI_PARENTESIS expresion FIN_PARENTESIS sentencia {checkCondition($3);};

sentencia_while:
	MIENTRAS INI_PARENTESIS expresion FIN_PARENTESIS HACER sentencia {checkCondition($3);};

sentencia_entrada: LEER variables PUNTO_Y_COMA ;

sentencia_salida: ESCRIBIR expresiones_salida PUNTO_Y_COMA ;

expresion_cadena: expresion {$$.type = getType($1);}
                	| CADENA {$$.type = CHAR;};

expresiones_salida: expresiones_salida COMA expresion_cadena
                   	| expresion_cadena ;

sentencia_mover_lista: expresion OP_ES PUNTO_Y_COMA {isList($1);};

sentencia_for:
	INI_PARENTESIS DESDE expresion HASTA expresion HACER sentencia FIN_PARENTESIS {
    checkCondition($5);
  };

llamada_proced:
	IDENTIFICADOR INI_PARENTESIS {
    nParam = 0;
		isProcDeclared($1);
		currentFunction = tsSearchEntry($1,PROC);
	}
  expresiones FIN_PARENTESIS PUNTO_Y_COMA {
    checkNumParam();
    nParam = 0;
		currentFunction = -1;
	};

expresiones: expresiones COMA expresion {nParam++; checkParam($3, nParam);}
            	| expresion {nParam++; checkParam($1, nParam);};

expresion:
		  OP_LONGITUD_LISTA expresion {checkDataType($2,LIST);}
		| expresion OP_ES {checkDataType($1,LIST);}
		| OP_ELEMENTO_LISTA expresion {checkDataType($2,LIST);}
		| OP_UNARIO expresion {
				if(checkUnitaryOp($1,$2)){
					$$.type = $2.type;
					if($2.type == LIST){
						$$.listType = $2.listType;
					}
				}
				else{
					$$.type = ERROR;
				}
		}
		| expresion OP_OR_LOGICO expresion {
			if(checkLogicOrAnd($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
		}
		| expresion OP_AND_LOGICO expresion {
			if(checkLogicOrAnd($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
		}
		| expresion OP_OR_BIT expresion {
			if(checkOrBit($1,$3)){
				$$.type = $1.type;
			}
			else{
				$$.type = ERROR;
			}
		}
		| expresion OP_EXC_OR expresion {
			if(checkExOr($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
		}
		| expresion OP_IGUALDAD expresion {
			if(checkRelation($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
		}
		| expresion OP_RELACION expresion {
			if(checkRelation($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
		}
		| SIGNO expresion %prec OP_UNARIO {
			if(checkSign($2)){
				$$.type = $2.type;
			}
			else{
				$$.type = ERROR;
			}
		}
		| expresion SIGNO expresion {
				if(checkBinOp($1,$2,$3)){
					if($1.type == LIST){
						$$.type = LIST;
						$$.listType = $1.listType;
					}
					else if($3.type == LIST){
						$$.type = LIST;
						$$.listType = $3.listType;
					}
					else{
						$$.type = $1.type;
					}
				}
				else{
					$$.type = ERROR;
				}
		}
		| expresion OP_MULTIPLICATIVO expresion {
				if(checkMultOp($1,$2,$3)){
					if($1.type == LIST){
						$$.type = LIST;
						$$.listType = $1.listType;
					}
					else if($3.type == LIST){
						$$.type = LIST;
						$$.listType = $3.listType;
					}
					else{
						$$.type = $1.type;
					}
				}
				else{
					$$.type = ERROR;
				}
		}
		| expresion OP_CONCATENAR expresion{
			if(checkConcOp($1,$3)){
				$$.type = LIST;
				$$.listType = $1.listType;
			}
			else{
				$$.type = ERROR;
			}
		}
		| expresion OP_MAS_MAS expresion OP_ARR expresion {
			if(checkTernOp($1,$3,$5)){
				$$.type = LIST;
				$$.listType = $1.listType;
			}
		}
		| IDENTIFICADOR OP_MENOS_MENOS expresion
		{
			$1.type = getType($1);
			if($1.type == LIST){
				$1.listType = getTypeList($1);
			}
			if(checkMinMin($1, $3)){
				$$.type = LIST;
				$$.listType = getTypeList($1);
			}
		}
		| INI_PARENTESIS expresion FIN_PARENTESIS {$$ = $2;}
		| IDENTIFICADOR {
				strcpy($$.lex,$1.lex);
				$$.type = getType($1);
				if($$.type == LIST){
					$$.listType = getTypeList($1);
				}
		}
		| constante {$$.type = $1.type;}
		| lista_constantes {$$.type = getType($1); $$.listType=getTypeList($1);}
		| error ;

tipo_dato: TIPO_BASICO {$$.type = $1.type;}| LISTA_DE TIPO_BASICO {$$.type = $1.type; $$.listType = $2.type;};

lista_constantes: INI_CORCHETE valores_lista FIN_CORCHETE {$$.type = LIST; $$.listType = $2.listType;};

valores_lista: lista_constantes_reales {$$.type = LIST; $$.listType = REAL;}
                | lista_constantes_enteros {$$.type = LIST; $$.listType = INT;}
                | lista_constantes_booleanos {$$.type = LIST; $$.listType = BOOL;}
                | lista_constantes_caracteres {$$.type = LIST; $$.listType = CHAR;} ;

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
	CONST_REAL {$$.type = REAL;}
	| CONST_ENTERO {$$.type = INT;}
	| CONST_CARACTER {$$.type = CHAR;}
	| CONST_BOOLEANO {$$.type = BOOL;};

signo: | SIGNO ;

%%

#include "lex.yy.c"

void yyerror(const char *msg ){
	fprintf(stderr, "\033[1;31mError sintáctico línea %d: %s\033[0m\n\n", yylineno, msg) ;
	fflush(stdout);
	syntacticErrorCount++;
}
