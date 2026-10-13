#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef void* Type;

struct strNode {
	Type data;
	struct strNode* next;
};

typedef struct strNode* Node;

struct strQueue {
	//struct strNode *first, *last;
	Node first, last;
	int size;
	printFunc print;
};

Queue queue_create(printFunc p) {
	//Crea una nueva cola
	//1. Reserva espacio en memoria dinámica para una estructura queue
	Queue q = malloc(sizeof(struct strQueue));
	//2. Asigna valores a las propiedades de la estructura (first, last y size)
	q->size = 0;
	q->first = NULL;
	q->last = NULL;
	q->print = p;
	//3. Devuelve el apuntador a queue al usuario
	return q;
}

int queue_size(Queue q) {
	//Extrae el tamaño de la cola
	return q->size;
}

Bool queue_isEmpty(Queue q) {
	//¿El primero es nulo?
	return q->size == 0;
}

Type queue_peek (Queue q) {
	//Consulta quién está al frente (no elimina)
	if (queue_isEmpty(q)) {
		return NULL;
	} else {
		return q->first->data;
	}
}

void queue_offer(Queue q, Type d) {
	//Se forma uno nuevo (colocarlo al final)
	//1. Reserva espacio en memoria dinámica para una estructura node
	//   y actualiza sus valores
	Node n = malloc(sizeof(struct strNode));
	n->data = d;
	n->next = NULL;
	//2. Revisa si la cola está vacía (si lo está, hay que actualizar tanto
	//   first como last; si no, sólo last). Antes de modificar last,
	//   hay que actualizar el next del anterior last.
	if (queue_isEmpty(q)) {
		q->first = n;
	} else {
		q->last->next = n;
	}
	q->last = n;
	//3. Actualiza size
	q->size ++;
}

Type queue_poll(Queue q) {
	//Atiende al que está al frente (elimina)
	if (queue_isEmpty(q)) {
		return NULL;
	} else {
		Node aux = q->first;
		Type toReturn = q->first->data;
		q->first = q->first->next;
		if (queue_size(q) == 1) {
			q->last = NULL;
		}
		q->size --;
		free(aux);
		return toReturn;
	}
}

void queue_destroy(Queue q) {
	while (!queue_isEmpty(q)) {
		queue_poll(q);
	}
	free(q);
	//Elimina a todos los nodos y a la cola misma
}

void queue_print(Queue q) {
	if (!queue_isEmpty(q)) {
		Node current = q->first;
		do {
			q->print(current->data);
			current = current->next;
		} while (current != NULL);
	}
	printf("\n");
}
