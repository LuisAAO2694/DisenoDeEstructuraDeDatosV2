#include <stdlib.h>
#include <stdio.h>

int main() 
{
    //a)
    double r1 = -7.528;
    double *p1 = &r1;

    //b)
    printf("Valor que apunta p1: %.2f\n", *p1);
    printf("Dirección de p1: %p\n", (void*)&p1);
    printf("Dirección de r1: %p (deberia ser la misma que *p1)\n\n", (void*)&r1);

    //c)
    *p1 /= 2;
    printf("Dividir entre 2: %.2f\n\n", r1);

    //d)
    short a1[100] = {0};

    //e)
    short *p3 = &a1[2];   //indice 2 = tercer elemento
    *p3 = 8;

    printf("a1[2] = %d\n", a1[2]);
    printf("Direccion de a1[2]: %p\n", (void*)&a1[2]);
    printf("Valor de p3: %p\n", (void*)p3);
}