#include <stdio.h>
#include <stdlib.h>


// int global1 = 5;
// int global2;

int** newMatrix(int R, int C)
{
    int **m = (int**) malloc(R * sizeof(int*));
    for(int i = 0; i<R; i++)
    {
        m[i] = malloc(C * sizeof(int));
    }
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            m[i][j] = rand();
            //*(*(m+i) + j) = rand();
        }
        
    }
    return m;
}

void printMatrix(int** m, int R, int C) 
{
    for(int a=0; a<R; a++)
    {
        printf("[ %p ]", m + a);
        printf("[ ");
        for(int b=0; b<C; b++)
        {
            printf("[%d][%d]=%6d  ", a, b, m[a][b]);
        }
        printf("]\n");
    }
}

int main()
{
    // static int static1 = 10;
    // static int static2;

    // short int myShort = 2;
    // short int *myShortPointer = &myShort;

    // short int *myDinamicArray = (short int*) malloc(20 * sizeof(short int));
    // short int myStaticArray[5];

    // printf("&global1: %p\n", &global1);
    // printf("&global2: %p\n", &global2);
    // printf("&static1: %p\n", &static1);
    // printf("&static2: %p\n", &static2);
    // printf("&myShort: %p\n", &myShort);
    // printf("&myShortPointer: %p\n", &myShortPointer);
    // printf("&myDinamicArray: %p\n", &myDinamicArray);
    // printf("&myDinamicArray0: %p\n", myDinamicArray); //dir primer elemento
    // printf("&myDinamicArray1: %p\n", myDinamicArray + 1); //dir segundo elemento
    // printf("&myDinamicArray2: %p\n", myDinamicArray[2]); //dir tercer elemento
    // printf("myStaticArray: %p\n", myStaticArray[2]);
    // printf("&myStaticArray: %p\n", &myStaticArray[2]);


    // int* pointer = NULL;

    // for (int i = 0; i < 10; i++) 
    // {
    //     //Resrvo espacio para 64 enteros
    //     pointer = (int*) calloc(64, sizeof(int));
    //     printf("%d\n", pointer[10]);
    //     if (pointer == NULL) {
    //         printf("Error: no se pudo reservar memoriaaaaa\n");
    //         return 1;
    //     }

    //     //Asigno 5000 a la posición 10
    //     pointer[10] = 5000;

    //     //Imprimo la direccion inicial
    //     printf("Iteración %2d -> ptr = %p\n", i + 1, (void*)pointer);
    //     free(pointer);
    //     printf("%d\n", pointer[10]);

    //     printf("----------------------------------------------");

    // }

    // free(pointer);
    // pointer = NULL;

    int R = 3, C = 4;
    int** m = newMatrix(R, C);
    
    printf("Matriz %dx%d:\n", R, C);
    printMatrix(m, R, C);

    return 0;

    return 0;
}


