#include <stdio.h>

void toLowerCase(char words [][10], int N) 
{
    //Recorro cada cadena (osea la fila)
    for(int a=0; a<N; a++)
    {
        //Mi apuntador al primer caracter la fila a / fila i
        char *palabra = *(words + a);


        //Aqui tratare de recorrer todos los caracteres hasta encontrar el \0 <- si se pudo!
        //*(palabra + j) es same as a palabra[j]
        for(int b=0; b<10 && *(palabra + b) != '\0'; b++)
        {
            //Me traigo el actual
            char c = *(palabra + b);

            //btw si es mayus, la convierto
            if(c >= 'A' && c<= 'Z')
            {
                *(palabra + b) = c + 32;
            }
        }
    }
}

int main() {
    char words[][10] = {"HOLA", "MUNDO", "Cruel5", "ADIÓS"};
    
    printf("Antes:\n");
    printf("Antes: %s\n", *(words));
    printf("Antes: %s\n", *(words + 1));
    printf("Antes: %s\n", *(words + 2));
    printf("Antes: %s\n", *(words + 3));
    printf("\n\n");
    
    toLowerCase(words, 3);
    
    printf("Despues: %s\n", *(words));
    printf("Despues: %s\n", *(words + 1));
    printf("Despues: %s\n", *(words + 2));
    printf("Despues: %s\n", *(words + 3));

    return 0;
}