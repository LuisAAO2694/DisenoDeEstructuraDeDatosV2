#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

void imprimirCola(Queue q)
{
    printf("  size = %d | isEmpty = %s | peek = ",
        queue_size(q),
        queue_isEmpty(q) == True ? "True" : "False");

    if (queue_isEmpty(q) == True)
        printf("(cola vacia)\n");
    else
        printf("%d\n", *(int *)queue_peek(q));
}

int main()
{
    //Crear cola
    printf("1) Creando cola...\n");
    Queue q = queue_create();
    imprimirCola(q);
    printf("\n");

    //Offer con varios datos
    printf("2) Formando elementos \n");
    int datos[5] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
    {
        queue_offer(q, &datos[i]);
        printf("  offer(%d) -> ", datos[i]);
        imprimirCola(q);
    }
    printf("\n");
    return 0;
}