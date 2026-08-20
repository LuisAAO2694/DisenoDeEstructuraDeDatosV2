#include <stdlib.h>
#include <stdio.h>
#include <math.h> 

int length(char *s) {

    //Copia del apuntador para no modificar el original
    char *p = s; 
    int contador = 0; //Aqui solo uso un contador para los caracteres 
    
    //Mientras no llegue a un caracter nulo, solo recorro la cadena hasta que encuentre el nulo
    while (*p != '\0') 
    {
        contador++; //Cuento el caracter actual
        p++; //Avanzo al siguiente caracter
    }
    
    return contador;
}

void swap(int *a, int *b) {
    //Primero guardo el valor original de *a
    //guardo *a en aux (temp = 35)
    int aux = *a;

    //Aqui ya asigno el valor de *b a *a
    //escribe *b en *a (*a = 40)
    *a = *b;

    //escribo aux en *b (*b = 35)
    *b = aux; //Ya aqui asigno el valor original de *a a *b
}

typedef struct {
    float x;
    float y;
} Vec2;

void toUnit(Vec2 *v) {
    //calculamos la magnitud del vector
    float mag = sqrt(v->x * v->x + v->y * v->y);

    //Checo que el vector no sea cero / la final quiero evitar la division entre 0
    if(mag > 0.0)
    {
        //Divido cada componente entre su magnitud
        v->x /= mag;
        v->y /= mag;
    }
    //En caso de que mi mag sea 0, el vector se queda asi tal cual 
}

void imprimirVector(const char *nombre, Vec2 v) 
{
    printf("%s: {%.2f, %.2f}\n", nombre, v.x, v.y);
}


int main()
{
    printf("Ejercicio 1----------------------------------------------- \n");
    //Cadena literal
    char *texto1 = "hola mundo";
    printf("'%s' tiene %d caracteres\n", texto1, length(texto1));
    
    //Arreglo de caracteres, esto pues una pila literalmente, solo es para prueba 
    char texto2[] = "Hola, ¿cómo estás?";
    printf("'%s' tiene %d caracteres\n", texto2, length(texto2));
    
    //Cadena vacía
    char *texto3 = "";
    printf("'%s' tiene %d caracteres\n", texto3, length(texto3));

    printf("\n");
    printf("Ejercicio 2----------------------------------------------- \n");

    int a = 35, b = 40;
    printf("Caso 1 - Antes: a=%d, b=%d\n", a, b);
    swap(&a, &b);
    printf("Caso 1 - Después: a=%d, b=%d\n\n", a, b);

    printf("\n");
    printf("Ejercicio 3----------------------------------------------- \n");

    //Vector 3,4
    Vec2 v1 = {3.0, 4.0};
    imprimirVector("Original v1", v1);
    toUnit(&v1);
    imprimirVector("Unitario v1", v1);
    printf("\n");

    //Vector con magnitud ya 1
    Vec2 v2 = {1.0, 0.0};
    imprimirVector("Original v2", v2);
    toUnit(&v2);
    imprimirVector("Unitario v2", v2);
    printf("\n");

    Vec2 v3 = {0.0, 0.0};
    imprimirVector("Original v3", v3);
    toUnit(&v3);
    imprimirVector("Unitario v3", v3);
    printf("\n");

    //Vector con valores negativos
    Vec2 v4 = {-3.0, -4.0};
    imprimirVector("Original v4", v4);
    toUnit(&v4);
    imprimirVector("Unitario v4", v4);
    
    return 0;
}