#include <stdio.h>
#include <stdlib.h>
#include "errorCount.h"

extern FILE *yyin;

int yyparse(void);
unsigned int syntacticErrorCount = 0;
unsigned int semanticErrorCount = 0;
unsigned int warning = 0;

int main( int argc, char *argv[1]){
    int retCode;
    yyin = NULL;

    syntacticErrorCount = 0;
    semanticErrorCount = 0;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");

        if (yyin == NULL) {
            fprintf(stderr, "Error intentado leer fichero: '%s'\n", argv[1]);
            exit(1);
        } else {
            printf("\nProcesando archivo ´%s´...\n", argv[1]);
        }
    } else {
        printf("\nSe requiere un solo argumento indicando el fichero a procesar\n");
        exit(1);
    }

    retCode = yyparse();

	printf("\n");
    printf("---------------------------------------------------------------\n");
	if (retCode != 0) {
    	printf("Error al procesar el archivo argv[1]\n");
	} else {
    //imprimir mensaje de número de errores sintácticos
		if (syntacticErrorCount == 0) {
    	printf("\t\033[1;32mSe ha procesado el archivo sin ningun error sintáctico.\033[0m\n");
		}
    else {
			printf("\t\033[1;31mSe han encontrado %d errores sintácticos en el fichero\033[0m\n", syntacticErrorCount);
		}
    //imprimir mensaje de número de errores semánticos
    if (semanticErrorCount == 0) {
      printf("\t\033[1;32mSe ha procesado el archivo sin ningun error semántico.\033[0m\n");
    }
    else{
      printf("\t\033[1;31mSe han encontrado %d errores semánticos en el fichero\033[0m\n", semanticErrorCount);
    }
    //imprimir número de advertencias
    if (warning != 0) {
      printf("\t\033[1;33mSe han encontrado %d advertencias.\033[0m\n", warning);
    }
	}
    printf("---------------------------------------------------------------\n");

	return retCode;
}
