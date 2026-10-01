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
Bool  stack_isEmpty(Stack s)
{
    return s->size == 0;
}

//Recibe un enetereo y lo guarda en la parye superior de la pila
void  stack_push(Stack s, int data)
{
    //Primero checo si mi pila existe
    if(s == NULL) 
    {
        return;
    }

    //Ahora si creo el nodo en memoria dinamica
    Node n = (Node)malloc(sizeof(struct strNode));
    //Esta de aqui solo es una validacion para checar que el malloc si se asigno
    if(n == NULL)
    {
        printf("Error no pude asignar mem\n");
        return;
    }

    //Aqui asigno los datos al nuevo nodo 
    n->data = data; //este recibe el valor que quiero guardar
    n->prior = s->top;

    //Aqui ya voy a enlazar el nuevo nodo con la pila

    //El nuevo nodo apunta al que era el tope.
    //Asi el nuevo nodo queda arriba del anterior tope
    //y mantiene la cadena hacia atras.
    n->prior = s->top;
    //Ahora el tope de la pila es el nuevo nodo
    //Aqui la pila ya conoce al nuevo como su elemento superior
    s->top = n;

    //Aqui solo actualizo el contador
    s->size++;
}

//Consulta el elemento en la parte superior de la pila
int  stack_top(Stack s)
{
    if(stack_isEmpty(s))
    {
        return 0;
    } else {
        return s->top->data;
    }
}

//Consulta y remeueve el elemento en la parte supeiorr de la pila
int  stack_pop(Stack s)
{
    //Checar que la pila no esta vacia xd
    if(stack_isEmpty(s)){
        printf("Cant perform pop on a empty stack\n");
        return 0;
    }

    //Primero guardo el nodo del top en una variable
    Node aux = s->top;

    //Despues guardo el dato del nodo antes de hacerle el free
    int toReturn = aux->data;

    //Ya aqui ahora si puedo mover mi tope al nodo anterior
    s->top = aux->prior;

    //Ya ahpra con eso enlazado le hago free del nodo que saque
    free(aux);

    //Actualizo el contador
    s->size--;

    //Devuelvo el dato que guarde en el [int d = n->data]
    return toReturn;
}

//Recorre la pila e imprime cada elemento, del tope hacia la base
//No modifica la pila, solo lee los datos de cada nodo
void  stack_print(Stack s)
{
    if(s == NULL)
    {
        return;
    }

    Node current = s->top;

    while(current != NULL)
    {
        printf("%d -> ", current->data);
        current = current->prior;
    }

    printf("NULL\n");
}

//Libera la memeoria reservada oara todos los nodos
//y aquella reservada para la estructura que representa a la pila
void  stack_destroy(Stack s)
{
    //Si la pila es null, no librearmos nancy    
    if(s == NULL)
    {
        return;
    }

    //Btw recorrere la pila nodo por nodo y liberar cada uno
    //Iniciar el recorrido en el tope de la pila
    Node current = s->top;

    //Ahora reccorro y libero cada nodo
    /*
    Mientras haya nodos
        Guardar el puntero al siguiente nodo (current->prior)
        antes de liberar el actual
        Liberar el nodo actual
        Avanzar al siguiente
    */
    while(current != NULL)
    {
        Node prior = current->prior; //Guardo el siguiente antes
        free(current); //libero el actual
        current = prior; //avanzo con el siguiente
    }

    //Libero la estructura strStack
    free(s);
}