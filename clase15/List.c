/*
 * List.c
 *
 *  Created on: 13 oct 2026
 *      Author: diego.gilbert
 */

#include "List.h"
#include <stdlib.h>
#include <stdio.h>

struct strNode {
	Type data;
	struct strNode *next, *prior;
};

typedef struct strNode* Node;

struct strList {
	int size;
	Node first, last, preFirst, postLast;
	freeFunc free;
};

List list_create(freeFunc f) {
	//Reservar espacio para una estructura strList
	List l = malloc(sizeof(struct strList));
	//Asignarle valores a sus propiedades
	l->size = 0;
	l->first = NULL;
	l->last = NULL;
	l->free = f;
	//Devolver el apuntador tipo List al usuario

	l->preFirst = malloc(sizeof(struct strNode));
	l->postLast = malloc(sizeof(struct strNode));
	l->preFirst->prior = NULL;
	l->preFirst->next = NULL;
	l->preFirst->data = NULL;
	l->postLast->prior = NULL;
	l->postLast->next = NULL;
	l->postLast->data = NULL;
	return l;
}

void list_destroy(List l) {
	//--
	//Elemento por elemento, liberar la memoria reservada para cada nodo
	//y, por último, liberar la memoria reservada para la estructura strList
	Node current = l->first;
	while(current != NULL && current != l->postLast) {
		Node aux = current;
		current = current->next;
		l->free(aux->data);
		free(aux);
	}
	//--
	free(l->preFirst);
	free(l->postLast);
	free(l);
}

int list_size(List l) {
	//Devolver el tamaño de la lista
	return l->size;
}

void list_add(List l, Type e) {
	//Agregar un nuevo elemento al final de la lista
	//Reservar espacio para una estructura strNode
	Node n = malloc(sizeof(struct strNode));
	//Actualizar su propiedad next
	n->next = NULL;
	n->data = e;
	//Si la lista está vacía:
	//	Actualizar first
	//Si la lista no está vacía:
	//	Actualizar la propiedad prior del nodo que vamos a insertar
	//	Actualizar la propiedad next del actual last
	if(list_size(l) == 0) {
		l->first = n;
		n->prior = l->preFirst;
		l->preFirst->next = n;
	} else {
		n->prior = l->last;
		l->last->next = n;
	}
	//Actualizar last
	l->last = n;

	n->next = l->postLast;
	l->postLast->prior = n;
	//Incrementar el tamaño de la lista
	l->size ++;
}

Type list_get(List l, int i) {
	//Si el índice se encuentra fuera del rango posible,
	//devolver nulo y avisarle al usuario
	if (i >= l->size) {
		printf("Index %d out of bounds (list size %d)\n", i, l->size);
		return NULL;
	//Caso contrario, recorrer la lista hasta llegar al índice
	//especificado y devolverle al usuario el dato contenido en ese nodo
	} else {
		Node current = l->first;
		for (int p = 0; p < i; p ++) {
			current = current->next;
		}
		return current->data;
	}
}

void list_set(List l, Type e, int i) {
	//Si el índice se encuentra fuera del rango posible,
	//salir de la función y avisarle al usuario
	if (i >= l->size) {
		printf("Index %d out of bounds (list size %d)\n", i, l->size);
	//Caso contrario, recorrer la lista hasta llegar al índice
	//especificado y sobreescribir el dato del nodo con el recibido como argumento
	} else {
		Node current = l->first;
		for (int p = 0; p < i; p ++) {
			current = current->next;
		}
		current->data = e;
	}
}

