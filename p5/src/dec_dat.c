#include "dec_dat.h"


/******************************************************************************/
list createList_int(int count, ...) {
    va_list arg_list;
    int j = 0;

    list newList;
    node_int *StartNode = malloc(sizeof(node_int));
    newList.dataInt = StartNode;
    newList.dataDouble = NULL;
    newList.dataChar = NULL;
    newList.size = count;
    newList.actualIndex = 0;

    node_int *pointerNode = StartNode;

    va_start(arg_list, count);
    for (j = 0; j < count; j++) {
        pointerNode->val = va_arg(arg_list, int);
        pointerNode->next = malloc(sizeof(node_int));
        pointerNode = pointerNode->next;
    }

    free(pointerNode);

    va_end(arg_list);
    return newList;
}
list createList_double(int count, ...) {
    va_list arg_list;
    int j = 0;

    list newList;
    node_double *StartNode = malloc(sizeof(node_double));
    newList.dataInt = NULL;
    newList.dataDouble = StartNode;
    newList.dataChar = NULL;
    newList.size = count;
    newList.actualIndex = 0;

    node_double *pointerNode = StartNode;

    va_start(arg_list, count);
    for (j = 0; j < count; j++) {
        pointerNode->val = va_arg(arg_list, double);
        pointerNode->next = malloc(sizeof(node_double));
        pointerNode = pointerNode->next;
    }

    free(pointerNode);

    va_end(arg_list);
    return newList;
}
list createList_char(int count, ...) {
    va_list arg_list;
    int j = 0;

    list newList;
    node_char *StartNode = malloc(sizeof(node_char));
    newList.dataInt = NULL;
    newList.dataDouble = NULL;
    newList.dataChar = StartNode;
    newList.size = count;
    newList.actualIndex = 0;

    node_char *pointerNode = StartNode;

    va_start(arg_list, count);
    for (j = 0; j < count; j++) {
        pointerNode->val = va_arg(arg_list, int);
        pointerNode->next = malloc(sizeof(node_char));
        pointerNode = pointerNode->next;
    }

    free(pointerNode);

    va_end(arg_list);
    return newList;
}


/******************************************************************************/
int getLength(list * l) {
    return l->size;
}


/******************************************************************************/
int getActual_int(list * l) {
    return getNode_int(l,l->actualIndex)->val;
}
double getActual_double(list * l) {
    return getNode_double(l,l->actualIndex)->val;
}
char getActual_char(list * l) {
    return getNode_char(l,l->actualIndex)->val;
}


/******************************************************************************/
int get_int(list * l, int index) {
    return getNode_int(l, index)->val;
}
double get_double(list * l, int index) {
    return getNode_double(l, index)->val;
}
char get_char(list * l, int index) {
    return getNode_char(l, index)->val;
}


/******************************************************************************/
void moveRight(list * l) {
    if (l->actualIndex + 1 < l->size)
        l->actualIndex++;
    else printf("\n ERROR LISTAS: se intenta desplazar fuera de rango\n");
}

/******************************************************************************/
void moveLeft(list * l) {
    if (l->actualIndex - 1 >= 0)
        l->actualIndex--;
    else printf("\n ERROR LISTAS: se intenta desplazar fuera de rango\n");
}

/******************************************************************************/
void set_to_start(list * l) {
    l->actualIndex = 0;
}


/******************************************************************************/
node_int* getNode_int(list *l, int index){

    if (index >= l->size) {
        printf ("\n ERROR LISTAS: indice fuera de rango, valor indice: %d \n", index);
    }

    node_int* result = l->dataInt;

    int i=0;
    for (; i < index ;i++){
        result = result->next;
    }

    return result;
}
node_double* getNode_double(list *l, int index){

    if (index >= l->size) {
        printf ("\n ERROR LISTAS: indice fuera de rango");
    }

    node_double* result = l->dataDouble;

    int i=0;
    for (; i < index ;i++){
        result = result->next;
    }

    return result;
}
node_char* getNode_char(list *l, int index){

    if (index >= l->size) {
        printf ("\n ERROR LISTAS: indice fuera de rango");
    }

    node_char* result = l->dataChar;

    int i=0;
    for (; i < index ;i++){
        result = result->next;
    }

    return result;
}

/******************************************************************************/
void insert_int(list * l, int value, int index) {
    node_int *newNode = malloc(sizeof(node_int));
    
    newNode->val = value;

    node_int *aux = getNode_int(l, index - 1);
    newNode->next = aux->next;
    aux->next = newNode;
}
void insert_double(list * l, double value, int index) {
    node_double *newNode = malloc(sizeof(node_double));
    
    newNode->val = value;

    node_double *aux = getNode_double(l, index - 1);
    newNode->next = aux->next;
    aux->next = newNode;
}
void insert_char(list * l, char value, int index) {
    node_char *newNode = malloc(sizeof(node_char));
    
    newNode->val = value;

    node_char *aux = getNode_char(l, index - 1);
    newNode->next = aux->next;
    aux->next = newNode;
}

