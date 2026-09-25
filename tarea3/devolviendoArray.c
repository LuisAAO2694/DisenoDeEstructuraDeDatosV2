#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* toLower(char* string) 
{
    //Primero pues calculamos la longitud de la cadena original
    int len = 0;
    while (string[len] != '\0')
    {
        len++;
    }

    //Aqui reservo memoria, btw len caracteres + 1 para el \0
    char* res = (char*)malloc((len+1) * sizeof(char));

    if(res == NULL)
    {
        printf("No se pude reservar memoria ;/");
        return NULL;
    }

    //Copio conviertiendo a minusculas
    for(int m = 0; m<len; m++)
    {
        res[m] = tolower(string[m]);
    }

    //termino nulo
    res[len] = '\0';

    return res;
}

int main()
{
    char original[] = "HOLA Esto es delvOlvEr uN ARREGLO en MiNuScUlAs";
    
    char* min = toLower(original);
    
    if (min != NULL) 
    {
        printf("Original:  %s\n", original);
        printf("Minusculas: %s\n", min);
        
        //Aqui nomas libero la copia
        free(min);
    }

    return 0;
}