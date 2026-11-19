#include "Map.h"
#include <stdlib.h>
#include <stdio.h>

struct strNode
{
    struct strNode *next;
    Type key, value;
};
typedef struct strNode *Node;

struct strMap
{
    HashFunc hash;
    CompareFunc compare;
    int M, size;
    Node *hashTable;
};

Node getNode(Map map, Type key)
{
    if (map == NULL)
        return NULL;

    int idx = map->hash(key) % map->M;
    Node current = map->hashTable[idx];

    while (current != NULL)
    {
        // Usamos la función compare del mapa.
        // Si devuelve verdadero (1), encontramos la llave.
        if (map->compare(current->key, key))
        {
            return current;
        }
        current = current->next;
    }

    // Si terminó el ciclo y no lo encontró, devuelve NULL
    return NULL;
}

Map map_create(int M, HashFunc hash, CompareFunc compare)
{
    if (M <= 0 || hash == NULL || compare == NULL) return NULL;

    Map map = (Map) malloc(sizeof(struct strMap));
    if (map == NULL) return NULL;

    map->hash = hash;
    map->compare = compare;
    map->M = M;
    map->size = 0;

    //calloc inicializa todas las cubetas en NULL
    map->hashTable = (Node*) calloc(M, sizeof(Node));
    if (map->hashTable == NULL) 
    {
        free(map);
        return NULL;
    }
    return map;
}

int map_size(Map m)
{
    return m->size;
}

Bool map_put(Map m, Type key, Type value)
{
    //Aplico la función de hashing para determinar el link
    int idx = m->hash(key) % m->M;
    
    //Buscamos si la llave ya existe usando nuestro auxiliar getNode
    Node existing = getNode(m, key);
    
    if (existing != NULL) 
    {
        //Si la llave ya existe, sobreescribo el valor
        existing->value = value;
        return True; 
    } else 
    {
        //Si la llave no existe, creamos un nuevo nodo
        Node newNode = (Node) malloc(sizeof(struct strNode));
        if (newNode == NULL) return False; //Por si falla la memoria
        
        newNode->key = key;
        newNode->value = value;
        newNode->next = NULL;
        
        if (m->hashTable[idx] == NULL) 
        {
            //Si la lista está vacía, el nuevo nodo es el primero
            m->hashTable[idx] = newNode;
        } 
        else 
        {
            //Si ya hay nodos, buscamos el final
            Node current = m->hashTable[idx];
            while (current->next != NULL) 
            {
                current = current->next;
            }
            //Enlazamos el último nodo con el nuevo
            current->next = newNode;
        }
        
        m->size++;
        return True;
    }
}

Bool map_contains(Map m, Type key)
{
    if (m == NULL) return False;

    //Alicamos la función hash y el módulo para obtener el índice
    int idx = m->hash(key) % m->M;

    //Recorremos la lista enlazada de esa cubeta
    Node current = m->hashTable[idx];
    while (current != NULL) 
    {
        //Comparamos la clave del nodo con la buscada
        if (m->compare(current->key, key)) {
            return True;   //la encontramos
        }
        current = current->next;
    }
    return False;
}


Type map_get(Map m, Type key)
{
    //Buscamos el nodo que contiene la llave
    Node n = getNode(m, key);
    
    //Si el nodo existe (no es NULL), devolvemos su valor.
    //Si no existe, getNode devolvió NULL, por lo que retornamos NULL.
    if (n != NULL) 
    {
        return n->value;
    } 
    else 
    {
        return NULL;
    }
}