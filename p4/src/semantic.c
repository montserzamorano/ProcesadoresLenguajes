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

void cleanNamesParam(){
  int ind = getTsTop();
  while(ts[ind].entry!=PROC){
    ts[ind].name = "";
    ind--;
  }
  //printPila();
}

//comprueba si un procedimiento ha sido inizializada
bool isProcDeclared(attr at){
  //printf("\n\033[1;34mBuscando procedimiento...\033[0m\n");
  int ind = getTsTop();
  while(ind >= 0){
    if(ts[ind].entry == PROC && strcmp(ts[ind].name, at.lex) == 0){
      //printf("\n\033[1;34mEncontrado: %s %d...\033[0m\n", ts[ind].name,ind);
      return true;
    }
    ind--;
  }
  printf("\n\033[1;31mError semántico línea %d: el procedimiento %s no ha sido declarado. \033[0m\n", line, at.lex);
  semanticErrorCount++;

  return false;
}
void checkLimit(){
  //printf("\n\033[1;34mTAMAÑO DE LA PILA %d\033[0m\n", tsSize);
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
  //printf("\n\033[1;34mInsertando marca de inicio de bloque...\033[0m\n");
}

void tsPop(){
  //printf("\n\033[1;34mTAMAÑO DE LA PILA %d\033[0m\n", tsSize);
  //printf("\n\033[1;34mBorrando %s...\033[0m\n", ts[getTsTop()].name);
  tsSize--;
}
//limpia las entradas de la ts que corresponden a un mismo bloque
void tsPopMark(){
  while (ts[getTsTop()].entry != MARK && getTsTop() >= 0) tsPop();
  if (tsSize != 0) tsPop(); //esta ultima quita la marca
}

