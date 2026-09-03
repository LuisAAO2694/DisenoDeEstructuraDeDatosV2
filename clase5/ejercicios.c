#include <stdio.h>
#include <math.h>

typedef enum {False, True} Bool;
typedef float (*Function2D)(float);

Bool isLinear(Function2D f)
{
    float a = f(10000);
    float b = f(20000);
    
    if(b/a >= 1.99 && b/a <= 2.01)
    {
        return True;
    }
    else
    {
        return False;
    }
}

//Ejercicio3
Bool isQuadratic(Function2D f)
{
    float a = f(10000);
    float b = f(20000);

    if(b/a >= 3.98 && b/a <= 4.02)
    {
        return True;
    }
    else
    {
        return False;
    }
}


//Ejercicio 4
float F1(float x)
{
    return 4.0 * x - 2.0;
}

float F2(float x)
{
    return 3.0 * x * x - 2.0 * x + 4.0;
}

float F3(float x)
{
    return 6 * sqrt(x) + 2;
}


int main()
{
    //Crear un apuntardor a funcion de tipo function2d
    //Asignarle cualquiera de las funciones f1, f2, f3
    //Lamar a islinear o quadratic, pasandle como argumento
    //el apuntador a funion crado, para averiguar si la funcion es lienar o cuadratica
    //----------------------------------------------------------------------------------------------------
    // Function2D mifuncion;

    // mifuncion = F1;

    // if(isLinear(mifuncion))
    // {
    //     printf("its linear \n");
    // } else {
    //     printf("it isnt lienar \n");
    // }

    // if(isQuadratic(mifuncion))
    // {
    //     printf("its Quadratic \n");
    // } else {
    //     printf("it isnt Quadratic \n");
    // }

    //a) Crear un arreglo capaz de almacenar apuntadores a funciones y guardar las referencias a las 3 funciones
    Function2D misfunciones[3] = {F1, F2, F3};

    for (int i = 0; i < 3; i++)
    {
        if (isLinear(*(misfunciones[i])))
        {
            printf("its linear \n");
        }
        else
        {
            printf("it isnt lienar \n");
        }

        if (isQuadratic(*(misfunciones + i)))
        {
            printf("its Quadratic \n");
        }
        else
        {
            printf("it isnt Quadratic \n");
        }
    }

    //Sin usar alias
    float (*fp) (float);
    fp = F2;

    printf("f2 ");
    if(isLinear(fp))
    {
        printf("is ");
    } else {
        printf("isnt");
    }
    printf("linear \n");

    return 0;
}