#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum {

	NOT_ASIG = 0,
	ENTERO,
	FLOTANTE,
	CARACTER,
	BOOLEANO,
	STRING,
	LIST,
	VACIO

} tipoDato;



#define YYSTYPE attrs
#define MAX_IN 1000
