#include <stdlib.h>
#include <stdio.h>

/*
EJERCICIOS
1. Diseñe una funcion createMatrix que reciba dos argumentos de parte del usuarios:
(pueden verlo como filas y columnas) y reserve espacio en memeoria dinamica para una matriz
con esas dimensiones
*/
int** createMatrix(int x, int z)
{
    int** matrix = (int**) malloc(x * sizeof(int*));
    if (matrix == NULL) {
        printf("Error: no se pudo reservar filas.\n");
        return NULL;
    }

    for (int i = 0; i < x; i++) {
        matrix[i] = (int*) malloc(z * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Error en fila %d.\n", i);
            // (Idealmente liberar las anteriores aquí)
            return NULL;
        }
    }
    return matrix;
}

// Esta función ASUME que el arreglo de filas YA fue reservado por el llamador
void createMatrix2(int** m, int N, int z)
{
    for (int i = 0; i < N; i++) {
        m[i] = (int*) malloc(z * sizeof(int));
    }
}

/*
3. Diseñe una funcion free array3D que reciba como argumentos las dimensiones de un arreglo tridimensional
creado en memeoria dinamica, y el apuntador que representa a dicho arreglo
*/
void freeArray3D(void*** array3D, int X, int Y, int Z)
{
    //Liberar cada columna
    for (int i = 0; i < X; i++) 
    {
        for (int j = 0; j < Y; j++) 
        {
            free(array3D[i][j]);
            array3D[i][j] = NULL;
        }

        //Liberar cada fila (nivel intermedio)
        free(array3D[i]);
        array3D[i] = NULL;
    }

    //Liberar el arreglo de planos
    free(array3D);
    //array3D = NULL;
}

//Cuenta con las siguientes estructuras y alias
struct strNode{
    int data;
    struct strNode *prior;
};
typedef struct strNode* Node;

struct strStack{
    int size;
    Node top;
};
typedef struct strStack* Stack;

/*
4. Codifique la funcion stack_push. push es la operacion que inserta un nuevo elemento a la pila
*/
void stack_push(Stack stack, int data)
{
    //Checar si la pila existe
    if (stack == NULL) {
        return;
    }

    //Crear un nuevo nodo con mem
    Node n = (Node) malloc(sizeof(struct strNode));
    
    //Asignar el dato y el apuntador al nodo anterior
    n->data = data;
    n->prior = stack->top;   //El anterior del nuevo nodo es el tope

    //El nuevo nodo pasa a ser el tope de la pila
    stack->top = n;

    stack->size++;
}

//Cuenta con las siguientes estructuras y alias
typedef void* Type;
struct strQueueNode{
    Type data;
    struct strQueueNode* next;
};
typedef struct strQueueNode* QueueNode;

struct strQueue
{
    int size;
    QueueNode first, last;
};
typedef struct strQueue* Queue;

/*
5. Codifique la funcion queue_poll. Poll es la operacion que remeueve un elemento de la cola
y se lo devuelve al usuari. No olvide hacer gestion responsable de la memeoria.
*/
Type queue_poll(Queue queue)
{
    //Obtener el nodo al frente
    QueueNode nodeToPoll = queue->first;

    //Extraer el dato ANTES de liberar el nodo
    Type dataToReturn = nodeToPoll->data;

    //Avanzar el first al siguiente nodo
    queue->first = nodeToPoll->next;

    //Caso especial: si la cola quedó vacía, actualizar last?
    if (queue->first == NULL) 
    {
        queue->last = NULL;
    }
    free(nodeToPoll);

    queue->size--;

    //Devolver el dato extraído
    return dataToReturn;
}

Queue queue_create(){
    Queue q = malloc (sizeof(struct strQueue)); 
    q->first = NULL;
    q-> last = NULL; 
    q-›size = 0; return q; 99 1
} 

int main()
{
    //1
    int** myMatrix = createMatrix(10, 10);

    //reservamos el arreglo de filas antes de llamar a createMatrix2
    int** myMatrix2 = (int**) malloc(10 * sizeof(int*));
    createMatrix2(myMatrix2, 10, 10);

    // Llenamos ambas matrices para no imprimir basura
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            myMatrix[i][j]  = i * 10 + j;
            myMatrix2[i][j] = i * 10 + j;
        }
    }

    printf("--- myMatrix ---\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf("%3d ", myMatrix[i][j]);
        printf("\n");
    }

    printf("\n--- myMatrix2 ---\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++)
            printf("%3d ", myMatrix2[i][j]);
        printf("\n");
    }

    // ¡No olvides liberar!
    for (int i = 0; i < 10; i++) {
        free(myMatrix[i]);
        free(myMatrix2[i]);
    }
    free(myMatrix);
    free(myMatrix2);

    /*
    2. Tiene un arreglo de 20 enteros en memoria dinamica. Redimensionelo para que sea capaz
    de almacenar 30.
    */
    int* myIntArray = malloc(20 * sizeof(int));
    myIntArray = realloc(myIntArray, 30 * sizeof(int));


    //3
    printf("\n");
    int X = 2, Y = 3, Z = 4;

    //Creación
    int*** arr = (int***) malloc(X * sizeof(int**));
    for (int i = 0; i < X; i++) {
        arr[i] = (int**) malloc(Y * sizeof(int*));
        for (int j = 0; j < Y; j++) {
            arr[i][j] = (int*) malloc(Z * sizeof(int));
        }
    }

    //Llenado
    for (int i = 0; i < X; i++)
        for (int j = 0; j < Y; j++)
            for (int k = 0; k < Z; k++)
                arr[i][j][k] = i * 100 + j * 10 + k;

    //Planos
    for (int i = 0; i < X; i++)
    {
        printf("Plano %d:\n", i);
        for (int j = 0; j < Y; j++)
        {
            for (int k = 0; k < Z; k++)
            {
                printf("%4d ", arr[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    freeArray3D((void***) arr, X, Y, Z);
    arr = NULL;


    //4.




    return 0;
}