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
	PARAM, /*si es parametro formal*/
	DESCRIPTOR
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

//estructura para almacenar las etiquetas en la tabla de simbolos
typedef struct
{
	char *labelIn;		  //nombre etiqueta de entrada
	char *labelOut;		  //nombre etiqueta de salida
	char *labelElse;	  //caso if: nombre de la etiqueta else
	char *controlVarName; //nombre variable de control bucles definidos
} instControlDescriptor;

typedef struct {
	entryType entry;
	char * name;
	dataType dt;
	dataType listType; //si es lista aqui ponemos el tipo de lista
	unsigned int nParam;
	unsigned int nDim;
	instControlDescriptor desc;
} TSentry; //entrada de la tabla de simbolos

typedef struct {
	int n; //atributo
	char *lex;
	bool isList;
	dataType type;
	dataType listType; //si es lista aqui ponemos el tipo de lista
	int dim;
} attr;

typedef struct cuart{

	bool start;
	bool varConst;
	//sentType st;
	TSentry a1;
	TSentry a2;
	TSentry op;
	TSentry result;

} cuart;

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

// Tabla de codigo intermedio
extern unsigned int tciSize;
extern cuart tci[MAX_TS]; //Tabla codigo intermedio

// Contador de numero de variables temporales
extern unsigned int tempCounter;

// Counter for the labels created
extern unsigned int labelsCounter;

// Archivo codigo intermedio
extern FILE *mainFile;

// Intermediate File for the functions defined on the code.
extern FILE *functionFile;

// Actual working file, this will in execution time when a function is defined
extern FILE *currentFile;

// Tabulation for intermediate code
extern unsigned int tabulationCount;

// Flag for track the locals variables for main
extern bool mainVarDeclared;

extern unsigned int nestingSubProgLevel;

extern unsigned int listValuesCounter;

// Enable debug mode
extern bool DEBUG;

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
bool isIDdeclaredProc(attr at);
bool checkPos(attr at1, attr at2);
/**************************/

void tsPushDescrip(TSentry e);
int tsSearchLastET(entryType et);
void initFilesAndHeaders();
void finalize();
void copyCuart(cuart *cNew, const cuart *cOriginal);
void tciAdd(cuart c);
unsigned int getTopTciIndex();
cuart *getFromTci(int index);
void tciClearUntilStart();
int searchToStart();
void startSplitExpressions();
void startSplitExpressionsWithName(const char *variableName);
void addExpresion(attr a1, attr op, attr a2, attr *result);
void addExpresionTernary(attr a1, attr a2, attr a3, attr *result);
void addExpresionUnary(attr op, attr a2, attr *result);
void addExpresionUnaryRight(attr op, attr a1, attr *result);
void addExpresionSingle(attr a1, attr *result);
void addExpresionConstList(attr a1, attr *result);
void endSplitExpressions();
char *genNextTempVarName();
char *genNextLabelName();
char *getStrtype(TSentry a);
char * getStrtypeAttr(attr a);
char * getStrtypeList(attr a);
void writeInFile(char *string);
void writeStartBrackets();
void writeEndBrackets();
void writeTabulations();
void writeIf();
void writeElse();
void writeEndIf();
void writeWhile();
void writeEndWhile();
void writeFor();
void writeEndFor();
void writeLocalsVars();
void writePrintVariable(attr a);
void writePrintString(attr a);
void writeEndPrint();
void writeScan(attr a);
void writeSubProgHeader();
int getStartIndex(int nStart);
void writeProcCall(attr a, int nParam);
char *concatenateValueSign(attr sign, attr value);
char *concatenateListStringSign(attr sign, attr value, attr string);
char *concatenateListString(attr value, attr string);
#endif
