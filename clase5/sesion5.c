#include <stdio.h>

void imprimirDoble(int x)
{
    printf("%d\n", x * 2);
}

void imprimirTriple(int x)
{
    printf("%d\n", x * 3);
}

int sumar(int a, int b)
{
    return a + b;
}

int restar(int a, int b)
{
    return a - b;
}

int main()
{
    void(*imprimirEntero) (int);
    imprimirEntero = imprimirDoble;

    imprimirDoble(2);
    imprimirEntero(2);

    imprimirEntero = imprimirTriple;
    imprimirEntero(2);
    //No se puede imprimirEntero = sumar;

    int (*operar)(int, int);

    //Va a apuntar a la funcion de sumar 
    operar = sumar;
    printf("Suma: %d\n", operar(2, 3));

    //Va a apuntar a la funcion de restar
    operar = restar;
    printf("Resta: %d\n", operar(2, 3));

    return 0;
}