void tsPushVar(attr at){
  if(isIDdeclared(at)){
    printf("\n\033[1;31mError semántico línea %d: el ID %s ya está en uso. \033[0m\n", line, at.lex);
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
  /*if(TMPtype!=LIST)
    printf("\n\033[1;34mInsertando variable %s.Tipo %s.\033[0m\n", at.lex, writeType(ts[tsSize-1].dt));
  else
    printf("\n\033[1;34mInsertando variable %s.Tipo %s. Tipo lista %s\033[0m\n", at.lex, writeType(ts[tsSize-1].dt), writeType(ts[tsSize-1].listType));*/
}

void tsPushProc(attr at){
  checkLimit();
  ts[tsSize].entry = PROC;
  ts[tsSize].name = at.lex;
  ts[tsSize].dt = NONE; //nunca devuelve nada es todo void
  ts[tsSize].nParam = 0; //inicializamos a 0 y si vamos encontrando parametros los sumamos
  tsSize++;

  currentFunction = getTsTop();
  //printf("\n\033[1;34mInsertando procedimiento %s...\033[0m\n", at.lex);
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
  /*if(isIDdeclared(at)){
    printf("\n\033[1;31mError semántico línea %d: el ID %s ya está en uso. \033[0m\n", line, at.lex);
    semanticErrorCount++;
    tsPushParamError(at);
    return;
  }*/
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
  return NOT_ASIG;
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
  return NONE;
}

bool checkDataType(attr a, dataType t){
  if(a.type == t){
    return true;
  }

  printf("\n\033[1;31mError semántico línea %d: %s no es de tipo %s. \033[0m\n", line, a.lex, writeType(t));
  semanticErrorCount++;

  return false;
}

bool checkCondition(attr a){
  if(a.type == BOOL){
    return true;
  }

  printf("\n\033[1;31mError semántico línea %d: la expresión no es de tipo booleano. \033[0m\n", line);
  semanticErrorCount++;

  return false;
}

bool checkListType(attr a, dataType lt){
  if(a.type == lt && a.isList){return true;}
  return false;
}

bool isList(attr a){
  if(a.isList){return true;}
  return false;
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

bool checkAssign(attr res, attr exp){
  if(exp.type==ERROR){
    return false;
  }

  if(isIDdeclared(res)){//si el resultado ha sido declarado
    //printPila();
    //printf("\n\033[1;34m %s recibido. Tipo: %s.\033[0m\n", res.lex, writeType(res.type));
    if(res.type != exp.type){
        printf("\n\033[1;31mError semántico línea %d: incompatibilidad de tipos en la asignación. El valor es de tipo %s. Se esperaba %s.\033[0m\n", line, writeType(exp.type), writeType(res.type));
        semanticErrorCount++;
        return false;
    }
    else if(res.type == LIST && res.listType != exp.listType){
        printf("\n\033[1;31mError semántico línea %d: incompatibilidad de tipos en la asignación. El valor es de tipo %s. Se esperaba %s.\033[0m\n", line, writeType(exp.listType), writeType(res.type));
        semanticErrorCount++;
        return false;
    }
  }
  return true;
}

//REVISAR ESTO

bool checkUnitaryOp(attr op, attr at){
  switch(op.n){
    case 0: //&
      if(!isIDdeclared(at)){//si es variable
        printf("\n\033[1;31mError semántico línea %d: la variable %s no existe.\033[0m\n", line, at.lex);
        semanticErrorCount++;
        return false;
      }
      break;
    case 1: //!
      if(at.type != BOOL){
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

// || y &&
bool checkLogicOrAnd(attr at1, attr at2){
  if(at1.type != BOOL || at2.type != BOOL){
    printf("\n\033[1;31mError semántico línea %d: ambos tipos deben ser lógicos.\033[0m\n", line);
    semanticErrorCount++;
    return false;
  }
  return true;
}

bool compatibleRealInt(attr at1, attr at2){
  if( (at1.type == REAL && at2.type == INT)||(at2.type == REAL && at1.type == INT)){
    return true;
  }
  return false;
}

bool compatibleRealIntList(attr at1, attr at2){
  if( (at1.listType == REAL && at2.listType == INT)||(at2.listType == REAL && at1.listType == INT)){
    return true;
  }
  return false;
}

bool checkSign(attr at){
  if(at.type == INT || at.type == REAL){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: %s no es numérico.\033[0m\n", line, at.lex);
  semanticErrorCount++;
  return false;
}

bool checkRelation(attr at1, attr at2){
  if(at1.type != at2.type){
    printf("\n\033[1;31mError semántico línea %d: %s no comparable con %s.\033[0m\n", line, writeType(at1.type), writeType(at2.type));
    semanticErrorCount++;
    return false;
  }
  if(at1.type == LIST||at2.type == LIST){
    printf("\n\033[1;31mError semántico línea %d: operador no compatible con tipo lista.\033[0m\n", line);
    semanticErrorCount++;
    return false;
  }
  return true;
}

// ExOR y OrBit tienen que ser ambos de tipo entero??

bool checkExOr(attr at1, attr at2){
  if(at2.type == BOOL && at1.type==BOOL){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: ambos operandos tienen que ser de tipo lógico.\033[0m\n", line);
  semanticErrorCount++;
  return false;
}

bool checkOrBit(attr at1, attr at2){
  if(at2.type == INT){
    return true;
  }
  printf("\n\033[1;31mError semántico línea %d: es necesario un entero en la segunda posición.\033[0m\n", line);
  semanticErrorCount++;
  return false;
}

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

bool checkMultOp(attr at1, attr op, attr at2){
  bool ok = true;
  switch(op.n){
    case 0:// *
    case 1:// /
      if(at1.type==at2.type && at1.type!=REAL && at1.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida para %s.\033[0m\n", line, writeType(at1.type));
        semanticErrorCount++;
      }
      else if(at1.type==LIST && at1.listType!=at2.type){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.type));
        semanticErrorCount++;
      }
      else if(at2.type==LIST && at2.listType!=at1.type){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: operación no definida entre lista de %s y %s.\033[0m\n", line, writeType(at2.listType), writeType(at1.type));
        semanticErrorCount++;
      }
      break;
    case 2: //% solo aceptamos lista y posicion
      if(at1.type!=LIST&&at2.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: los tipos esperados son lista y entero, recibidos %s y %s.\033[0m\n", line, writeType(at1.listType), writeType(at2.listType));
        semanticErrorCount++;
      }
      else if(at1.type!=LIST){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: se esperaba lista, se ha recibido %s.\033[0m\n", line, writeType(at1.listType));
        semanticErrorCount++;
      }
      else if(at2.type!=INT){
        ok = false;
        printf("\n\033[1;31mError semántico línea %d: se esperaba entero, se ha recibido %s.\033[0m\n", line, writeType(at2.listType));
        semanticErrorCount++;
      }
    default:
      break;
  }
  return ok;
}

bool checkBinOp(attr at1, attr op, attr at2){
  bool ok = false;
  switch(op.n){
    case 0: //+
      if(at1.type==at2.type && at1.type!=INT && at2.type!=REAL){
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
      }
      else if(at2.type==LIST){ //la lista solo puede ir en primera posicion
        if(at2.listType!=REAL && at2.listType!=INT){
          ok = false;
          printf("\n\033[1;31mError semántico línea %d: se ha recibido lista de %s. Se esperaba lista de enteros o reales.\033[0m\n", line, writeType(at1.listType));
          semanticErrorCount++;
        }
      }
      break;
    case 1: //-
      if(at1.type==at2.type && at1.type!=REAL && at1.type!=INT){
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

//menos menos para listas

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

//operador ternario
bool checkTernOp(attr at1, attr at2, attr at3){
  bool ok = true;
  //probamos primera posicion
  if(at1.type != LIST){
    ok = false;
    printf("\n\033[1;31mError semántico línea %d: %s no es de tipo lista.\033[0m\n", line, at1.lex);
    semanticErrorCount++;
  }
  //probamos segunda posicion. el orden de estas dos es importante
  if(at1.listType != at2.type){ //se le tiene que sumar un valor del mismo tipo del que tenga la lista
    printf("\n\033[1;31mError semántico línea %d: tipo %s no compatible con el tipo de la lista %s.\033[0m\n", line, writeType(at2.type), writeType(at1.type));
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
