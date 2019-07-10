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

programa: PRINCIPAL {
		initFilesAndHeaders();
	}
	bloque {
		finalize();
	};

bloque: INI_LLAVES {
			tsPushMark();
			writeStartBrackets();
		}
		contenido_bloque
		FIN_LLAVES {
			tsPopMark();
			writeEndBrackets();
		};

contenido_bloque: declar_de_variables_locales {writeLocalsVars();} declar_de_subprogs contenido_bloque2;

contenido_bloque2: sentencias | ;

declar_de_subprogs: declar_de_subprogs declar_subprog
					| ;

declar_subprog: cabecera_subprog {subProg=1;} bloque {subProg=0; cleanNamesParam();};

cabecera_subprog:
	PROCEDIMIENTO IDENTIFICADOR {
		tsPushProc($2);
	} INI_PARENTESIS parametros FIN_PARENTESIS {
		writeSubProgHeader();
	};

parametros:
	parametros COMA tipo_dato IDENTIFICADOR {
		$2.type = $1.type;
		$2.listType = $1.listType;
		tsPushParam($4);
	}
	| parametros error tipo_dato IDENTIFICADOR
	| tipo_dato IDENTIFICADOR {
		$2.type = $1.type;
		$2.listType = $1.listType;
		tsPushParam($2);
	}
	| ;

declar_de_variables_locales:
	INI_VARIABLES { decVar = 1; } variables_locales FIN_VARIABLES { decVar = 0; } |;

variables_locales: variables_locales cuerpo_declar_variables | cuerpo_declar_variables ;

cuerpo_declar_variables:
	tipo_dato {TMPtype=$1.type; if(TMPtype==LIST)TMPlistType=$1.listType;}
	variables {TMPtype=NONE;TMPlistType=NONE;}
	PUNTO_Y_COMA
	| error ;

variables: IDENTIFICADOR {if(decVar==1){tsPushVar($1);}}
			| IDENTIFICADOR COMA variables {if(decVar==1){tsPushVar($1);}}
			| IDENTIFICADOR error variables;

sentencias: sentencias sentencia
          	| sentencia;

sentencia: bloque
			|  sentencia2
          	| sentencia_asignacion PUNTO_Y_COMA
          	| sentencia_entrada
          	| sentencia_salida
			| sentencia_for;

sentencia2: sentencia_if
          	| sentencia_while
			| sentencia_mover_lista
			| sentencia_comienzo;
          	| llamada_proced

sentencia_comienzo: OP_INICIO_LISTA expresion {isList($2); endSplitExpressions();};

sentencia_asignacion:
	IDENTIFICADOR {$1.type = getType($1);if($1.type == LIST){$1.listType = getTypeList($1);}}
	ASIGNACION {startSplitExpressionsWithName($1.lex);}
	expresion {
		checkAssign($1,$5);
		$$.type = $1.type;
		if($$.type == LIST){
			$$.listType = $1.listType;
		}
		endSplitExpressions();
	}
	| error;

sentencia_if:
	SI INI_PARENTESIS expresion FIN_PARENTESIS {
	 checkCondition($3);
		endSplitExpressions();
		writeIf();
	}
	sentencia 
	sentencia_else {
		writeEndIf();
	};

sentencia_else:
	SINO {
		writeElse();
	}
	sentencia
	| ;

sentencia_while:
	MIENTRAS INI_PARENTESIS expresion
	{
		//endSplitExpressions(); Esta funcion esta dentro de writeWhile
		writeWhile();
	}
	FIN_PARENTESIS HACER sentencia {
		checkCondition($3);
		writeEndWhile();
	};

sentencia_for:
	HACER INI_PARENTESIS DESDE sentencia_asignacion {
		startSplitExpressions();
	}
	HASTA expresion {
		checkCondition($7);
		//endSplitExpressions(); Esta funcion esta dentro de writeFor
		writeFor();
	}
	FIN_PARENTESIS sentencia {
		writeEndFor();
	};

sentencia_entrada: LEER IDENTIFICADOR PUNTO_Y_COMA {writeScan($2);};

sentencia_salida: ESCRIBIR expresiones_salida PUNTO_Y_COMA {/*writeEndPrint()*/};

expresiones_salida: expresiones_salida COMA expresion_cadena
                   	| expresion_cadena {$$.lex = $1.lex;};

expresion_cadena: {startSplitExpressions();} expresion {$$.type = $1.type; writePrintVariable($1);}
                	| CADENA {$$.type = CHAR; writePrintString($1);};

sentencia_mover_lista:
	expresion OP_ES {
		isList($1);
		addExpresionUnaryRight($2, $1, &$$);
		endSplitExpressions();
	}
	PUNTO_Y_COMA;

llamada_proced:
	IDENTIFICADOR INI_PARENTESIS {
    nParam = 0;
		isProcDeclared($1);
		currentFunction = tsSearchEntry($1,PROC);
	}
  expresiones FIN_PARENTESIS PUNTO_Y_COMA {
	checkNumParam();
    writeProcCall($1,nParam);
    nParam = 0;
		currentFunction = -1;
	};

expresiones: expresiones COMA expresion {nParam++; checkParam($3, nParam); endSplitExpressions();}
            	| expresion {nParam++; checkParam($1, nParam); endSplitExpressions();};