Type list_remove(List l, int i) {
	if (i >= l->size) {
		printf("Index %d out of bounds (list size %d)\n", i, l->size);
		return NULL;
	} else {
		//Remover al nodo del índice especificado y devolverle al usuario
		//el dato almacenado en él
		Node current = l->first;
		for (int p = 0; p < i; p ++) {
			current = current->next;
		}
		Type toReturn = current->data;
		if (l->size == 1) {
			//1. El nodo que se va a remover es el único (primero y último)
			l->first = NULL;
			l->last = NULL;
			l->preFirst->next = NULL;
			l->postLast->prior = NULL;
		} else if (i == 0) {
			//2. El nodo que se va a remover es el primero, pero no el único
			l->first = l->first->next;
			l->first->prior = l->preFirst;//
			l->preFirst->next = l->first;//
		} else if (i == l->size - 1) {
			//3. El nodo que se va a remover es el último, pero no el único
			l->last = l->last->prior;
			l->last->next = l->postLast;//
			l->postLast->prior = l->last;//
		} else {
			//4. El nodo que se va a remover está en medio
			current->next->prior = current->prior;
			current->prior->next = current->next;
		}
		free(current);
		l->size --;
		return toReturn;
	}
}

void list_insert(List l, Type e, int i) {
	if (i > l->size) {
		printf("Index %d out of bounds (list size %d)\n", i, l->size);
	} else {
		//Insertar al nuevo nodo del índice especificado
		Node current = l->first;
		for (int p = 0; p < i; p ++) {
			current = current->next;
		}
		Node n = malloc(sizeof(struct strNode));
		n->data = e;
		if (l->size == 0) {
			//1. El nodo que se va a insertar es el único (primero y último)
			l->first = n;
			l->last = n;
			n->prior = l->preFirst;
			n->next = l->postLast;
			l->preFirst->next = n;
			l->postLast->prior = n;
		} else if (i == 0) {
			//2. El nodo que se va a insertar es el primero, pero no el único
			//--
			n->prior = l->preFirst;
			//--
			n->next = l->first;
			l->first->prior = n;
			l->first = n;
			l->preFirst->next = n;
		} else if (i == l->size) {
			//3. El nodo que se va a insertar es el último, pero no el único
			//--
			n->next = l->postLast;
			//--
			n->prior = l->last;
			l->last->next = n;
			l->last = n;
			l->postLast->prior = n;
		} else {
			//4. El nodo que se va a insertar está en medio
			n->prior = current->prior;
			n->next = current;
			current->prior->next = n;
			current->prior = n;
		}
		l->size ++;
		// [ 0 ] <-> [ 1 ] <-> [ 2 ] <-> [ 3 ] <-> [ 4 ] <-> [ 5 ]
		//                                 ^
	}
}

Iterator list_begin(List l) 
{
    //Devuelve el iterador apuntando al pre-inicio (preFirst)
    return l->preFirst;
}

Iterator list_end(List l) 
{
    //Devuelve el iterador apuntando al post-final (postLast)
    return l->postLast;
}

//--
bool list_hasNext(Iterator it) 
{
    //Hacemos el cast a Node para poder acceder a ->next
    Node n = (Node)it;
    
    //Hay un siguiente si el nodo actual no es nulo 
    //Y su siguiente no es nulo ni es el centinela postLast (postLast->next es NULL)
    if (n != NULL && n->next != NULL && n->next->next != NULL) 
	{
        return true;
    }
    return false;
}
//--

//--
bool list_hasPrior(Iterator it) 
{
    Node n = (Node)it;
    
    //Hay un anterior si el nodo actual no es nulo 
    //Y su anterior no es nulo ni es el centinela preFirst (preFirst->prior es NULL)
    
	if (n != NULL && n->prior != NULL && n->prior->prior != NULL) 
	{
        return true;
    }
    return false;
}
//--

Iterator list_next(Iterator it) 
{
    Node n = (Node)it;
    if (n != NULL) 
	{
        return n->next; // Devuelve el apuntador al siguiente nodo
    }
    return NULL;
}

Iterator list_prior(Iterator it) 
{
    Node n = (Node)it;
    if (n != NULL) 
	{
        return n->prior; //Devuelve el apuntador al nodo anterior
    }
    return NULL;
}

Type list_data(Iterator it) 
{
    Node n = (Node)it;
    if (n != NULL)
	{
        return n->data;
    }
    return NULL;
}
