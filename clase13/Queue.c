#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>


typedef void *Type;
struct strNode
{
    Type data;
    struct strNode *next;
};

typedef struct strNode *Node;
struct strQueue
{
    // struct strNode *first, *last;
    Node first, last;
    int size;
};

Queue queue_create()
{
    Queue q = (Queue) malloc(sizeof(struct strQueue));
    if (q == NULL) return NULL;

    q->first = NULL;
    q->last  = NULL;
    q->size  = 0;

    return q;
}

int queue_size(Queue q)           // Extrae el tamaño de la cola
{
    if (q == NULL) return 0;
    return q->size;
}

Bool queue_isEmpty(Queue q)       // ¿El primero es nulo?
{
    if (q == NULL) return True;
    return (q->first == NULL) ? True : False;
}

Type queue_peek(Queue q)         // Consulta quién está al frente (no elimina)
{
    if (q == NULL || q->first == NULL) return NULL;
    return q->first->data;
}

void queue_offer(Queue q, Type d) // Se forma uno nuevo (colocarlo al final)
{
    if (q == NULL) return;

    //First creo el new nodo
    Node nuevo = (Node) malloc(sizeof(struct strNode));
    if (nuevo == NULL) return;

    nuevo->data = d;
    nuevo->next = NULL;

    //Despues tengo que referenciar la cola 
    if (q->last == NULL) //Caso: cola vacia
    {
        q->first = nuevo;
        q->last  = nuevo;
    }
    else //Caso: cola con elementos
    {
        q->last->next = nuevo;
        q->last       = nuevo;
    }

    q->size++;
}

Type queue_poll(Queue q)          // Atiende al que está al frente (elimina)
{
    if (q == NULL || q->first == NULL) return NULL;

    //Guardo el nodo y el dato a devolver
    Node nodeToPoll = q->first;
    Type toReturn   = nodeToPoll->data;

    //Avanzar first
    q->first = nodeToPoll->next;

    //Si la cola quedovacia, last entonces también debe ser NULL
    if (q->first == NULL)
        q->last = NULL;

    //Liberar el nodo
    free(nodeToPoll);

    //Decrementar tamaño
    q->size--;

    return toReturn;
}

void queue_destroy(Queue q)
{
    if (q == NULL) return;

    //Reccorro y libero cada nodo
    Node actual = q->first;
    while (actual != NULL)
    {
        Node temp = actual;
        actual = actual->next;
        free(temp);
    }

    //Le hago free para borrar todo
    free(q);
}
