#include <stdio.h>
#include <stdlib.h>
#include "errorCount.h"

extern FILE *yyin;

int yyparse(void);
unsigned int errorCount = 0;

int main( int argc, char *argv[1]){
    int retCode;
    yyin = NULL;

    errorCount = 0;

    if (argc == 2) {
        yyin = fopen(argv[1], "r");

        if (yyin == NULL) {
            fprintf(stderr, "Error intentado leer fichero: '%s'\n", argv[1]);
            exit(1);
        } else {
            printf("\nProcesando archivo ´%s´\n", argv[1]);
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
		if (errorCount == 0) {
    		printf("\t\033[1;32mSe ha procesador el archivo sin ningun error!!\033[0m\n");
		} else {
			printf("\t\033[1;31mSe han encontrado %d errores en el fichero\033[0m\n", errorCount);
		}
	}
    printf("---------------------------------------------------------------\n");

	return retCode;
}