/******************************************************************************/
void remove_int(list * l, int index) {
    node_int *removeNode = getNode_int(l, index);
    node_int *auxnode = getNode_int(l, index-1);
    auxnode->next = removeNode->next;

    free(removeNode);
}
void remove_double(list * l, int index) {
    node_double *removeNode = getNode_double(l, index);
    node_double *auxnode = getNode_double(l, index - 1);
    auxnode->next = removeNode->next;

    free(removeNode);
}
void remove_char(list * l, int index) {
    node_char *removeNode = getNode_char(l, index);
    node_char *auxnode = getNode_char(l, index - 1);
    auxnode->next = removeNode->next;

    free(removeNode);
}


/******************************************************************************/
void removeToEnd_int(list * l, int index) {
    int i;
    for (i=l->size; i >= index; i++) {
        remove_int(l, i);
    }
}
void removeToEnd_double(list * l, int index) {
    int i;
    for (i = l->size; i >= index; i++)
    {
        remove_double(l, i);
    }
}
void removeToEnd_char(list * l, int index) {
    int i;
    for (i = l->size; i >= index; i++)
    {
        remove_char(l, i);
    }
}


/******************************************************************************/
list link_int(list * l1, list* l2) {

    node_int* lastL1 = getNode_int(l1, l1->size - 1);

    lastL1->next = l2->dataInt;
    l1->size += l2->size;
    return *l1;

}
list link_double(list * l1, list* l2) {
    node_double *lastL1 = getNode_double(l1, l1->size - 1);

    lastL1->next = l2->dataDouble;
    l1->size += l2->size;
    return *l1;
}
list link_char(list * l1, list* l2) {
    node_char *lastL1 = getNode_char(l1, l1->size - 1);

    lastL1->next = l2->dataChar;
    l1->size += l2->size;
    return *l1;
}


/******************************************************************************/
int sumVal_int(list * l, int val) {

    int retVal = val;

    node_int *aux = l->dataInt;
    while (aux -> next != NULL){
        retVal += aux->val;
        aux = aux->next;
    }
    return retVal;
}
double sumVal_double(list * l, double val) {
    double retVal = val;

    node_double *aux = l->dataDouble;
    while (aux -> next != NULL){
        retVal += aux->val;
        aux = aux->next;
    }
    return retVal;
}

/******************************************************************************/


list * sumList_int(list * l, int val) {

    node_int *aux = l->dataInt;
    while (aux -> next != NULL){
        aux->val += val;
        aux = aux->next;
    }
    return l;
}
list * sumList_double(list * l, double val) {

    node_double *aux = l->dataDouble;
    while (aux -> next != NULL){
        aux->val += val;
        aux = aux->next;
    }
    return l;
}


/******************************************************************************/
int subVal_int(list * l, int val) {

    int retVal = val;

    node_int *aux = l->dataInt;
    while (aux -> next != NULL){
        retVal -= aux->val;
        aux = aux->next;
    }
    return retVal;
}
double subVal_double(list * l, double val) {
    double retVal = val;

    node_double *aux = l->dataDouble;
    while (aux -> next != NULL){
        retVal -= aux->val;
        aux = aux->next;
    }
    return retVal;
}


/******************************************************************************/
int prod_int(list * l, int val) {

    int retVal = val;

    node_int *aux = l->dataInt;
    while (aux -> next != NULL){
        retVal *= aux->val;
        aux = aux->next;
    }
    return retVal;
}
double prod_double(list * l, double val) {
    double retVal = val;

    node_double *aux = l->dataDouble;
    while (aux -> next != NULL){
        retVal *= aux->val;
        aux = aux->next;
    }
    return retVal;
}

/******************************************************************************/


list * prodList_int(list * l, int val) {

    node_int *aux = l->dataInt;
    while (aux -> next != NULL){
        aux->val *= val;
        aux = aux->next;
    }
    return l;
}
list * prodList_double(list * l, double val) {

    node_double *aux = l->dataDouble;
    while (aux -> next != NULL){
        aux->val *= val;
        aux = aux->next;
    }
    return l;
}


/******************************************************************************/
int div_int(list * l, int val) {

    int retVal = val;

    node_int *aux = l->dataInt;
    while (aux -> next != NULL){
        retVal /= aux->val;
        aux = aux->next;
    }
    return retVal;
}
double div_double(list * l, double val) {
    double retVal = val;

    node_double *aux = l->dataDouble;
    while (aux -> next != NULL){
        retVal /= aux->val;
        aux = aux->next;
    }
    return retVal;
}