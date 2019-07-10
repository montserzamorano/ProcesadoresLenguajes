#include "semantic.h"
#include "errorCount.h"

bool subProg = 0;
int currentFunction = -1;
unsigned int nParam = 0;
unsigned int decVar = 0;
unsigned int decParam = 0;
unsigned int line = 1;
dataType TMPtype = NONE;
dataType TMPlistType = NONE;

/**********************************/

unsigned int tciSize = 0;
cuart tci[MAX_TS]; //Tabla codigo intermedio
unsigned int tempCounter = 0;
unsigned int labelsCounter = 0;

FILE *mainFile = NULL;
FILE *functionFile = NULL;
FILE *currentFile = NULL;

unsigned int tabulationCount = 0;
bool mainVarDeclared = false;
unsigned int nestingSubProgLevel = 0;
unsigned int listValuesCounter = 0;

bool DEBUG = false;

/**********************************/


void printPila(){
  for(int i=getTsTop(); i>=0; i--){
    printf("\n\033[1;34mNombre:%s Tipo:%s. Tipo lista:%s\033[0m\n", ts[i].name, writeType(ts[i].dt),writeType(ts[i].listType) );
  }
}

char * writeType(dataType d){
  char * type;
  if(d==REAL){
    type = "real";
  }
  else if(d==BOOL){
    type = "booleano";
  }
  else if(d==CHAR){
    type = "caracter";
  }
  else if(d==LIST){
    type = "lista";
  }
  else if(d==INT){
    type = "entero";
  }
  else if(d==NONE){
    type = "ninguno";
  }
  else if(d==ERROR){
    type = "no definido";
  }
  else{
    type = "no asignado";
  }
  return type;
}

/*Lista de funciones y procedimientos para el manejo de la TS*/

int getTsTop(){
  if(tsSize-1 < 0){
    fflush(stdout);
  }
  return tsSize-1;
}
//comprueba si una variable ha sido declarada
bool isIDdeclared(attr at){
  int ind = getTsTop();
  while(ind >= 0){
    if(strcmp(ts[ind].name, at.lex) == 0){
      return true;
    }
    ind--;
  }
  return false;
}

bool isIDdeclaredProc(attr at){
  int ind = getTsTop();
  while(ind >= 0 && ts[ind].entry!=PROC){
    if(strcmp(ts[ind].name, at.lex) == 0){
      return true;
    }
    ind--;
  }
  return false;
}

void cleanNamesParam(){
  int ind = getTsTop();
  while(ts[ind].entry!=PROC){
    ts[ind].name = "";
    ind--;
  }
}

//comprueba si un procedimiento ha sido inizializada
bool isProcDeclared(attr at){
  int ind = getTsTop();
  while(ind >= 0){
    if(ts[ind].entry == PROC && strcmp(ts[ind].name, at.lex) == 0){
      return true;
    }
    ind--;
  }
  printf("\n\033[1;31mError semántico línea %d: el procedimiento %s no ha sido declarado. \033[0m\n", line, at.lex);
  semanticErrorCount++;

  return false;
}
void checkLimit(){
  //check if the limit of the stack has been reach
  if(tsSize >= MAX_TS){
    printf("\nError: Tabla de símbolos llena\n");
    return;
  }
  if(tsSize < 0){fflush(stdout);}
}

//insertar entrada de tipo marca
void tsPushMark(){
  checkLimit();
  ts[tsSize].entry = MARK;
  ts[tsSize].name = "}";
  ts[tsSize].dt = NONE;
  ts[tsSize].nParam = 0;
  tsSize++;
}

void tsPop(){
  tsSize--;
}
//limpia las entradas de la ts que corresponden a un mismo bloque
void tsPopMark(){
  while (ts[getTsTop()].entry != MARK && getTsTop() >= 0) tsPop();
  if (tsSize != 0) tsPop(); //esta ultima quita la marca
}

void tsPushVar(attr at){
  if(subProg==1){
    if(isIDdeclaredProc(at)){
      printf("\n\033[1;31mError semántico línea %d: el ID %s ya está en uso. \033[0m\n", line, at.lex);
      semanticErrorCount++;
      return;
    }
  }
  else if(isIDdeclared(at)){
    printf("\n\033[1;31mError semántico línea %d: el ID %s ya está en uso. \033[0m\n", line, at.lex);
    semanticErrorCount++;
    return;
  }
  checkLimit();
  ts[tsSize].entry = VAR;
  ts[tsSize].name = at.lex;
  ts[tsSize].dt = TMPtype;
  if(ts[tsSize].dt == LIST){ //si es lista asignamos tipo
    ts[tsSize].listType = TMPlistType;
  }
  ts[tsSize].nParam = 0;
  tsSize++;
}

void tsPushProc(attr at){
  checkLimit();
  ts[tsSize].entry = PROC;
  ts[tsSize].name = at.lex;
  ts[tsSize].dt = NONE; //nunca devuelve nada es todo void
  ts[tsSize].nParam = 0; //inicializamos a 0 y si vamos encontrando parametros los sumamos
  tsSize++;

  currentFunction = getTsTop();
}

void tsPushParamError(attr at){
  tsSize++;
  int ind = getTsTop();

  ts[ind].entry = PARAM;
  ts[ind].name = "error";
  ts[ind].dt = at.type;
  if(ts[ind].dt == LIST){ //si es lista asignamos tipo
    ts[ind].listType = at.listType;
  }
  ts[ind].nParam = 0;
  //añadimos el parametro a la ultima funcion añadida en la ts
  while(ts[ind].entry != PROC && ind >=0){
    ind--; //vamos buscando el procedimiento
  }
  ts[ind].nParam = ts[ind].nParam + 1;
}

