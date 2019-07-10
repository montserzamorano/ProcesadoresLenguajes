#ifndef __SEMANTIC_H__
#define __SEMANTIC_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int bool;
#define true 1
#define false 0

typedef enum {
	MARK = 0, /*marca comienzo bloque*/
	PROC , /*si es procedimiento*/
	VAR, /*si es variable*/
	PARAM /*si es parametro formal*/
}entryType;

typedef enum {
	NOT_ASIG = 0,
	ERROR,
	BOOL,
	INT,
	REAL,
	CHAR,
	LIST,
	NONE /*desconocido*/
}dataType;

typedef struct {
	entryType entry;
	char * name;
	dataType dt;
	dataType listType; //si es lista aqui ponemos el tipo de lista
	unsigned int nParam;
	unsigned int nDim;
} TSentry; //entrada de la tabla de simbolos

typedef struct {
	int n; //atributo
	char *lex;
	bool isList;
	dataType type;
	dataType listType; //si es lista aqui ponemos el tipo de lista
	int dim;
} attr;

/**************************/
// Tabla de simbolos
#define YYSTYPE attr /* cada simbolo tiene una estructura de tipo atributo*/
#define MAX_TS 1000
int tsSize;
TSentry ts[MAX_TS];
//extern attr ts[MAX_TS]

// Tipo de dato actual
extern dataType actualDataType;
extern bool actualTypeIsList;

// Indica si se ha entrado en la produccion de un subprograma
extern bool subProg;

// Indica la posicion de la TS donde esta almacenada la info de la ultima funcion declarada
extern int currentFunction ;

// Indica el numero de parametros declarados en la funcion actual.
extern unsigned int nParam ;

// Indica el uso de las variables.
extern unsigned int decVar;
extern unsigned int decParam;
extern dataType TMPtype;
extern dataType TMPlistType;
// Linea actual.
extern unsigned int line;

/**************************/


/*Lista de funciones y procedimientos para el manejo de la TS*/
void printPila(); //para depurar codigo
char * writeType(dataType d);
int getTsTop();
bool isIDdeclared(attr at);
bool isProcDeclared(attr at);
void checkLimit();
void tsPushMark();
void tsPop();
void tsPopMark();
void tsPushVar(attr at);
void tsPushProc(attr at);
void tsPushParam(attr at);
dataType getType(attr at);
dataType getTypeList(attr at);
bool checkDataType(attr a, dataType t);
bool checkCondition(attr a);
bool checkListType(attr a, dataType lt);
bool isList(attr a);
int tsSearchEntry(attr at, entryType et);
bool checkConcOp(attr at1, attr at2);
void checkParam(attr at, int pos);
void checkNumParam();
bool checkMinMin(attr at1, attr at2);
bool checkAssign(attr res, attr exp);
bool checkUnitaryOp(attr op, attr at);
bool checkLogicOrAnd(attr at1, attr at2);
bool compatibleRealInt(attr at1, attr at2);
bool compatibleRealIntList(attr at1, attr at2);
bool checkSign(attr at);
bool checkRelation(attr at1, attr at2);
bool checkExOr(attr at1, attr at2);
bool checkOrBit(attr at1, attr at2);
bool checkMultOp(attr at1, attr op, attr at2);
bool checkBinOp(attr at1, attr op, attr at2);
bool checkTernOp(attr at1, attr at2, attr at3);
void cleanNamesParam();

/**************************/


#endif
