#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <stdbool.h>

//Definimos el tipo genérico y el apuntador a la función comparadora
typedef void* Type;
typedef int (*CompareFunc)(Type, Type);

//Exponemos el tipo PriorityQueue como un apuntador a la estructura interna
typedef struct strPriorityQueue* PriorityQueue;

// --- Métodos Públicos ---
PriorityQueue priorityqueue_create(int capacity, CompareFunc comparator);
void priorityqueue_destroy(PriorityQueue pq);
int priorityqueue_size(PriorityQueue pq);

bool priorityqueue_offer(PriorityQueue pq, Type element);
Type priorityqueue_peek(PriorityQueue pq);
Type priorityqueue_poll(PriorityQueue pq);

#endif /* PRIORITYQUEUE_H_ */