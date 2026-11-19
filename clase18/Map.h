#ifndef MAP_H_
#define MAP_H_

typedef void *Type;

typedef enum
{
    False,
    True
} Bool;

typedef int (*HashFunc)(Type);
typedef int (*CompareFunc)(Type, Type);
typedef struct strMap *Map;

Map map_create(int M, HashFunc hash, CompareFunc compare);
int map_size(Map m);
Bool map_put(Map m, Type key, Type value);
Bool map_contains(Map m, Type key);
Type map_get(Map m, Type key);

#endif /* MAP_H_ */