/*
 * sesion6.c
 *
 *  Created on: 3 sept 2026
 *      Author: diego.gilbert
 */

#include <stdio.h>

typedef int (*CompareFunc) (void*, void*);

typedef struct {
	float x;
	float y;
}Vec2;

int compareFloat (void* x, void* y) {
	if (*(float*)x > *(float*)y) {
		return 1;
	} else if (*(float *)x < *(float *)y) {
		return -1;
	} else {
		return 0;
	}
}

int compareInt (void* x, void* y) {
	return *((int*)x) - *(int*)y;
}

int compareVec2(void* x, void* y) {
    Vec2* v1 = (Vec2*) x;
    Vec2* v2 = (Vec2*) y;
    
    // Magnitud al cuadrado: x² + y²
    float mag1_sq = v1->x * v1->x + v1->y * v1->y;
    float mag2_sq = v2->x * v2->x + v2->y * v2->y;
    
    if (mag1_sq < mag2_sq) return -1;
    else if (mag1_sq > mag2_sq) return 1;
    else return 0;
}


int indexOf(void* objects[], void* key, int N, CompareFunc compare) {
	for(int i = 0; i < N; i ++) {
		if (compare(objects[i], key) == 0) return i;
	}
	return -1;
}


//A ver entonces en esta funcion deberia de ordenar un arr de apuntadores void*
//de forma no decreciente, voy a usar selection sorttt
		//arr de apunt a orde.| num elements   | funcion de comp determian el orden en que se acomoda
void sort(void* objects[],      int N,           CompareFunc compare)
{
	//Aqui recorro cada pos del arr
	for(int a = 0; a<N - 1; a++)
	{
		//Aqui supongo que el element actual es el mas chiquito
		int minIndex = a;

		//Bieen aqui busco el element mas pequeño en lo que queda del arreglo
		for(int b = a+1; b<N; b++)
		{
			//Si llego a encontrar un elemento mas chiquito que el actual minimo
			//comapre me devolveria negativo si objects[b] < objects[minIndex] maybeeee
			if (compare(objects[b], objects[minIndex]) < 0) 
			{
				//Actualizo la posicion del min
                minIndex = b;
            }
		}

		//Ahora si encuentro un element mas pequeño que el actual, nomas le hago el swap
		if(minIndex != a)
		{
			//Hago el swap de los apuntadores de a y minIndex
			void* tempo = objects[a];
			objects[a] = objects[minIndex];
			objects[minIndex] = tempo;
		}
	}
}

// void printIntArray(void* objects[], int N) {
//     printf("[");
//     for (int i = 0; i < N; i++) {
//         printf("%d", *(int*)objects[i]);
//         if (i < N - 1) printf(", ");
//     }
//     printf("]\n");
// }

// void printFloatArray(void* objects[], int N) {
//     printf("[");
//     for (int i = 0; i < N; i++) {
//         printf("%.2f", *(float*)objects[i]);
//         if (i < N - 1) printf(", ");
//     }
//     printf("]\n");
// }

// void printVec2Array(void* objects[], int N) {
//     printf("[");
//     for (int i = 0; i < N; i++) {
//         Vec2* v = (Vec2*)objects[i];
//         printf("(%.1f,%.1f)", v->x, v->y);
//         if (i < N - 1) printf(", ");
//     }
//     printf("]\n");
// }

void printArray(void* objects[], int N, char type) 
{
    printf("[");
    for (int i = 0; i < N; i++) 
	{
        switch(type) 
		{
            case 'i':  // Entero
                printf("%d", *(int*)objects[i]);
                break;
            case 'f':  // Flotante
                printf("%.2f", *(float*)objects[i]);
                break;
            case 'v': { // Vec2
                Vec2* v = (Vec2*)objects[i];
                printf("(%.1f,%.1f)", v->x, v->y);
                break;
				}
        }
        if (i < N - 1) printf(", ");
    }
    printf("]\n");
}