expresion:
		  OP_LONGITUD_LISTA expresion {if(isList($2)){$$.type=INT;}; addExpresionUnary($1, $2, &$$);}
		| expresion OP_ES {if(isList($1)){$$.type=LIST;$$.listType=$1.listType;}; addExpresionUnaryRight($2,$1, &$$);}
		| OP_ELEMENTO_LISTA expresion {if(isList($2)){$$.type=INT;}; addExpresionUnary($1, $2, &$$);}
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
				addExpresionUnary($1, $2, &$$);
		}
		| IDENTIFICADOR OP_ARR expresion {
			$1.type = getType($1);
			if($1.type == LIST){
				$1.listType = getTypeList($1);
			}
			if(checkPos($1,$3)){
				$$.type=$1.listType;
			} else {
				$$.type=ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		} %prec OP_MAS_MAS
		| expresion OP_OR_LOGICO expresion {
			if(checkLogicOrAnd($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		}
		| expresion OP_AND_LOGICO expresion {
			if(checkLogicOrAnd($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		}
		| expresion OP_OR_BIT expresion {
			if(checkOrBit($1,$3)){
				$$.type = $1.type;
			}
			else{
				$$.type = ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		}
		| expresion OP_EXC_OR expresion {
			if(checkExOr($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		}
		| expresion OP_IGUALDAD expresion {
			if(checkRelation($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		}
		| expresion OP_RELACION expresion {
			if(checkRelation($1,$3)){
				$$.type = BOOL;
			}
			else{
				$$.type = ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		}
		| SIGNO expresion %prec OP_UNARIO {
			if(checkSign($2)){
				$$.type = $2.type;
			}
			else{
				$$.type = ERROR;
			}
			addExpresionUnary($1, $2, &$$);
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
			addExpresion($1, $2, $3, &$$);
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
			addExpresion($1, $2, $3, &$$);
		}
		| expresion OP_CONCATENAR expresion{
			if(checkConcOp($1,$3)){
				$$.type = LIST;
				$$.listType = $1.listType;
			}
			else{
				$$.type = ERROR;
			}
			addExpresion($1, $2, $3, &$$);
		}
		| expresion OP_MAS_MAS expresion OP_ARR expresion {
			if(checkTernOp($1,$3,$5)){
				$$.type = LIST;
				$$.listType = $1.listType;
			}
			else{
				$$.type = ERROR;
			}
			addExpresionTernary($1, $3, $5, &$$);
		}
		| expresion OP_MENOS_MENOS expresion
		{
			if(checkMinMin($1, $3)){
				$$.type = LIST;
				$$.listType = getTypeList($1);
			}
			else{
				$$.type=ERROR;
			}
			addExpresionUnaryRight($2,$1, &$$);
		}
		| INI_PARENTESIS expresion FIN_PARENTESIS {$$.type = $2.type; $$.listType = $2.listType; $$.lex = $2.lex;}
		| IDENTIFICADOR {
			strcpy($$.lex,$1.lex);
			$$.type = getType($1);
			if($$.type == LIST){
				$$.listType = getTypeList($1);
			}
			addExpresionSingle($1, &$$);
		} %prec OP_ARR
		| constante {$$.type = $1.type;  $$.listType=$1.listType ;$$.lex = $1.lex; addExpresionSingle($1, &$$);}
		| lista_constantes {
			$$.type = $1.type;
			$$.listType = $1.listType;
			$$.lex = $1.lex;
			addExpresionConstList($1, &$$);
		}
		| error ;

tipo_dato:
	TIPO_BASICO {$$.type = $1.type;}
	|
	LISTA_DE TIPO_BASICO {$$.type = $1.type; $$.listType = $2.type;};

lista_constantes:
	INI_CORCHETE valores_lista FIN_CORCHETE {$$.lex = $2.lex; $$.type = LIST; $$.listType = $2.listType;};

valores_lista: lista_constantes_reales {$$.type = LIST; $$.listType = REAL; $$.lex = $1.lex;}
                | lista_constantes_enteros {$$.type = LIST; $$.listType = INT; $$.lex = $1.lex;}
                | lista_constantes_booleanos {$$.type = LIST; $$.listType = BOOL; $$.lex = $1.lex;}
                | lista_constantes_caracteres {$$.type = LIST; $$.listType = CHAR; $$.lex = $1.lex;};

lista_constantes_reales:
	signo CONST_REAL {$$.lex = concatenateValueSign($1, $2); listValuesCounter++;}
	| signo CONST_REAL COMA lista_constantes_reales {$$.lex = concatenateListStringSign($1, $2, $3); listValuesCounter++;};

lista_constantes_enteros:
	signo CONST_ENTERO {$$.lex = concatenateValueSign($1, $2); listValuesCounter++;}
	| signo CONST_ENTERO COMA lista_constantes_enteros  {$$.lex = concatenateListStringSign($1, $2, $4); listValuesCounter++;};

lista_constantes_booleanos:
	CONST_BOOLEANO {$$.lex = $1.lex; listValuesCounter++;}
	| CONST_BOOLEANO COMA lista_constantes_booleanos {concatenateListString($1, $3); listValuesCounter++;};

lista_constantes_caracteres:
	CONST_CARACTER  {$$.lex = $1.lex; listValuesCounter++;}
	| CONST_CARACTER COMA lista_constantes_caracteres {concatenateListString($1, $3); listValuesCounter++;};

constante:
	CONST_REAL {$$.type = REAL;}
	| CONST_ENTERO {$$.type = INT;}
	| CONST_CARACTER {$$.type = CHAR;}
	| CONST_BOOLEANO {$$.type = BOOL;};

signo: { $$.lex = strdup("");} | SIGNO {$$.lex = $1.lex;};

%%

#include "lex.yy.c"

void yyerror(const char *msg ){
	fprintf(stderr, "\033[1;31mError sintáctico línea %d: %s\033[0m\n\n", yylineno, msg) ;
	fflush(stdout);
	syntacticErrorCount++;
}
