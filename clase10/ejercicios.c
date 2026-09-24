#include <stdio.h>
#include <stdlib.h>

void initString(char** target, char* source)
{
    //Checamos cantidad de recibidios
    int i=0;
    while(source[i] != '\0')
    {
        i++;
    }
    *target = malloc(i* sizeof(char));
    for(int j = 0; j<i; j++) {
        // *target[j] = source[j];
        (*target)[j] = source[j];
    }


}


int main()
{
    char s[30] = "Texto de prueba";
    char* t = NULL;
    initString(&t, s);
    printf("%s\n", t);

    int *myDynamicArray = malloc(10 * sizeof(int));
    realloc(myDynamicArray, 20 * sizeof(int));

    return 0;
}