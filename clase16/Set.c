#include "Set.h"
#include <stdlib.h>
#include <stdio.h>

struct strNode {
    Type data;
    struct strNode *left, *right;
};

typedef struct strNode* Node;

struct strSet {
    Node root;
    int size;
    CompareFunc compareFunc;
};

// Creamos el conjunto
Set set_create(CompareFunc cf) 
{
    Set s = malloc(sizeof(struct strSet));
    s->root = NULL;
    s->size = 0;
    s->compareFunc = cf;
    return s;
}

int set_size(Set s) 
{
    return s->size;
}

bool set_add(Set s, Type t) {
    //Creo un nuevo nodo, guardar el dato y asignar nulos a los hijos
    Node n = malloc(sizeof(struct strNode));
    n->data = t;
    n->left = NULL;
    n->right = NULL;

    //Si el conjunto está vacío (la raíz es nula), la raíz será el nuevo nodo
    if (s->root == NULL) 
    {
        s->root = n;
        s->size++;
        return true;
    }

    //Si no, recorrer el árbol desde la raíz hacia abajo
    Node current = s->root;
    
    while (current != NULL) 
    {
        //Ejecutar la función de comparación
        int cmp = s->compareFunc(t, current->data);

        if (cmp == 0) 
        {
            //btw si devuelve 0, encontramos el valor. No se añade
            free(n); //Eliminamos de memoria al nuevo nodo creado
            return false; 
        } 
        else if (cmp < 0) {
            //Si devuelve negativo, vamos por la izquierda
            if (current->left == NULL) {
                //Si el hijo izquierdo no existe, será el nuevo nodo
                current->left = n;
                s->size++; //Incrementamos tamaño
                return true;
            }
            //Si existe, continuamos la búsqueda por ahí
            current = current->left;
        } 
        else {
            //Si devuelve positivo, vamos por la derecha
            if (current->right == NULL) {
                //Si el hijo derecho no existe, será el nuevo nodo
                current->right = n;
                s->size++; //Incrementamos tamaño
                return true;
            }
            //Si existe, continuamos la búsqueda por ahí
            current = current->right;
        }
    }
    
    return false;
}