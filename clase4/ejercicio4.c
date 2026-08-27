#include <stdio.h>

#define R 3
#define C 3

//Encuentro el numero mas grande en una matriz 
//btw solo uso apuntadores y recorro la matriz
int max(int mat[][C])
{
    //Apuntador al primer elemento de mi matriz
    int *ap = &mat[0][0];

    //inicializo max con el primer valor
    int max = *ap;

    //Recorrere todos los R*C elementos
    for (int i = 0; i < R * C; i++) 
    {
        //Si el valor actual es mayor que max, lo actualizo
        if (*ap > max) 
        {
            max = *ap;
        }
        //Me voy al siguiente elemento
        ap++;
    }

    return max;
}

int main()
{
    int mat[R][C] = { {1, 2, 3}, {-1, -2, 0}, {2, 4, -3} };
    int m = max(mat);

    printf("El num mas grande es: %d\n", m);

    return 0;
}