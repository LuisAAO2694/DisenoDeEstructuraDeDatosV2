// Set.h
#ifndef SET_H
#define SET_H
#include <stdbool.h> 

typedef void* Type;
//El apuntador a la función comparadora
typedef int (*CompareFunc)(Type, Type); 

//El Set es un apuntador a la estructura interna
typedef struct strSet* Set; 

Set set_create(CompareFunc cf);
void set_destroy(Set s);
int set_size(Set s);
bool set_add(Set s, Type t);
bool set_contains(Set s, Type t);
void set_print(Set s);

#endif