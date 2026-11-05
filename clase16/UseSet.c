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

     printf("\n--- Probando set_remove ---\n");
    
    // Vamos a insertar valores manuales para tener un árbol controlado
    // Árbol esperado: 50, 30, 70, 20, 40, 60, 80
    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for(int i = 0; i < 7; i++) {
        int *v = malloc(sizeof(int));
        *v = vals[i];
        set_add(myIntSet, v);
    }
    
    printf("Árbol inicial: ");
    set_print(myIntSet, printInt);
    printf("\n");

    // Caso A: Eliminar una hoja (sin hijos)
    int buscar1 = 20;
    if (set_remove(myIntSet, &buscar1)) {
        printf("Se eliminó %d (hoja).\n", buscar1);
        // OJO: Aquí deberíamos liberar el entero 20 que estaba en el árbol,
        // pero como pasamos &buscar1 (memoria stack), no hacemos free().
        // En un caso real con malloc, sí harías free.
    }

    // Caso B: Eliminar un nodo con un hijo (el 30 ahora solo tiene al 40)
    int buscar2 = 30;
    if (set_remove(myIntSet, &buscar2)) {
        printf("Se eliminó %d (un hijo).\n", buscar2);
    }

    // Caso C: Eliminar un nodo con dos hijos (el 70 tiene al 60 y al 80)
    int buscar3 = 70;
    if (set_remove(myIntSet, &buscar3)) {
        printf("Se eliminó %d (dos hijos).\n", buscar3);
    }

    // Intentar eliminar algo que no existe
    int buscar4 = 999;
    if (!set_remove(myIntSet, &buscar4)) {
        printf("No se encontró %d, devolvió false correctamente.\n", buscar4);
    }

    printf("Árbol final:   ");
    set_print(myIntSet, printInt);
    printf("\n");
    printf("Tamaño final del conjunto: %d\n", set_size(myIntSet));

    //Crear dos conuntos difrenretes y luego un tercer conjunto que sea la interseccion de los 2 primeros
    //Sin consultarlos
    printf("-------------------------------\n");
    Set A = set_create(compareInt);
    Set B = set_create(compareInt);

    int datosA[] = {5, 2, 8, 1, 9, 4};
    int datosB[] = {3, 8, 2, 10, 1, 7};

    // Llenar A
    for (int i = 0; i < 6; i++)
    {
        int *x = malloc(sizeof(int));
        *x = datosA[i];
        if (!set_add(A, x))
            free(x);
    }

    // Llenar B
    for (int i = 0; i < 6; i++)
    {
        int *x = malloc(sizeof(int));
        *x = datosB[i];
        if (!set_add(B, x))
            free(x);
    }

    // Tercer conjunto = intersección
    Set C = set_intersection(A, B);

    printf("A:       ");
    set_print(A, printInt);
    printf("\nB:       ");
    set_print(B, printInt);
    printf("\nA ∩ B:   ");
    set_print(C, printInt);
    printf("\n");

    set_destroy(C);
    set_destroy(B);
    set_destroy(A);

    return 0;
}