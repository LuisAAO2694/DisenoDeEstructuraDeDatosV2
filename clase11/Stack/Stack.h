#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef void* Type;
typedef struct strStack* Stack;
typedef enum {False, True} Bool;

//Crea una pila vacia y devolver la referencia
Stack stack_create();

//Reporta la cantidad de elementos que actualemente hay en la pila
int   stack_size(Stack);

//Reporta si la pila esta vacía o no
Bool  stack_isEmpty(Stack);

//Recibe un enetereo y lo guarda en la parye superior de la pila
void  stack_push(Stack, int);

//Consulta el elemento en la parte superior de la pila
int  stack_top(Stack);

//Consulta y remeueve el elemento en la parte supeiorr de la pila
int  stack_pop(Stack);

//Imprime todos los elementos de la pila, del tope hacia la base
void  stack_print(Stack);

//Libera la memeoria reservada oara todos los nodos
//y aquella reservada para la estructura que representa a la pila
void  stack_destroy(Stack);

#endif