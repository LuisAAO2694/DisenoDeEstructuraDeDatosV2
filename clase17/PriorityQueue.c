#include "PriorityQueue.h"
#include <stdlib.h>
#include <stdio.h>

struct strPriorityQueue {
    Type *data;
    int length;
    int size;
    CompareFunc compare;
};

PriorityQueue priorityqueue_create(int capacity, CompareFunc comparator) 
{
    
    PriorityQueue pq = malloc(sizeof(struct strPriorityQueue));
    
    //Reservamos memoria para el arreglo de apuntadores
    pq->data = malloc(sizeof(Type) * capacity);
    pq->length = capacity;
    pq->size = 0;
    pq->compare = comparator;

    return pq;
}

//Esta sirve para añadir un elemento al montículo
bool priorityqueue_offer(PriorityQueue pq, Type element) 
{
    if (pq == NULL) return false;

    //Checar si hay espacio en el arreglo
    //Ps si ya está lleno, redimensionamos
    if (pq->size == pq->length) 
    {
        //Duplico el valor de lenght
        pq->length = pq->length * 2;
        //Busco un new espacio y copio los datos ahi
        pq->data = realloc(pq->data, sizeof(Type) * pq->length);
    }

    //Inserto el new elemento al final del arreglo
    int i = pq->size;
    pq->data[i] = element;
    pq->size++;

    //Mientras no sea la raíz y sea menor que su padre, intercambiar
    while (i > 0) 
    {
        int p = parent(i);
        
        //Si el elemento actual es menor que su padre, le hago swap
        if (pq->compare(pq->data[i], pq->data[p]) < 0) 
        {
            swap(&pq->data[i], &pq->data[p]);
            i = p; //Vamonos hacia arriba
        } else {
            // Si ya es mayor o igual que el padre, ya esta ordenado
            break;
        }
    }

    return true;
}

// Devuelve el tamaño actual de la cola
int priorityqueue_size(PriorityQueue pq) 
{
    return pq->size;
}

// Obtiene el elemento con mayor prioridad SIN eliminarlo (Página 13)
Type priorityqueue_peek(PriorityQueue pq) 
{
    if (pq == NULL || pq->size == 0) {
        return NULL; // La cola está vacía
    }
    // En un min-heap, la raíz (índice 0) siempre tiene la mayor prioridad
    return pq->data[0];
}

//Destruye la cola y libera la memoria
//OJO: No libera los datos internos (Type), solo la estructura del arreglo
void priorityqueue_destroy(PriorityQueue pq) 
{
    if (pq == NULL) return;
    free(pq->data); // Liberamos el arreglo
    free(pq);       // Liberamos la estructura principal
}
