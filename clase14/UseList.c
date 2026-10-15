// gcc -Wall Stack.c UseStack.c -o UseStack && ./UseStack
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
void freeInt(void *x)
{
    free(x);
}
int main()
{
    List myList = list_create(freeInt);
    for (int i = 0; i < 10; i++)
    {
        int *x = malloc(sizeof(int));
        *x = rand() % 100;
        list_add(myList, x);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%3d ", *((int *)list_get(myList, i)));
    }
    printf("\n");
    
    int *x = malloc(sizeof(int));
    *x = 7;
    list_insert(myList, x, 5);

    for (int i = 0; i < 11; i++)
    {
        printf("%3d ", *((int *)list_get(myList, i)));
    }
    printf("\n");

    x = malloc(sizeof(int));
    *x = 7;
    list_insert(myList, x, 0);

    x = malloc(sizeof(int));
    *x = 7;
    list_insert(myList, x, 12);

    for (int i = 0; i < 13; i++)
    {
        printf("%3d ", *((int *)list_get(myList, i)));
    }
    printf("\n");

    free(list_remove(myList, 12));
    free(list_remove(myList, 0));
    x = list_remove(myList, 8);
    printf("Apunto de liberar %p, que actualmente contiene un %d\n", x, *((int *)x));
    free(x);

    for (int i = 0; i < 10; i++)
    {
        printf("%3d ", *((int *)list_get(myList, i)));
    }
    printf("\n");

    list_destroy(myList);
    
    return 0;
}

/*
Gestion de memeoria dinamica
hasta queue
*/
