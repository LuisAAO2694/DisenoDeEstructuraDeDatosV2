#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

struct strNode {
    int data;
    struct strNode *prior;
};

typedef struct strNode* Node;

struct strStack {
    struct strNode* top;
    int size;
};

Stack stack_create(){
    //Crea una pila vacia y devolver la referencia
    Stack s = malloc(sizeof(struct strStack));
    s->top = NULL;
    s->size = 0;
    return s;
}

int   stack_size(Stack s){
    //Reporta la cantidad de elementos que actualemente hay en la pila
    return s->size;
}

//Reporta si la pila esta vacía o no
Bool  stack_isEmpty(Stack);

//Recibe un enetereo y lo guarda en la parye superior de la pila
void  stack_push(Stack, int);

//Consulta el elemento en la parte superior de la pila
int  stack_top(Stack);

//Consulta y remeueve el elemento en la parte supeiorr de la pila
int  stack_pop(Stack);

//Libera la memeoria reservada oara todos los nodos
//y aquella reservada para la estructura que representa a la pila
void  stack_destroy(Stack);