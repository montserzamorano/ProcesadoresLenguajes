
#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum {
	BOOL,
	INT,
	FLOAT,
	CHAR,
	NONE
} type;

typedef struct node_int{
    int val;
    struct node_int * next;
} node_int;

typedef struct node_double{
    double val;
    struct node_double * next;
} node_double;

typedef struct node_char{
    char val;
    struct node_char * next;
} node_char;

typedef struct{
    node_int *dataInt;
    node_double * dataDouble;
    node_char * dataChar;
    int actualIndex;
    int size;
    type t;
} list, list_int, list_double, list_char;

list createList_int(int count, ...);
list createList_double(int count, ...);
list createList_char(int count, ...);
int getLength(list *l);
int getActual_int(list * l);
double getActual_double(list * l);
char getActual_char(list * l);
int get_int(list * l, int index);
double get_double(list * l, int index);
char get_char(list * l, int index);
void set_to_start(list * l);
node_int* getNode_int(list *l, int index);
node_double* getNode_double(list *l, int index);
node_char* getNode_char(list *l, int index);
void insert_int(list * l, int value, int index);
void insert_double(list * l, double value, int index);
void insert_char(list * l, char value, int index);
void remove_int(list * l, int index);
void remove_double(list * l, int index);
void remove_char(list * l, int index);
void removeToEnd_int(list * l, int index);
void removeToEnd_double(list * l, int index);
void removeToEnd_char(list * l, int index);
list link_int(list * l1, list* l2);
list link_double(list * l1, list* l2);
list link_char(list * l1, list* l2);
int sumVal_int(list * l, int val);
double sumVal_double(list * l, double val);
list * sumList_int(list * l, int val);
list * sumList_double(list * l, double val);
int subVal_int(list * l, int val);
double subVal_double(list * l, double val);
int prod_int(list * l, int val);
double prod_double(list * l, double val);
list * prodList_int(list * l, int val);
list * prodList_double(list * l, double val);
int div_int(list * l, int val);
double div_double(list * l, double val);

#endif
