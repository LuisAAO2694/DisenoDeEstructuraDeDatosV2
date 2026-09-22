#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int* sumar(int a1[], int a2[], int N){
    //int a3[N];
    int *a3 = malloc(N* sizeof(int));
    for (int i = 0; i < N; i++)
    {
        a3[i] = a1[i] + a2[i];
    }

    return a3;
}

typedef struct {
    float i;
    float j;
} Vec2D;

Vec2D* normalize(Vec2D* vectors, int N)
{
    //First creo el arreglo dinamico para los n vectores
    Vec2D* resultado = malloc(N * sizeof(Vec2D));
    
    //Aqui checo que la asignacion fue exitosa
    if (resultado == NULL) 
    {
        printf("no se pudo asignar memoria\n");
        return NULL;
    }
    
    //Recorro para cada vector y normalizarlo
    for (int k = 0; k < N; k++) 
    {
        //Me traigo la magnitud del vector
        float magnitud = sqrtf(vectors[k].i * vectors[k].i + vectors[k].j * vectors[k].j);
        resultado[k].i = vectors[k].i / magnitud;
        resultado[k].j = vectors[k].j / magnitud;
    }
    
    return resultado;
}

//------------------------------------------------------------------------------------------------------------
int** createMatrix(int R, int C) {
	//Crea una matriz de R por C en memoria dinámica.
	int** m = malloc(R * sizeof(int*));
    if (m == NULL) return NULL;

	for (int i = 0; i < R; i ++)
    {
        // *(m + i) es equivalente a m[i]
		*(m + i) = (int*)malloc(C * sizeof(int));
        if (*(m + i) == NULL) 
        {
            // Limpieza por si falla
            for (int k = 0; k < i; k++) 
            {
                free(*(m + k));
            }
            free(m);
            return NULL;
        }

        //Recorro las columnas usando el puntero dentro de la fila 
        int* fila = *(m+i); //btw puntero al inicio de la fija i
        for (int j = 0; j < C; j++) 
        {
        //*(fila + j) es equivalente a fila[j] que es m[i][j]
        *(fila + j) = rand() % 100;
        }
	}
	return m;
}

void printMatrix(int** m, int R, int C) 
{
	for (int i = 0; i < R; i++) 
    {
        //*(m + i) me da el puntero a la fila i
        int* fila = *(m + i);
        
        //Print de la direccion de la fila
        printf("%p [ ", (void*)fila);
        
        for (int j = 0; j < C; j++) 
        {
            //*(fila + j) accede al elemento j de mi fila
            printf("%2d ", *(fila + j));
        }
        printf("]\n");
    }
}

void freeMatrix(int** m, int R) 
{
    for (int i = 0; i < R; i++) 
    {
        //btw libero cada fila
        free(*(m + i));   
    }
    //libero el arreglo de punteros
    free(m);
}


int*** createCube(int x, int y, int z)
{
    //Reservo el arreglo de capas
    int*** cubo = (int***)malloc(x * sizeof(int**));

    //Bien aqui en este for, voy a por cada capa, reservo el arr de filas
    for (int i = 0; i < x; i++) 
    {
        *(cubo + i) = (int**)malloc(y * sizeof(int*));
        if (*(cubo + i) == NULL) 
        {
            //Libero las capas anteriores
            for (int k = 0; k < i; k++) {
                free(*(cubo + k));
            }
            free(cubo);
            return NULL;
        }

    for (int j = 0; j < y; j++) 
    {
            *(*(cubo + i) + j) = (int*)malloc(z * sizeof(int));

            if (*(*(cubo + i) + j) == NULL) 
            {
                //Libero las filas anteriores de esta capa
                for (int k = 0; k < j; k++) 
                {
                    free(*(*(cubo + i) + k));
                }

                //Liberar capas anteriores
                for (int k = 0; k < i; k++) 
                {
                    free(*(cubo + k));
                }
                free(cubo);
                return NULL;
            }

            //Lleno la fila con valores random
            int* fila = *(*(cubo + i) + j);
            for (int k = 0; k < z; k++) 
            {
                *(fila + k) = rand() % 100;
            }
        }
    }

    return cubo;
}

int main()
{
    int myIntArray1[] = {1,2,3,4,5};
    int myIntArray2[] = {1,2,3,4,5};
    int N = 5;

    //Llamar a la función
    int* resultado = sumar(myIntArray1, myIntArray2, N);
    
    // Imprimir el arreglo resultante
    printf("Arreglo resultado: ");
    for (int i = 0; i < N; i++) 
    {
        printf("\nresultado[%d] = %d", i, resultado[i]);
    }
    printf("\n");

    printf("------------------------\n");
    //Creo mi arreglo de vectores
    Vec2D vectores[] = {
        {3.0f, 4.0f},
        {1.0f, 0.0f},
        {0.0f, 2.0f},
        {0.0f, 0.0f},
        {1.0f, 1.0f}
    };

    //Aqui btw solo llamo a la funcion 
    Vec2D* normalizados = normalize(vectores, N);
    
    if (normalizados == NULL) {
        return 1;
    }
    
    //Aqui solo impirmo los resultados con el for
    for (int k = 0; k < 5; k++) 
    {
        printf("Vector %d:\n", k);
        printf("Original:     (%.3f, %.3f)\n", vectores[k].i, vectores[k].j);
        printf("Normalizado:  (%.3f, %.3f)\n", normalizados[k].i, normalizados[k].j);
        
        //Checo que la magnitud del normalizado sea 1 (excepto el vec nulo)
        float mag = sqrtf(normalizados[k].i * normalizados[k].i + normalizados[k].j * normalizados[k].j);
        printf("Magnitud:     %.3f\n\n", mag);
    }
//------------------------------------------------------------------------------------------------------------
    srand(time(NULL));
    
    int R = 10, C = 10;
    
    int** myMatrix = createMatrix(R, C);
    if (myMatrix == NULL) {
        printf("Error: no se pudo crear la matriz\n");
        return 1;
    }
    
    printf("=== Matriz %d x %d (con direcciones de fila) ===\n", R, C);
    printMatrix(myMatrix, R, C);
    
    // Liberar memoria
    freeMatrix(myMatrix, R);

    return 0;
}
