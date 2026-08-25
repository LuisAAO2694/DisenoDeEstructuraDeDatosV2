#include <stdio.h>

//Imprimo cada uno de los 15 caracteres de cada fila incluyendo los nulos
//btw imprime la basura.
void printAll(char strings [][15], int R) {

    for (int i = 0; i < R; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            //printf("%c", strings[i][j]);
            printf("%c", *(*(strings + i) + j));
        }    
        printf("\n");
    }
    
}

//Aqui utlizo %s para el formato del print
//imprime cada palabra completa, el %s deteine en automatico el caracter nulo
void printAll2(char strings [][15], int R) {
    //Recorro cada fila, i mean cada palabra
    for (int i = 0; i < R; i++) 
    {
        //printf("%s\n"), imprime la cadena completa
        //el strings apunta al primer caracter de la fila i
        //al final %s recorre la memoria hasta encontrar '\0'
        printf("%s\n", strings[i]);
    }
    printf("\n");
}

//Aqui igual imprimo caracter por caracter, peroo solo hasta que encuentro el nulo '\0'
void printAll3(char strings [][15], int R) {
    //Recorro cada fila, i mean cada palabra
    for (int i = 0; i < R; i++)
    {
        //Con este otro for recorro cada columna (al final termina siendo cada caracter)
        for (int j = 0; j < 15; j++)
        {
            //Obtengo el caracter con apuntadores
            //apunto a la primera fila avanzo a la siguiente, obtengo la fila con el primer *
            //despues avanzo en j dentro de la fila 
            //y con el ultimo apuntador obtengo el caracter en esa posicion 
            char c = *(*(strings + i) + j);

            //Si llega a ser \0 termino la palabra, btw ya no lo imprimo 
            if(c == '\0')
            {
                break;
            }

            //Si el caracter no es nulo, lo imprimo
            printf("%c", c);
        }
        printf("\n");
    }
}

printAllVersionProfe(char strings [][15], int R)
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < 15; j++)
        {

        }
    }

}

int main() {
    char palabras1[][15] = { "Diseno", "Estructura", "Datos" };
    printAll3(palabras1, 3);
}