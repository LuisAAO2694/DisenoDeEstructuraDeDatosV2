#include <stdio.h>

//Funcion que incrementa en 1 los valores apuntados por un arr de apuntadores
void addOne(int *arr[], int N)
{
    //First creo que recorro el arreglo en N elementos del arr
    for(int i = 0; i<N; i++)
    {
        //Bieeen si el apuntador en la posicion i no es null ps 
        if(arr[i] !=NULL)
        {
            //Incremento mi valor apuntado
            (*arr[i])++;
        }
    }
}


int main()
{
    int a = 7;
    int b = 8;
    int c = 9;

    //Creo el arreglo de 10 apuntadores a los enteros
    //Los primeros 3 apuntan a los de arriba
    int *arr[10] = {&a, &b, &c};

    printf("Sin mi addOne: \n");
    printf("a = %d, b = %d, c = %d\n", a,b,c);

    //Aqui easy
    //Llamo a mi funcion e incremento arr[0] = &a y se incrementa
    //Igual con arr[1] = &b, pero con los elemntos null, solo se ignoran
    addOne(arr, 5);


    //Muestro mis valores
    printf("Con mi addOne: \n");
    printf("a = %d, b = %d, c = %d\n", a,b,c);

    return 0;
}