void tsPushParam(attr at){
  checkLimit();
  tsSize++;
  int ind = getTsTop();

  ts[ind].entry = PARAM;
  ts[ind].name = at.lex;
  ts[ind].dt = at.type;
  if(ts[ind].dt == LIST){ //si es lista asignamos tipo
    ts[ind].listType = at.listType;
  }
  ts[ind].nParam = 0;
  //añadimos el parametro a la ultima funcion añadida en la ts
  while(ts[ind].entry != PROC && ind >=0){
    ind--; //vamos buscando el procedimiento
  }
  ts[ind].nParam = ts[ind].nParam + 1;
}

//devuelve el tipo de dato de un atributo

dataType getType(attr at){
  int ind = tsSize;
  if(isIDdeclared(at)){
    for(int ind = getTsTop(); ind >= 0; ind--){
      if(strcmp(ts[ind].name,at.lex)==0){
        return ts[ind].dt;
      }
    }
  }
  else{
    printf("\n\033[1;31mError semántico línea %d: el identificador %s no ha sido declarado. \033[0m\n", line, at.lex);
    semanticErrorCount++;
  }
  return ERROR;
}

dataType getTypeList(attr at){
  if(isIDdeclared(at)){
    for(int ind = getTsTop(); ind >= 0; ind--){
      if(strcmp(ts[ind].name,at.lex)==0){
        return ts[ind].listType;
      }
    }
  }
  else{
    printf("\n\033[1;31mError semántico línea %d: el identificador %s no ha sido declarado. \033[0m\n", line, at.lex);
    semanticErrorCount++;
  }
  return ERROR;
}

