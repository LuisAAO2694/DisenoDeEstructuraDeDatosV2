#include <stdio.h>
#include <math.h> 

typedef int (*ComapreFunc) (void*, void*);

//Definimos la estructura Vec2D
typedef struct {
    float x;
    float y;
} Vec2D;

int compareFloat(void* x, void* y)
{
    if (*(float *)x < (*(float *)y)) //1er valor menor que el segundo
    {
        return -1;
    } 
    else if (*(float *)x > (*(float *)y)) //Si 1er valor es mayor que segundo
    {
        return 1;
    } 
    else //ps si son iguales
    {
        return 0;
    }
}

int comapreInt(void* a, void* b)
{
    //La resta de estos apuntadores nos da el resultado
    /*
        be like
        3 - 4 = -1 / 3 es menor que 4
        4 - 3 = 1 / 4 es mayor que 3
        3 - 3 = 0 / son iguales
    */

    return *((int*)a) - *(int*)b;
}

int comapreVec2D (void* x, void* y)
{
    //Primero deberia de hacer el cast de void* a Vec2D*
    Vec2D* v1 = (Vec2D*)x;
    Vec2D* v2 = (Vec2D*)y;


    //Ahora calculo la magnitud del vector, btw creo que es la ditancia desde el origen si no estoy mal*
    //magnitud = sqrt(x**2 + y**2)
    float mag1 = sqrt(v1->x * v1->x + v1->y * v1->y);
    float mag2 = sqrt(v2->x * v2->x + v2->y * v2->y);


    // Comparamos las magnitudes
    if (mag1 < mag2) 
    {
        return -1;
    } 
    else if (mag1 > mag2) 
    {
        return 1;
    } else {
        return 0;
    }
}


//Aqui creo mi funcion que hace un search a un arreglo de apuntadores void
/*
    obj es el arreglo de apuntadores void* for cada elemento
    key es mi apuntador void al valor que estoy buscando
    N el numero de elements en el arr
    compare apuntador a mi funcion de comaprefunc
*/
int indexOf(void* obj[], void* key, int N, ComapreFunc comapre)
{
    //Bien, para mi aproach recorro elemento por elemento
    for(int i=0; i<N; i++)
    {
        //A ver pues primero neceisto comparar el elemento actual con a clave usando la función compare
        //Entonces si compare devuelve 0, me dice que son los same/iguales pues
        if(comapre(obj[i], key) == 0)
        {
            return i; //Encuentro la clave en la pos i
        }
    }

    //But si acabo aqui terminaria el ciclo sin encontrar la clave no esta en el arreglo
    return -1;
}

int main()
{

    // Vec2D vec1 = {3.0, 4.0};    //5.0
    // Vec2D vec2 = {1.0, 1.0};    //1.414
    // Vec2D vec3 = {0.0, 5.0};    //5.0
    // Vec2D vec4 = {5.0, 0.0};    //5.0
    
    // printf("vec1 (3,4) vs vec2 (1,1): %d\n", comapreVec2D(&vec1, &vec2));
    
    // printf("vec2 (1,1) vs vec1 (3,4): %d\n", comapreVec2D(&vec2, &vec1));
    
    // printf("vec1 (3,4) vs vec3 (0,5): %d\n", comapreVec2D(&vec1, &vec3));
    
    // printf("vec3 (0,5) vs vec4 (5,0): %d\n", comapreVec2D(&vec3, &vec4));

    /*
    
    float myFloat1 = 3.14;
    float myFloat2 = 3.1416;
    float myFloat3 = 3.1416;

    float* myFloatPointer1 = &myFloat1;
    float* myFloatPointer2 = &myFloat2;
    float* myFloatPointer3 = &myFloat3;

    printf("%d\n", compareFloat(myFloatPointer3, myFloatPointer1));
    printf("%d\n", compareFloat(myFloatPointer2, myFloatPointer3));
    printf("%d\n", compareFloat(myFloatPointer3, myFloatPointer3));


    int myInt1 = 3.14;
    int myInt2 = 3.1416;
    int myInt3 = 3.1416;

    int* myIntPointer1 = &myInt1;
    int* myIntPointer2 = &myInt2;
    int* myIntPointer3 = &myInt3;

    printf("%d\n", comapreInt(myIntPointer1, myFloatPointer2));
    printf("%d\n", comapreInt(myIntPointer1, myFloatPointer3));;
    printf("%d\n", comapreInt(myIntPointer3, myFloatPointer3));

    */


    float myFloat1 = 3.14;
    float myFloat2 = 3.1416;
    float myFloat3 = 3.1416;

    void* myVoidPointer1 = &myFloat1;
    void* myVoidPointer2 = &myFloat2;
    void* myVoidPointer3 = &myFloat3;

    printf("%d\n", compareFloat(myVoidPointer3, myVoidPointer1));
    printf("%d\n", compareFloat(myVoidPointer2, myVoidPointer3));
    printf("%d\n", compareFloat(myVoidPointer1, myVoidPointer3));
    


    int myInt1 = 5;
    int myInt2 = 2;
    int myInt3 = 9;
    int myInt4 = 15;
    int myInt5 = 9;

    void* myVoidPointerArray[] = { &myInt1, &myInt2, &myInt3, &myInt4};

    void* myVoidPointer = &myInt5;

    //ComapreFunc comaprePointer = comapreInt;
    printf("%d\n", indexOf(myVoidPointerArray, myVoidPointer, 4, comapreInt));

    printf("--------------Vectores--------------");
    

    return 0;
}