int main() {

	/*
	float myFloat1 = 3.14;
	float myFloat2 = 3.1416;
	float myFloat3 = 3.1416;

	float* myFloatPointer1 = &myFloat1;
	float* myFloatPointer2 = &myFloat2;
	float* myFloatPointer3 = &myFloat3;

	printf("%d\n", compareFloat(myFloatPointer3, myFloatPointer1));
	printf("%d\n", compareFloat(myFloatPointer2, myFloatPointer3));
	printf("%d\n", compareFloat(myFloatPointer1, myFloatPointer3));

	int myInt1 = 7;
	int myInt2 = 2;
	int myInt3 = 7;

	int* myIntPointer1 = &myInt1;
	int* myIntPointer2 = &myInt2;
	int* myIntPointer3 = &myInt3;

	printf("%d\n", compareInt(myIntPointer1, myIntPointer2));
	printf("%d\n", compareInt(myIntPointer1, myIntPointer3));
	printf("%d\n", compareInt(myIntPointer2, myIntPointer1));
	*/
	float myFloat1 = 3.14;
	float myFloat2 = 3.1416;
	float myFloat3 = 3.1416;

	void* myVoidPointer1 = &myFloat1;
	void* myVoidPointer2 = &myFloat2;
	void* myVoidPointer3 = &myFloat3;

	printf("%d\n", compareFloat(myVoidPointer3, myVoidPointer1));
	printf("%d\n", compareFloat(myVoidPointer2, myVoidPointer3));
	printf("%d\n", compareFloat(myVoidPointer1, myVoidPointer3));

	int myInt1 = 5;
	int myInt2 = 2;
	int myInt3 = 9;
	int myInt4 = 15;
	int myInt5 = 9;

	void* myVoidPointerArray[] = { &myInt1, &myInt2, &myInt3,
								   &myInt4 };
	void* myVoidPointer = &myInt5;

	//CompareFunc comparePointer = compareInt;
	printf("%d\n", indexOf(myVoidPointerArray,
						   myVoidPointer, 4,
						   compareInt));


    printf("--- Ordenando enteros ---\n");
    
    //Definimos los datos
    int int1 = 5, int2 = 2, int3 = 9, int4 = 1, int5 = 7;
    
    //Creamos el arreglo de apuntadores void*
    void* intArray[] = { &int1, &int2, &int3, &int4, &int5 };
    int N = 5;
    
    printf("Arreglo original: ");
    printArray(intArray, N, 'i');
    
    //Ordenamos usando compareInt
    sort(intArray, N, compareInt);
    
    printf("Arreglo ordenado: ");
    printArray(intArray, N, 'i');
    printf("\n");

    printf("--- Ordenando flotantes ---\n");
    
    float f1 = 3.14, f2 = 2.71, f3 = 1.61, f4 = 4.20, f5 = 0.99;
    
    void* floatArray[] = { &f1, &f2, &f3, &f4, &f5 };
    N = 5;
    
    printf("Arreglo original: ");
    printArray(floatArray, N, 'f');
    
    sort(floatArray, N, compareFloat);
    
    printf("Arreglo ordenado: ");
    printArray(floatArray, N, 'f');
    printf("\n");

    printf("--- Ordenando vectores 2D por magnitud ---\n");
    
    Vec2 v1 = {3.0, 4.0};   // Magnitud: 5.0
    Vec2 v2 = {1.0, 1.0};   // Magnitud: 1.41
    Vec2 v3 = {0.0, 5.0};   // Magnitud: 5.0
    Vec2 v4 = {6.0, 8.0};   // Magnitud: 10.0
    Vec2 v5 = {2.0, 2.0};   // Magnitud: 2.83
    
    void* vecArray[] = { &v1, &v2, &v3, &v4, &v5 };
    N = 5;
    
    printf("Arreglo original: ");
    printArray(vecArray, N, 'v');
    printf("(Magnitudes: 5.0, 1.41, 5.0, 10.0, 2.83)\n");
    
    sort(vecArray, N, compareVec2);
    
    printf("Arreglo ordenado: ");
    printArray(vecArray, N, 'v');
    printf("(Ordenado por magnitud: 1.41, 2.83, 5.0, 5.0, 10.0)\n");
    printf("\n");

    printf("--- Ordenando con elementos repetidos ---\n");
    
    int r1 = 3, r2 = 1, r3 = 3, r4 = 2, r5 = 1, r6 = 3;
    
    void* repeatArray[] = { &r1, &r2, &r3, &r4, &r5, &r6 };
    N = 6;
    
    printf("Arreglo original: ");
    printArray(repeatArray, N, 'v');
    
    sort(repeatArray, N, compareInt);
    
    printf("Arreglo ordenado: ");
    printArray(repeatArray, N, 'v');
    printf("\n");

    printf("--- Usando indexOf después de ordenar ---\n");
    
    int a1 = 8, a2 = 3, a3 = 5, a4 = 2, a5 = 7;
    void* searchArray[] = { &a1, &a2, &a3, &a4, &a5 };
    N = 5;
    
    printf("Arreglo original: ");
    printArray(searchArray, N, 'i');
    
    //Ordenamos
    sort(searchArray, N, compareInt);
    printf("Arreglo ordenado: ");
    printArray(searchArray, N, 'i');
    
    //Buscamos un elemento después de ordenar
    int key = 5;
    int pos = indexOf(searchArray, &key, N, compareInt);
    printf("Buscando %d despues de ordenar: indice %d\n", key, pos);
    
    //Buscamos un elemento que no existe
    int keyNotExist = 99;
    pos = indexOf(searchArray, &keyNotExist, N, compareInt);
    printf("Buscando %d (no existe): indice %d\n", keyNotExist, pos);

	return 0;
}
