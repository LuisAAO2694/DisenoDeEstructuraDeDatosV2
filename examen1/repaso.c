#include <stdio.h>
#include <math.h>

/*
    2.
    Desarrolle una función incrementArray que reciba un arreglo de enteros y un entero N que indique su tamaño. 
    La función deberá incrementar en 1 el valor de cada elemento del arreglo. 
    No emplee notación de corchetes para resolver este problema (use aritmética de apuntadores para acceder a los elementos).
*/
void incrementArray(int *arr, int N)
{
    for(int a=0; a<N; a++)
    {
        *(arr+a) = *(arr+a) + 1;
    }
}

/*
    3.
    Dada la siguiente función,

        int add(int x, int y) {
            return x + y;
        }

    Cree un apuntador myFunctionPointer capaz de apuntar a una función como add y almacene en él la dirección de dicha función. 
    Declare una variable de tipo entero mySum y asígnele el resultado de una llamada a la función con los parámetros 5 y 7. 
    Llame a la función a través del apuntador myFunctionPointer, no directamente.
*/
int add(int x, int y) 
{
    return x + y;
}

/*
    4.
    Defina una estructura Vec2D que tenga dos atributos de tipo float: i y j. 
    Implemente una función printVec2D que reciba un apuntador a Vec2D e imprima el vector con el formato { i, j }. 
    Cree un vector myVector, asígnele valores y llame a la función printVec2D pasandloe el apuntador. 
*/
struct Vec2D 
{
    float i;
    float j;
};
void printVec2D(struct Vec2D *vec)
{
    printf("{%g, %g}\n", vec->i, vec->j);
};

/*
    5.
    Implemente una función powInPlace reciba dos argumentos: un apuntador a entero y un entero. 
    El apuntador referirá un entero que desee elevarse a una potencia, y el entero la potencia a la que se desea que sea elevado. 
    Declare un entero, asígnele un valor y llame a la función powInPlace para él, elevándolo a la potencia 5.
*/
void powInPlace(int *x, int potencia)
{
    int base = *x;
    int res = 1;

    for (int k = 0; k < potencia; k++) 
    {
        res *= base;
    }
    *x = res; //Aqui modifique el valor original a traves del apuntador
}


/*
    6.
    Declare cuatro variables de tipo Vec2D y cuatro variables de tipo flotante.
    Asigne valores a las variables de tipo Vec2D. Cree dos arreglos de apuntadores para almacenar las direcciones de las variables Vec2D y float. 
    Implemente una función que reciba un arreglo de apuntadores a Vec2D, un arreglo de apuntadores a float, y un entero N que indique el tamaño de los arreglos. 
    La función deberá calcular la magnitud de cada vector y almacenarlo en la posición correspondiente en el arreglo de flotantes.
*/
typedef struct {
    float i;
    float j;
} Vec2D;
void calcularMag(Vec2D **vectores, float **magnitudes, int N)
{
    for (int a = 0; a < N; a++) 
    {
        float i = vectores[a]->i;
        float j = vectores[a]->j;

        *magnitudes[a] = sqrtf(i * i + j * j);
    }
}


int main()
{
    /*
    1. 
    Apuntadores
    Declare tres flotantes (myFloat1, myFloat2, myFloat3) y 
    tres apuntadores a flotante (myFloatPointer1, myFloatPointer2, myFloatPointer3). 
    Guarde las direcciones de los flotantes en los apuntadores. 
    Asigne, a través de los apuntadores, los valores 2 y 3 a los primeros dos flotantes. Asigne, a través de los apuntadores, 
    el resultado de la suma de los primeros dos flotantes al tercero.
    */
    float myFloat1, myFloat2, myFloat3;
    float *myFloatPointer1, *myFloatPointer2, *myFloatPointer3;

    myFloatPointer1 = &myFloat1;
    myFloatPointer2 = &myFloat2;
    myFloatPointer3 = &myFloat3;

    *myFloatPointer1 = 2;
    *myFloatPointer2 = 3;

    *myFloatPointer3 = *myFloatPointer1 + *myFloatPointer2;

    printf("myFloat1 = %.2f\n", myFloat1);
    printf("myFloat2 = %.2f\n", myFloat2);
    printf("myFloat3 = %.2f\n", myFloat3);
    printf("\n");

    //2.
    int datos[] = {1, 2, 3, 4, 5};
    int N = sizeof(datos) / sizeof(datos[0]);

    printf("Antes:  ");
    for (int i = 0; i < N; i++) 
    {
        printf("%d ", *(datos + i));
    }
    printf("\n");

    incrementArray(datos, N);

    printf("Despues: ");
    for (int i = 0; i < N; i++) 
    {
        printf("%d ", *(datos + i));
    }
    printf("\n");

    //3.
    int (*myFunctionPointer)(int, int);

    myFunctionPointer = add;
    int mySum = myFunctionPointer(5, 7);
    printf("\n");
    printf("mySum = %d\n",mySum);
    printf("\n");

    //4.
    struct Vec2D myVector;
    myVector.i = 3.5;
    myVector.j = -2.0;
    printVec2D(&myVector);
    printf("\n");


    //5.
    int myNumber = 2;

    printf("Antes:  %d\n", myNumber);
    
    //paso la direccion -> pase por referencia
    powInPlace(&myNumber, 5);
    printf("Despues: %d\n", myNumber);
    printf("\n");

    //6.
    Vec2D v1, v2, v3, v4;

    float m1, m2, m3, m4;
    v1.i = 3.0f;  v1.j = 4.0f;
    v2.i = 1.0f;  v2.j = 0.0f;
    v3.i = 0.0f;  v3.j = 2.0f;
    v4.i = 6.0f;  v4.j = 8.0f;
    
    Vec2D *vectores[4] = { &v1, &v2, &v3, &v4 };
    float *magnitudes[4] = { &m1, &m2, &m3, &m4 };

    calcularMag(vectores, magnitudes, 4);
    for (int i = 0; i < 4; i++)
    {
        printf("Vec2D[%d] = {%g, %g} ||| magnitud = %g\n", i, vectores[i]->i, vectores[i]->j, *magnitudes[i]);
    }
    

    return 0;
}