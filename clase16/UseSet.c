#include "Set.h"
#include <stdlib.h>
#include <stdio.h>

int compareInt(Type a, Type b)
{
    return *((int*) a) - *((int*)b);
}

void printInt(Type a)
{
    printf("%d ", *((int*) a));
}

int main()
{

    Set myIntSet = set_create(compareInt);

    for(int i = 0; i<20; i++)
    {
        int *x = malloc(sizeof(int));
        *x = rand() %100;
        if(!set_add(myIntSet, x))
        {
            printf("%d ya estaba en el conjunto\n", *x);
            free(x); // no se agregó, liberamos la memoria
        }
    }

    printf("\nIn-order:  ");
    set_print(myIntSet, printInt);
    printf("\n");

    printf("Pre-order: ");
    set_printPre(myIntSet, printInt);
    printf("\n");

    return 0;
}