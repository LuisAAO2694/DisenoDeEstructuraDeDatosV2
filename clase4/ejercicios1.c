#include <stdio.h>

//Definicion tipo bool
typedef enum { False, True } bool;


//Comparamos 2 cadenas de texto, caracter por caracter, con apuntadores
bool equals(char *s1, char *s2)
{

    //Aqui primero, se me ocurrio crear copias de los apuntadores de s1 y s2
    //btw only para poder impirmir las cadenas
    char *texto1 = s1;
    char *texto2 = s2;

    //Aqui use un while que se ejecuta mientras cumpla mis 2 condiciones 
    //El caracter s1 es \0?, los caracteres son iguales?
    while(*s1 && *s1 == *s2)
    {
        //Aqui itero caracter por caracter en cada una de las 2 cadenas
        s1++;
        s2++;
    }

    //Aqui ya solo comparo los caracteres actuales 
    bool res = (*s1 == *s2);

    //btw aqui solo imprimo los resultados
    printf("%s " "==" " %s" " | %s\n", texto1, texto2, res ? "True" : "False");

    return res;
}

int main() 
{
    char palabras1[][15] = { "Diseno", "Estructura", "Datos" };
    equals(palabras1[0], *(palabras1 + 1));

    equals("Hola", "hola");
    equals("Hola", "Hola");
}