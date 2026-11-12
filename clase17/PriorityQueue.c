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

Type priorityQueue_poll(PriorityQueue pq) 
{
    //Si la cola está vacía, no hay nada que sacar
    if (pq == NULL || pq->size == 0) {
        return NULL;
    }

    //Respaldar al elemento que se encuentra en la "raíz"
    Type rootElement = pq->data[0];

    //Tomar al último elemento y sobreescribir con él al primero.
    //Ojo: Solo lo movemos si la cola tiene más de 1 elemento.
    if (pq->size > 1) {
        pq->data[0] = pq->data[pq->size - 1];
    }
    
    //Reducir size en 1 (porque ya sacamos el elemento)
    pq->size--;

    //Comparar el elemento que quedó en la "raíz" con sus hijos y hacer Bubble-Down
    int i = 0; //Índice actual, empezamos en la raíz
    
    //El ciclo se detiene cuando:
    //a) El elemento es más prioritario que sus hijos
    //b) Dicho elemento es una hoja (no tiene hijos)
    while (true) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i; //Asumimos que el padre es el más pequeño por ahora

        //Verificamos si el hijo izquierdo existe Y es menor que el actual más pequeño
        if (left < pq->size && pq->compare(pq->data[left], pq->data[smallest]) < 0) {
            smallest = left;
        }

        //Verificamos si el hijo derecho existe Y es menor que el actual más pequeño
        if (right < pq->size && pq->compare(pq->data[right], pq->data[smallest]) < 0) {
            smallest = right;
        }

        //Si el más pequeño sigue siendo el padre, significa que ya está en su lugar.
        //Esto cumple la condición de parada (a) y (b).
        if (smallest == i) {
            break;
        }

        //Si llegamos aquí, uno de los hijos era menor. Hacemos el swap
        //con el hijo más prioritario (el más pequeño).
        swap(&pq->data[i], &pq->data[smallest]);
        
        //Nos movemos hacia abajo para seguir revisando
        i = smallest;
    }

    //Devolver al elemento que respaldamos en el primer paso
    return rootElement;
}