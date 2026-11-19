#include "Map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stringHash(Type e)
{
    char *key = (char *) e;
    int hash = 0;
    int i;
    
    for (i = 0; key[i] != '\0'; i++) 
    {
        // Restamos 'a' para que el número sea más pequeño (asume puras minúsculas)
        hash += (key[i] - 'a'); 
    }
    return hash;
}

int stringCompare(Type x, Type y)
{
    // strcmp devuelve 0 si son iguales. 
    // Para que funcione como Bool (1 = verdadero, 0 = falso) hacemos esto:
    if (strcmp((char*)x, (char*)y) == 0) {
        return 1; // Verdadero (son iguales)
    } else {
        return 0; // Falso (son diferentes)
    }
}

int main()
{
    Map myMap = map_create(10, stringHash, stringCompare);

    char* s1 = "lunes";
    char* s2 = "martes";
    char* s3 = "miercoles";
    char* s4 = "jueves";
    char* s5 = "viernes";
    char* s6 = "sabado";

    map_put(myMap, s1, "Monday");
    map_put(myMap, s2, "Tuesday");
    map_put(myMap, s3, "Wednesday");
    map_put(myMap, s4, "Thursday");
    map_put(myMap, s5, "Friday");
    map_put(myMap, s6, "Saturday");

    // 4. Probando el mapa
    printf("Tamanio del mapa: %d\n\n", map_size(myMap));

    // Buscando uno que SÍ existe
    printf("Buscando 'lunes': %s\n", (char*) map_get(myMap, s1));

    // Buscando uno que NO existe (para probar el NULL)
    printf("Buscando 'domingo': %s\n", (char*) map_get(myMap, "domingo"));

    // Probando map_contains
    if (map_contains(myMap, s4)) {
        printf("El mapa SI contiene 'jueves'.\n");
    }

    return 0;
}