bool checkDataType(attr a, dataType t){
  /*if(isIDdeclared(a)||isIDdeclaredProc(a)){
    if(getType(a)==t){
      return true;
    }
  }*/
  if(a.type == t){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: la expresión es de tipo %s. Se esperaba tipo %s. \033[0m\n", line, writeType(a.type), writeType(t));
  semanticErrorCount++;

  return false;
}

bool checkCondition(attr a){
  /*if(a.type == BOOL){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: condición no válida. La expresión no es de tipo booleano. \033[0m\n", line);
  semanticErrorCount++;

  return false;*/
  return checkDataType(a,BOOL);
}

bool checkListType(attr a, dataType lt){
  /*if(isIDdeclared(a)||isIDdeclaredProc(a)){
    if(getTypeList(a)==lt){
      return true;
    }
  }*/
  if(a.listType==lt && a.type==LIST){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: la expresión es de tipo lista de %s. Se esperaba tipo lista de %s. \033[0m\n", line, writeType(a.listType), writeType(lt));
  semanticErrorCount++;
  return false;
}

bool isList(attr a){
  /*if(a.type==LIST){return true;}
  printf("\n\033[1;31mError semántico línea %d: la expresión es de tipo %s. Se esperaba lista. \033[0m\n", line, writeType(a.type));
  semanticErrorCount++;
  return false;*/
  return checkDataType(a,LIST);
}

int tsSearchEntry(attr at, entryType et) {
    int ind;
    for(int ind = getTsTop(); ind >= 0; ind--){
        if (ts[ind].entry == et && strcmp(at.lex, ts[ind].name) == 0)
            return ind;
    }
    return -1;
}

void checkParam(attr at, int pos){
  int ind = currentFunction+pos;
  //si existe, comprobamos el tipo. Si la posicion esta fuera del rango lo ignoramos
  if(pos <= ts[currentFunction].nParam){//lo de none???
    if(ts[ind].dt != at.type){
      printf("\n\033[1;31mError semántico línea %d: %s es de tipo %s. Se esperaba %s.\033[0m\n", line, at.lex, writeType(at.type), writeType(ts[ind].dt));
      semanticErrorCount++;
    }
    //si es de tipo lista, comprobamos la compatibilidad de tipos
    else if(ts[ind].dt == at.type && at.type == LIST){
      if(ts[ind].listType != at.listType){
        printf("\n\033[1;31mError semántico línea %d: la lista %s es de tipo %s. Se esperaba lista de tipo %s.\033[0m\n", line, at.lex, writeType(at.listType), writeType(ts[ind].listType));
        semanticErrorCount++;
      }
    }
  }
}
//esta se llama solo en el ultimo parametro
void checkNumParam(){
  if(nParam > ts[currentFunction].nParam){
    printf("\n\033[1;31mError semántico línea %d: se han proporcionado %d argumentos al procedimiento %s. Se esperaban %d. \033[0m\n",
    line, nParam,ts[currentFunction].name,ts[currentFunction].nParam);
    semanticErrorCount++;
  }
}

//COMPROBADOS MENSAJES DE ERROR
bool checkAssign(attr res, attr exp){
  if(isIDdeclared(res)){ //&& isIDdeclared(exp)){//si el resultado ha sido declarado
    if(res.type != exp.type){
        printf("\n\033[1;31mError semántico línea %d: incompatibilidad de tipos en la asignación. El valor es de tipo %s. Se esperaba %s.\033[0m\n", line, writeType(exp.type), writeType(res.type));
        semanticErrorCount++;
        return false;
    }
    else if(res.type==LIST && res.listType!=exp.listType){
        printf("\n\033[1;31mError semántico línea %d: incompatibilidad de tipos en la asignación. El valor es de tipo lista de %s. Se esperaba lista de %s.\033[0m\n", line, writeType(exp.listType), writeType(res.type));
        semanticErrorCount++;
        return false;
    }
  }
  return true;
}
//COMPROBADO
bool checkUnitaryOp(attr op, attr at){
  switch(op.n){
    case 0: //&
      if(!isIDdeclared(at) && !isProcDeclared(at)){//si es variable al ser una referencia
        printf("\n\033[1;31mError semántico línea %d: la variable %s no existe.\033[0m\n", line, at.lex);
        semanticErrorCount++;
        return false;
      }
      break;
    case 1: //!
      if(at.type!=BOOL){
        printf("\n\033[1;31mError semántico línea %d: incompatibilidad de tipos. Se esperaba valor lógico.\033[0m\n", line);
        semanticErrorCount++;
        return false;
      }
      break;
    default:
      break;
  }
  return true;
}
//COMPROBADO
// || y &&
bool checkLogicOrAnd(attr at1, attr at2){
  if(at1.type != BOOL || at2.type != BOOL){
    printf("\n\033[1;31mError semántico línea %d: ambos tipos deben ser lógicos.\033[0m\n", line);
    semanticErrorCount++;
    return false;
  }
  return true;
}
//COMPROBADO
bool checkSign(attr at){
  if(at.type == INT || at.type == REAL){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: tipo %s no es numérico.\033[0m\n", line, at.lex);
  semanticErrorCount++;
  return false;
}
//COMPROBADO
bool checkRelation(attr at1, attr at2){
  if(at1.type!=at2.type){
    printf("\n\033[1;31mError semántico línea %d: tipo %s no comparable con %s.\033[0m\n", line, writeType(at1.type), writeType(at2.type));
    semanticErrorCount++;
    return false;
  }
  else if(at1.type!=REAL && at1.type!=INT){
    printf("\n\033[1;31mError semántico línea %d: operador no compatible con tipo %s.\033[0m\n", line, writeType(at1.type));
    semanticErrorCount++;
    return false;
  }
  return true;
}
//COMPROBADO
bool checkExOr(attr at1, attr at2){
  if(at2.type==BOOL && at1.type==BOOL){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: ambos operandos tienen que ser de tipo lógico.\033[0m\n", line);
  semanticErrorCount++;
  return false;
}
//COMPROBADO
bool checkOrBit(attr at1, attr at2){
  if(at2.type == INT){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: es necesario un entero en la segunda posición.\033[0m\n", line);
  semanticErrorCount++;
  return false;
}
//COMPROBADO
bool checkConcOp(attr at1, attr at2){
  bool ok = true;
  if(at1.type!=LIST){
    ok = false;
    printf("\n\033[1;31mError semántico línea %d: %s tiene que ser de tipo lista.\033[0m\n", line, at1.lex);
    semanticErrorCount++;
  }
  if(at2.type!=LIST){
    ok = false;
    printf("\n\033[1;31mError semántico línea %d: %s tiene que ser de tipo lista.\033[0m\n", line, at2.lex);
    semanticErrorCount++;
  }
  if(at1.type==LIST && at2.type==LIST && at1.listType!=at2.listType){
      ok = false;
      printf("\n\033[1;31mError semántico línea %d: la lista de tipo %s no es concatenable con la lista de tipo %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.listType));
      semanticErrorCount++;
  }
  return ok;
}
//COMPROBADO
bool checkPos(attr at1, attr at2){
  bool ok = true;
  if(at1.type!=LIST){
    ok = false;
    printf("\n\033[1;31mError semántico línea %d: se ha recibido %s. Se esperaba lista. \033[0m\n", line, writeType(at1.type));
    semanticErrorCount++;
  }
  if(at2.type != INT){
    ok = false;
    printf("\n\033[1;31mError semántico línea %d: se ha recibido %s. Se esperaba entero. \033[0m\n", line, writeType(at2.type));
    semanticErrorCount++;
  }
  return ok;
}

//COMPROBADO
bool checkMultOp(attr at1, attr op, attr at2){
  bool ok = true;
  switch(op.n){
    case 0:// * lista y valor o valor y lista
      if(at1.type==at2.type && at1.type!=REAL && at1.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre %ss.\033[0m\n", line, writeType(at1.type));
        semanticErrorCount++;
      }
      else if(at1.type==LIST && at1.listType!=at2.type){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.type));
        semanticErrorCount++;
      }
      else if(at1.type==LIST && at1.listType==at2.type && at2.type!=REAL && at2.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.type));
        semanticErrorCount++;
      }
      else if(at2.type==LIST && at2.listType!=at1.type){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at2.listType), writeType(at1.type));
        semanticErrorCount++;
      }
      else if(at2.type==LIST && at2.listType==at1.type && at1.type!=REAL && at1.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at2.listType), writeType(at1.type));
        semanticErrorCount++;
      }
      break;
    case 1:// / solo lista y valor
      if(at1.type==at2.type && at1.type!=REAL && at1.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre %ss.\033[0m\n", line, writeType(at1.type));
        semanticErrorCount++;
      }
      else if(at1.type==LIST && at1.listType!=at2.type){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.type));
        semanticErrorCount++;
      }
      else if(at1.type==LIST && at1.listType==at2.type && at2.type!=REAL && at2.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.type));
        semanticErrorCount++;
      }
      break;
    case 2: //% solo aceptamos lista y posicion
      if(at1.type!=LIST){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: se esperaba lista, se ha recibido %s.\033[0m\n", line, writeType(at1.type));
        semanticErrorCount++;
      }
      if(at2.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: se esperaba entero, se ha recibido %s.\033[0m\n", line, writeType(at2.type));
        semanticErrorCount++;
      }
      break;
    default:
      break;
  }
  return ok;
}

//COMPROBADOS MENSAJES
bool checkBinOp(attr at1, attr op, attr at2){
  bool ok = true;
  switch(op.n){
    case 0: //+
      if(at1.type!=at2.type){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no compatible entre %s y %s.\033[0m\n", line, writeType(at1.type), writeType(at2.type));
        semanticErrorCount++;
      }
      else if(at1.type==at2.type && at1.type!=INT && at1.type!=REAL){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no compatible entre %s y %s.\033[0m\n", line, writeType(at1.type), writeType(at2.type));
        semanticErrorCount++;
      }
      else if(at1.type==LIST){ //la lista solo puede ir en primera posicion
        if(at1.listType!=REAL && at1.listType!=INT){
          ok = false;
          printf("\n\033[1;31mError semántico línea %d: se ha recibido lista de %s. Se esperaba lista de enteros o reales.\033[0m\n", line, writeType(at1.listType));
          semanticErrorCount++;
        }
        else if(at1.listType!=at2.type){
          ok=false;
          printf("\n\033[1;31mError semántico línea %d: operación no compatible entre lista de %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.type));
          semanticErrorCount++;
        }
      }
      else if(at2.type==LIST){
        if(at2.listType!=REAL && at2.listType!=INT){
          ok = false;
          printf("\n\033[1;31mError semántico línea %d: se ha recibido lista de %s. Se esperaba lista de enteros o reales.\033[0m\n", line, writeType(at1.listType));
          semanticErrorCount++;
        }
        else if(at2.listType!=at1.type){
          ok=false;
          printf("\n\033[1;31mError semántico línea %d: operación no compatible entre lista de %s y %s.\033[0m\n", line, writeType(at2.listType), writeType(at1.type));
          semanticErrorCount++;
        }
      }
      break;
    case 1: //-
      if(at1.type!=at2.type){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no compatible entre %s y %s.\033[0m\n", line, writeType(at1.type), writeType(at2.type));
        semanticErrorCount++;
      }
      else if(at1.type==at2.type && at1.type!=REAL && at1.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no compatible entre %s y %s.\033[0m\n", line, writeType(at1.type), writeType(at2.type));
        semanticErrorCount++;
      }
      if(at1.type==LIST){ //la lista solo puede ir en primera posicion
        if(at1.listType!=REAL && at1.listType!=INT){
          ok = false;
          printf("\n\033[1;31mError semántico línea %d: se ha recibido lista de %s. Se esperaba lista de enteros o reales.\033[0m\n", line, writeType(at1.listType));
          semanticErrorCount++;
        }
        else if(at1.listType!=at2.type){
          ok = false;
          printf("\n\033[1;31mError semántico línea %d: operación no compatible entre lista de %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.type));
          semanticErrorCount++;
        }
      }
      else if(at2.type==LIST){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: la lista no puede ir en segunda posición.\033[0m\n", line);
        semanticErrorCount++;
      }
      break;
    default:
      break;
  }

  return ok;
}

//COMPROBADOS MENSAJES
//Menos menos (solo para listas)
bool checkMinMin(attr at1, attr at2){
  bool ok = true;
  if(at1.type!=LIST){
    printf("\n\033[1;31mError semántico línea %d: %s es de tipo %s. Se esperaba lista.\033[0m\n", line, at1.lex, writeType(at1.type));
    semanticErrorCount++;
    ok = false;
  }
  if(at2.type!=INT){
    printf("\n\033[1;31mError semántico línea %d: %s es de tipo %s. Se esperaba entero.\033[0m\n", line, at2.lex, writeType(at2.type));
    semanticErrorCount++;
    ok = false;
  }
  return ok;
}

//COMPROBADOS MENSAJES
//operador ternario
bool checkTernOp(attr at1, attr at2, attr at3){
  bool ok = true;
  //probamos primera posicion
  if(at1.type != LIST){
    ok = false;
    printf("\n\033[1;31mError semántico línea %d: %s es de tipo %s. Se esperaba tipo lista.\033[0m\n", line, at1.lex, writeType(at1.type));
    semanticErrorCount++;
  }
  //probamos segunda posicion. el orden de estas dos es importante
  if(at1.type==LIST && at1.listType != at2.type){ //se le tiene que sumar un valor del mismo tipo del que tenga la lista
    printf("\n\033[1;31mError semántico línea %d: tipo %s no compatible con el tipo de la lista %s.\033[0m\n", line, writeType(at2.type), writeType(at1.listType));
    semanticErrorCount++;
    ok = false;
  }
  //probamos tercera posicion
  if(at3.type != INT){
    printf("\n\033[1;31mError semántico línea %d: se ha proporcionado tipo %s. Se esperaba un valor entero.\033[0m\n", line, writeType(at3.type));
    semanticErrorCount++;
    ok = false;
  }
  return ok;
}

/*Fin de lista de funciones y procedimientos para el manejo de la TS*/


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/* Codigo intermedio */

void printDebug(const char * string) {
    if (DEBUG) printf("\n\tDEBUG -- %s --\n",string);
    fflush(stdin);
}

void tsPushDescrip(TSentry e){

  checkLimit();
  ts[tsSize].entry = e.entry;
  ts[tsSize].name = e.name;
  ts[tsSize].dt = NONE;
  ts[tsSize].listType = NONE;
  ts[tsSize].nParam = 0;
  ts[tsSize].desc = e.desc;
  tsSize++;
}

int tsSearchLastET(entryType et) {

    int i;
    for (i = getTsTop(); i >=0; i-- )
        if (ts[i].entry == et)
            return i;

    return -1;
}

void initFilesAndHeaders(){

    printDebug("Iniciando codigo intermedio");

    // Create output code file
    mainFile = fopen("generatedCode/mainCode.c", "w");
    currentFile = mainFile;
    fputs("#include <stdio.h>\n", mainFile);
    fputs("#include \"dec_dat.h\"\n", mainFile);

    // Before translate "main" statement, globals variables must be defined
}

void finalize(){
    // Close the files opened on initFilesAndHeaders function
    fclose(mainFile);

    // TODO also remove the files if we got a semantic or sintactic error
}

void copyCuart(cuart *cNew, const cuart *cOriginal) {
    cNew->start = cOriginal->start;
    cNew->varConst = cOriginal->varConst;
    //cNew->st = cOriginal->st;
    cNew->a1 = cOriginal->a1;
    cNew->a2 = cOriginal->a2;
    cNew->op = cOriginal->op;
    cNew->result = cOriginal->result;
}

void tciAdd (cuart c) {
    if (semanticErrorCount || syntacticErrorCount)
        return;

    //Check if the limit of the stack has been reach
    if (tciSize >= MAX_TS) {
        printf("\nERROR: Alcanzado el maximo de la pila del codigo intermedio\n");
        return;
    }

    //If new cuart is just a start flag, is no need to copy all the data.
    if (c.start) {
        tci[tciSize].start = true;
        tci[tciSize].result.name = c.result.name;
        //printf("\nStart añadido en pos: %d\n", tciSize);
    } else {
        // Copy all the data contain in cuart c
        copyCuart(&tci[tciSize], &c);
    }

    tciSize++;
}

unsigned int getTopTciIndex(){
    if (semanticErrorCount || syntacticErrorCount)
        return 0;

    if (tciSize <= 0) {
        printf("\nERROR: Solicitada informacion a la pila de codigo intermedio estando vacia\n");
        return 0;
    }
    return tciSize-1;
}

cuart* getFromTci(int index){
    if (index < 0 || index > tciSize) {
        printf("\nERROR: Indice de tabla de codigo intermedio fuera de rango\n");
        return 0;
    }
    return &tci[index];
}

// Clear the stack until the start of the asignation
void tciClearUntilStart(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    int currentTop = getTopTciIndex();
    while (!tci[currentTop].start && currentTop > 0) {
        currentTop--;
    }

    tciSize = currentTop+1;
}

// Iterate upward on the tci stack until reach a start flag
int searchToStart(){
    if (semanticErrorCount || syntacticErrorCount)
        return 0;

    int i;
    for (i = getTopTciIndex(); i >= 0; i--)
        if (tci[i].start)
            return i;

    //printf("\nERROR: No se ha encontrado ningun flag de inicio de simplificacion de expresion\n");
    return 0;
}

// Just to set a flag to know where the split expressions start.

void startSplitExpressions(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    cuart newCuart;
    newCuart.start = true;
    newCuart.result.name = NULL;
    tciAdd(newCuart);
}
// Just to set a flag to know where the split expressions start.
void startSplitExpressionsWithName(const char * variableName){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    cuart newCuart;
    newCuart.start = true;
    newCuart.result.name = strdup(variableName);
    tciAdd(newCuart);
}

void addExpresion(attr a1, attr op, attr a2, attr *result){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    char *newTempName = genNextTempVarName(); //genNe.... Actually return a copy of the pointer no need for strdup

    cuart newCuart;
    newCuart.a1.name = strdup(a1.lex);
    newCuart.a2.name = strdup(a2.lex);
    newCuart.op.name = strdup(op.lex);
    newCuart.result.dt = result->type;
    newCuart.result.listType = result->listType;
    newCuart.result.name = strdup(newTempName);
    //newCuart.result.isList = result->isList;
    newCuart.start = false;
    newCuart.varConst = false;

    if (strcmp(op.lex, "--") == 0 ) {
        char functionCall[50];

        sprintf(functionCall, "getLength(&%s)", a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "%") == 0) {
        char functionCall[50];

        sprintf(functionCall, "removeToEnd_%s(&%s,%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "@") == 0) {
        char functionCall[50];

        sprintf(functionCall, "get_%s(&%s,%s)", getStrtypeList(a1), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "**") == 0) {
        char functionCall[50];

        sprintf(functionCall, "link_%s(&%s,&%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "+") == 0 && a1.type == LIST) {
        char functionCall[50];

        sprintf(functionCall, "sumVal_%s(&%s,%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "+") == 0 && a2.type == LIST) {
        char functionCall[50];

        sprintf(functionCall, "sumList_%s(&%s,%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "-") == 0 && a1.type == LIST) {
        char functionCall[50];

        sprintf(functionCall, "subVal_%s(&%s,%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "*") == 0 && a1.type == LIST) {
        char functionCall[50];

        sprintf(functionCall, "prod_%s(&%s,%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "*") == 0 && a2.type == LIST) {
        char functionCall[50];

        sprintf(functionCall, "prodList_%s(&%s,%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "/") == 0 && a1.type == LIST) {
        char functionCall[50];

        sprintf(functionCall, "divVal_%s(&%s,%s)", getStrtypeList(a2), a1.lex, a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }

    result->lex = strdup(newTempName);
    tciAdd(newCuart);
}

// For the ternary operator for the lists
// We will translate this to a function call, soo we adress this like a unary operator
// No need to get the operators, we have only one ternary op.
void addExpresionTernary(attr a1, attr a2, attr a3, attr *result){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    char *newTempName = genNextTempVarName(); //genNe.... Actually return a copy of the pointer no need for strdup

    char functionCall[50];

    sprintf(functionCall, "insert_%s(&%s,%s,%s)", getStrtypeAttr(a1) ,a1.lex, a2.lex, a3.lex);

    cuart newCuart;
    newCuart.a1.name = strdup("");
    newCuart.a2.name = strdup(functionCall);
    newCuart.op.name = strdup("");
    newCuart.result.dt = result->type;
    newCuart.result.listType = result->listType;
    newCuart.result.name = strdup(newTempName);
    //newCuart.result.isList = result->isList;
    newCuart.start = false;
    newCuart.varConst = false;

    result->lex = strdup(newTempName);

    tciAdd(newCuart);
}

// For unary expression like "!a" or "-a"
// Same behaviour as addExpresion but, omit the first identificator
void addExpresionUnary(attr op, attr a2, attr *result){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    char *newTempName = genNextTempVarName(); //genNe.... Actually return a copy of the pointer no need for strdup

    cuart newCuart;
    newCuart.a1.name = strdup(""); //Omit the attr name
    newCuart.a2.name = strdup(a2.lex);
    newCuart.op.name = strdup(op.lex);
    newCuart.result.dt = result->type;
    newCuart.result.listType = result->listType;
    newCuart.result.name = strdup(newTempName);
    //newCuart.result.isList = result->isList;
    newCuart.start = false;
    newCuart.varConst = false;

    result->lex = strdup(newTempName);

    if (strcmp(op.lex, "#") == 0 ) {
        char functionCall[50];

        sprintf(functionCall, "getLength(&%s)", a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "?") == 0) {
        char functionCall[50];

        sprintf(functionCall, "getActual_%s(&%s)", getStrtypeList(a2), a2.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }

    tciAdd(newCuart);
}

// For unary expression like "l>>"
// Same behaviour as addExpresionUnary but with the operators on the right
void addExpresionUnaryRight(attr op, attr a1, attr *result){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    char *newTempName = genNextTempVarName(); //genNe.... Actually return a copy of the pointer no need for strdup

    cuart newCuart;
    newCuart.a1.name = strdup(a1.lex); //Omit the attr name
    newCuart.a2.name = strdup("");
    newCuart.op.name = strdup(op.lex);
    newCuart.result.dt = result->type;
    newCuart.result.listType = result->listType;
    newCuart.result.name = strdup(newTempName);
    //newCuart.result.isList = result->isList;
    newCuart.start = false;
    newCuart.varConst = false;

    result->lex = strdup(newTempName);

    if (strcmp(op.lex, ">>") == 0 ) {
        char functionCall[50];

        sprintf(functionCall, "moveRight(&%s)", a1.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }
    else if (strcmp(op.lex, "<<") == 0) {
        char functionCall[50];

        sprintf(functionCall, "moveLeft(&%s)", a1.lex);
        newCuart.a1.name = strdup("");
        newCuart.a2.name = strdup(functionCall);
        newCuart.op.name = strdup("");
    }

    tciAdd(newCuart);
}

// For expresion of only a variable or constant
// This is usefull when we have a assignation like "a = b;"
void addExpresionSingle(attr a1, attr *result){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    cuart newCuart;
    newCuart.a1.name = strdup(a1.lex);
    newCuart.result.dt = result->type;
    newCuart.result.name = strdup(a1.lex);
    //newCuart.result.isList = result->isList;
    newCuart.result.listType = result->listType;
    newCuart.start = false;
    newCuart.varConst = true;

    tciAdd(newCuart);
}

void addExpresionConstList(attr a1, attr *result){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    char *newTempName = genNextTempVarName(); //genNe.... Actually return a copy of the pointer no need for strdup

    char functionCall[50];

    sprintf(functionCall, "createList_%s(%d,%s)", getStrtypeList(a1), listValuesCounter, a1.lex);
    listValuesCounter = 0;

    cuart newCuart;
    newCuart.a1.name = strdup(functionCall); //Omit the attr name
    newCuart.a2.name = strdup("");
    newCuart.op.name = strdup("");
    newCuart.result.dt = result->type;
    newCuart.result.listType = result->listType;
    newCuart.result.name = strdup(newTempName);
    //newCuart.result.isList = result->isList;
    newCuart.start = false;
    newCuart.varConst = true;

    result->lex = strdup(newTempName);

    tciAdd(newCuart);
}


// Resolve the split expresions and write the new simplified expresions
void endSplitExpressions (){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    // Pointer to the current cuart
    cuart *currentCuart;

    // Find the start flag on the stack
    unsigned int flagIndex = searchToStart();

    // Get the index for the first expression
    unsigned int expIndex = flagIndex + 1;

    // Check if we have a initial variable to asign the final expression
    bool hasVariableName = false;
    if (tci[flagIndex].result.name != NULL)
        hasVariableName = true;

    // Check if we hace a single asignation like "a = b" or just "b"
    if (expIndex == tciSize-1 && hasVariableName) {

        char newExp[200];
        currentCuart = &tci[expIndex];
        currentCuart->result.name = tci[flagIndex].result.name;
        currentCuart->result.dt = NONE;
        sprintf(newExp, "%s = %s;",
                currentCuart->result.name,
                currentCuart->a1.name);
        writeInFile(newExp);

    } else {
        while (expIndex < tciSize) {
            char newExp[200] ;
            currentCuart = &tci[expIndex];

            // Ignore the expression if just a var name or a constant was read.
            if (currentCuart->varConst){
                expIndex++;
                continue;
            }

            if (hasVariableName && expIndex == tciSize - 1) {
                currentCuart->result.name = tci[flagIndex].result.name;
                currentCuart->result.dt = NONE;
                tempCounter--;
                sprintf(newExp, "%s = %s %s %s;",
                        currentCuart->result.name,
                        currentCuart->a1.name,
                        currentCuart->op.name,
                        currentCuart->a2.name);
            } else {
                sprintf(newExp, "%s %s = %s %s %s;",
                        getStrtype(currentCuart->result),
                        currentCuart->result.name,
                        currentCuart->a1.name,
                        currentCuart->op.name,
                        currentCuart->a2.name);
            }
            writeInFile(newExp);
            expIndex++;
        }
    }

    startSplitExpressions();
}

// Generate the next temporal variable name
char * genNextTempVarName() {

    char temp[10];
    tempCounter++;
    sprintf(temp, "temp%d", tempCounter);
    return strdup(temp);
}

// Generate the next label name
char * genNextLabelName() {

    char temp[30];
    labelsCounter++;
    sprintf(temp, "etiqueta%d", labelsCounter);
    return strdup(temp);
}


/*


*/
/*
//funcion que traduce una sentencia LEER
//sentencia leer en c : scanf("% en primer lugar
//analizamos Tipo
//imprimimos tipo en FILE
//cerramos sentencia scanf
void traducirLeer(attr a){
  fputs("scanf(\"%",arch);
  //tenemos que pasar booleano a int
  if(a.dt == BOOL || a.dt == INT){fputs("d",arch);}
  else if(a.dt == REAL){fputs("f",arch);}
  else if(a.dt == CHAR){fputs("c",arch);}
  else {fputs("s",arch);}

  fputs("\", &", arch);
  fputs(a.name, arch);
  fputs(");", arch);
}*/
/*
//funcion que traduce una sentencia ESCRIBIR
void traducirEscribir(attr a){
  if( (a.dt != NOT_ASIG) || (a.dt != NONE) ){
    fputs("printf(\"%",arch) ;
    //tipo
    if(a.dt == BOOL || a.dt == INT){fputs("d",arch);}
    else if(a.dt == REAL){fputs("f",arch);}
    else if(a.dt == CHAR){fputs("c",arch);}
    //fin printf
    fputs("\", &", arch);
    fputs(a.name, arch);
    fputs(");\n", arch);
  }
  else{//si no hay tipo asignado
    fputs("printf(",arch) ;
    fputs(a.name, arch) ;
    fputs(");\n", arch) ;
  }
}
*/

char * getStrtype(TSentry a){

    char * strType;
    switch (a.dt) {
        case INT:
        case BOOL:
            strType = strdup("int");
            break;
        case REAL:
            strType = strdup("double");
            break;
        case CHAR:
            strType = strdup("char");
            break;
        case NONE:
            strType = strdup("");
            break;

        case LIST:
                {
                switch (a.listType) {
                    case INT:
                    case BOOL:
                        strType = strdup("list_int");
                        break;
                    case REAL:
                        strType = strdup("list_double");
                        break;
                    case CHAR:
                        strType = strdup("list_char");
                        break;
                    case NONE:
                        strType = strdup("");
                        break;
                }
            break;
            }
        default:
            printf("\tERROR, attr with-out data type defined");
            break;
    }
    //if (a.isList) strcat(strType, " *");
    return strType;
}

char * getStrtypeAttr(attr a){

    char * strType;
    switch (a.type) {
        case INT:
        case BOOL:
            strType = strdup("int");
            break;
        case REAL:
            strType = strdup("double");
            break;
        case CHAR:
            strType = strdup("char");
            break;
        case NONE:
            strType = strdup("");
            break;

        case LIST:
            {
                switch (a.listType) {
                    case INT:
                    case BOOL:
                        strType = strdup("list_int");
                        break;
                    case REAL:
                        strType = strdup("list_double");
                        break;
                    case CHAR:
                        strType = strdup("list_char");
                        break;
                    case NONE:
                        strType = strdup("");
                        break;
                }
            strType = strdup("");
            break;
            }
        default:
            printf("\tERROR, attr with-out data type defined");
            break;
    }
    //if (a.isList) strcat(strType, " *");
    return strType;
}

char * getStrtypeList(attr a){

    char * strType;
    switch (a.listType) {
        case INT:
        case BOOL:
            strType = strdup("int");
            break;
        case REAL:
            strType = strdup("double");
            break;
        case CHAR:
            strType = strdup("char");
            break;
        case NONE:
            strType = strdup("");
            break;
        default:
            printf("\tERROR, attr with-out data type defined");
            break;
    }
    //if (a.isList) strcat(strType, " *");
    return strType;
}

char * getStrTypeFormat(dataType d){

    char * strType;
    switch (d) {
        case INT:
        case BOOL:
            strType = strdup("d");
            break;
        case REAL:
            strType = strdup("f");
            break;
        case CHAR:
            strType = strdup("c");
            break;
        case LIST:
            strType = strdup("s");
            break;
        case NONE:
            strType = strdup("");
            break;
        default:
            printf("\tERROR, attr with-out data type defined");
            break;
    }
    //if (a.isList) strcat(strType, " *");
    return strType;
}

void redirectFunctionOutput(){
    currentFile = functionFile;
    nestingSubProgLevel++;
}
void redirectMainOutput(){
    nestingSubProgLevel--;
    if (nestingSubProgLevel == 0)
        currentFile = mainFile;
}

void writeInFile(char * string){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    printDebug("Escribiendo en archivo");

    if (string == NULL) {
        printf("\nERROR: Se intenta escribir una cadena NULL en el archivo\n");
        return;
    }

    if (currentFile == NULL) {
        printf("\nERROR: Se intenta escribir a un archivo no valido\n");
        return;
    }

    writeTabulations();
    fputs(string, currentFile);
}

void writeStartBrackets(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    if(mainVarDeclared){
        writeInFile("{\n");
        tabulationCount++;
    }
}
void writeEndBrackets(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    if (mainVarDeclared) {
        tabulationCount--;
        writeTabulations();
        writeInFile("}");
    }
}

void writeTabulations(){

    unsigned i = 0;
    fputs("\n", currentFile);
    for (i=0 ; i < tabulationCount; i++){
        fputs("\t", currentFile);
    }
}

void writeIf(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    // TODO aclarar si hay que incluir un par de llaves adicionales
    char string[200];

    // Create the labels for this sentence and push it to 'ts' stack
    TSentry newTSEntry;
    newTSEntry.entry = DESCRIPTOR;
    newTSEntry.name = strdup("");
    newTSEntry.desc.labelIn = genNextLabelName();
    newTSEntry.desc.labelOut = newTSEntry.desc.labelIn;
    newTSEntry.desc.labelElse = genNextLabelName();
    tsPushDescrip(newTSEntry);

    sprintf(string, "if (!%s) goto %s;",
            tci[getTopTciIndex()-1].result.name,
            newTSEntry.desc.labelIn);
    writeInFile(string);
    tciClearUntilStart();
}

void writeElse(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    // TODO aclarar si hay que incluir un par de llaves adicionales

    int indexLastDesc = tsSearchLastET(DESCRIPTOR);
    char string[200];

    ts[indexLastDesc].desc.labelOut = ts[indexLastDesc].desc.labelElse;

    sprintf(string, "goto %s;", ts[indexLastDesc].desc.labelOut);
    writeInFile(string);

    sprintf(string, "%s: ;", ts[indexLastDesc].desc.labelIn);
    writeInFile(string);

}

void writeEndIf(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    int indexLastDesc = tsSearchLastET(DESCRIPTOR);
    char string[200];

    sprintf(string, "%s: ;", ts[indexLastDesc].desc.labelOut);
    writeInFile(string);
}

void writeWhile(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    // TODO aclarar si hay que incluir un par de llaves adicionales
    char string[200];

    // Create the labels for this sentence and push it to 'ts' stack
    TSentry newTSEntry;
    newTSEntry.entry = DESCRIPTOR;
    newTSEntry.name = strdup("");
    newTSEntry.desc.labelIn = genNextLabelName();
    newTSEntry.desc.labelOut = genNextLabelName();
    newTSEntry.desc.labelElse = strdup("");
    tsPushDescrip(newTSEntry);

    sprintf(string, "%s: ;", newTSEntry.desc.labelIn);
    writeInFile(string);

    endSplitExpressions();

    sprintf(string, "if (!%s) goto %s;",
            tci[getTopTciIndex()-1].result.name,
            newTSEntry.desc.labelOut);
    writeInFile(string);
    tciClearUntilStart();
}

void writeEndWhile(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    int indexLastDesc = tsSearchLastET(DESCRIPTOR);
    char string[200];

    sprintf(string, "goto %s;", ts[indexLastDesc].desc.labelIn);
    writeInFile(string);

    sprintf(string, "%s: ;", ts[indexLastDesc].desc.labelOut);
    writeInFile(string);
}

void writeFor(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    char string[200];

    // Create the labels for this sentence and push it to 'ts' stack
    TSentry newTSEntry;
    newTSEntry.entry = DESCRIPTOR;
    newTSEntry.name = strdup("");
    newTSEntry.desc.labelIn = genNextLabelName();
    newTSEntry.desc.labelOut = genNextLabelName();
    newTSEntry.desc.labelElse = strdup("");
    tsPushDescrip(newTSEntry);

    sprintf(string, "%s: ;", newTSEntry.desc.labelIn);
    writeInFile(string);

    endSplitExpressions();

    sprintf(string, "if (!%s) goto %s;",
            tci[getTopTciIndex()-1].result.name,
            newTSEntry.desc.labelOut);
    writeInFile(string);
    tciClearUntilStart();
}

void writeEndFor(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    int indexLastDesc = tsSearchLastET(DESCRIPTOR);
    char string[200];

    sprintf(string, "goto %s;", ts[indexLastDesc].desc.labelIn);
    writeInFile(string);

    sprintf(string, "%s: ;", ts[indexLastDesc].desc.labelOut);
    writeInFile(string);
}

void writeLocalsVars(){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    // We need to check on the symbols table the variables declared.
    int i;

    // Get the index of the first variable declared
    for (i = getTsTop(); i >=0; i-- ){
        if (ts[i].entry != VAR){
            i++;
            break;
        }
    }

    // Now write it down in order from the index
    for (; i < tsSize; i++){
        char var[200];
        sprintf(var, "%s %s;", getStrtype(ts[i]), ts[i].name);
        writeInFile(var);
    }

    // If this variables are from main statement then we need to declared the main statement
    if (!mainVarDeclared) {
        writeInFile("int main()");
        mainVarDeclared = true;
        writeStartBrackets();
    }

}

void writePrintVariable(attr a){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    //dataType dt = getType(a);
    char string[200];
    char *format;
    endSplitExpressions();

    format = strdup(getStrTypeFormat(tci[getTopTciIndex()-1].result.dt));

    sprintf(string, "printf(\"%%%s\", %s);", format, tci[getTopTciIndex()-1].result.name);

    writeInFile(string);

}
void writePrintString(attr a){
    if (semanticErrorCount || syntacticErrorCount)
        return;

    char string[200];

    sprintf(string, "printf(\"%%s\", %s);", a.lex);

    writeInFile(string);
}

void writeEndPrint(){

    if (semanticErrorCount || syntacticErrorCount)
        return;

    char string[200];

    sprintf(string, "printf(\\n);");

    writeInFile(string);
}

void writeScan(attr a){

    if (semanticErrorCount || syntacticErrorCount)
        return;

    dataType dt = getType(a);
    char string[200];
    char *format;

    format = strdup (getStrTypeFormat(dt));

    sprintf(string, "scanf(\"%%%s\", &%s);", format, a.lex);

    writeInFile(string);
}

void writeSubProgHeader(){

    if (semanticErrorCount || syntacticErrorCount) return;


    // Get the index of the function identificator
    int funcNameIndex;
    for (funcNameIndex = getTsTop(); funcNameIndex >=0; funcNameIndex-- ){
        if (ts[funcNameIndex].entry == PROC){
            break;
        }
    }

    // Iterate over the parameters
    char *stringParams;
    int i = funcNameIndex+1;

    if (i < tsSize){
        stringParams = strdup(getStrtype(ts[i]));
        strcat(stringParams, " ");
        strcat(stringParams, ts[i].name);
        i++;
        for (; i < tsSize; i++ ){
            strcat(stringParams, ", ");
            strcat(stringParams, getStrtype(ts[i]));
            strcat(stringParams, " ");
            strcat(stringParams, ts[i].name);
        }
    }

    char string[200];
    sprintf(string, "void %s(%s)", ts[funcNameIndex].name, stringParams);
    writeInFile(string);
}

int getStartIndex(int nStart){

    int i;
    for (i = getTopTciIndex(); i >= 0 && nStart > 0; i--)
        if (tci[i].start == true){
            nStart--;
            if (nStart <=0) return i;
        }
    return i;
}

void writeProcCall(attr a, int nParam){

    int startCounter = 0;
    int index = 0;
    char string[200];
    strcat(string, a.lex);
    strcat(string, "(");

    if (nParam > 0) {
        index = getStartIndex(nParam);
        strcat(string, tci[index - 1].result.name);
        nParam--;
        while (nParam > 0){
            strcat(string, ", ");
            index = getStartIndex(nParam);
            strcat(string, tci[index-1].result.name);
            nParam--;
        }
    }
    strcat(string, ");");
    writeInFile(string);
}

char *concatenateValueSign(attr sign, attr value){

    if (semanticErrorCount || syntacticErrorCount) return strdup("");

    char aux[200];
    strcpy(aux, sign.lex);
    strcat(aux, value.lex);


    return strdup(aux);
}


char *concatenateListStringSign(attr sign, attr value, attr string){

    if (semanticErrorCount || syntacticErrorCount) return strdup("");

    char aux[200];
    strcpy(aux, sign.lex);
    strcat(aux, value.lex);
    strcat(aux,",");
    strcat(aux, string.lex);

    return strdup(aux);
}

char *concatenateListString(attr value, attr string){

  if (semanticErrorCount || syntacticErrorCount) return strdup("");

    char aux[200];
    strcpy(aux, value.lex);
    strcat(aux,",");
    strcat(aux, string.lex);

    return strdup(aux);
}
