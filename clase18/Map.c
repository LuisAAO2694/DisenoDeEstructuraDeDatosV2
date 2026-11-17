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

Node getNode(Map map, Type key);

map_create(int M, HashFunc hash, CompareFunc compare)
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

int map_size(Map m);
Bool map_put(Map m, Type key, Type value);
Bool map_contains(Map m, Type key);
Type map_get(Map m, Type key);