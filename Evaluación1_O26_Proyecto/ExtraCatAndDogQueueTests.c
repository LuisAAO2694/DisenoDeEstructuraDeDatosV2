#include "CatAndDogQueue.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK(condition, message)               \
    do                                          \
    {                                           \
        if (!(condition))                       \
        {                                       \
            printf("    Error: %s\n", message); \
            return FALSE;                       \
        }                                       \
    } while (0)

typedef Bool (*TestFunction)(void);

static Bool expectAndFree(Pet currentPet, Pet expectedPet, const char *message)
{
    //Comprueba que se adoptó la mascota esperada y libera su memoria.
    if (currentPet != expectedPet)
    {
        printf("    Error: %s\n", message);
        return FALSE;
    }

    free(currentPet);
    return TRUE;
}

static Bool testEmptyQueue(void)
{
    //Comprueba el comportamiento de una cola recién creada y sin mascotas.
    CatAndDogQueue shelter = catAndDogQueue_create();

    CHECK(shelter != NULL, "No se pudo crear la cola.");
    CHECK(catAndDogQueue_size(shelter) == 0, "La cola vacía debe tener tamaño 0.");
    CHECK(catAndDogQueue_isEmpty(shelter) == TRUE, "La cola debe iniciar vacía.");
    CHECK(catAndDogQueue_dequeue(shelter) == NULL, "dequeue vacío debe devolver NULL.");
    CHECK(catAndDogQueue_dequeueCat(shelter) == NULL, "dequeueCat vacío debe devolver NULL.");
    CHECK(catAndDogQueue_dequeueDog(shelter) == NULL, "dequeueDog vacío debe devolver NULL.");

    free(shelter);
    return TRUE;
}

static Bool testGeneralFifo(void)
{
    //Comprueba que dequeue respete el orden de llegada entre ambos tipos.
    CatAndDogQueue shelter = catAndDogQueue_create();
    Pet cat1 = pet_create(101, CAT);
    Pet dog1 = pet_create(201, DOG);
    Pet cat2 = pet_create(102, CAT);
    Pet dog2 = pet_create(202, DOG);

    CHECK(shelter != NULL, "No se pudo crear la cola.");
    catAndDogQueue_enqueue(shelter, cat1);
    catAndDogQueue_enqueue(shelter, dog1);
    catAndDogQueue_enqueue(shelter, cat2);
    catAndDogQueue_enqueue(shelter, dog2);
    CHECK(catAndDogQueue_size(shelter) == 4, "El tamaño debe ser 4 después de encolar.");

    CHECK(expectAndFree(catAndDogQueue_dequeue(shelter), cat1,
                        "La primera mascota general debía ser el gato 101.") == TRUE,
          "Falló el primer dequeue general.");
    CHECK(expectAndFree(catAndDogQueue_dequeue(shelter), dog1,
                        "La segunda mascota general debía ser el perro 201.") == TRUE,
          "Falló el segundo dequeue general.");
    CHECK(expectAndFree(catAndDogQueue_dequeue(shelter), cat2,
                        "La tercera mascota general debía ser el gato 102.") == TRUE,
          "Falló el tercer dequeue general.");
    CHECK(expectAndFree(catAndDogQueue_dequeue(shelter), dog2,
                        "La cuarta mascota general debía ser el perro 202.") == TRUE,
          "Falló el cuarto dequeue general.");
    CHECK(catAndDogQueue_isEmpty(shelter) == TRUE, "La cola debería terminar vacía.");

    free(shelter);
    return TRUE;
}

static Bool testFifoByType(void)
{
    //Comprueba que cada especie conserve su propio orden FIFO.
    CatAndDogQueue shelter = catAndDogQueue_create();
    Pet dog1 = pet_create(1, DOG);
    Pet cat1 = pet_create(1, CAT);
    Pet dog2 = pet_create(2, DOG);
    Pet cat2 = pet_create(2, CAT);
    Pet dog3 = pet_create(3, DOG);

    CHECK(shelter != NULL, "No se pudo crear la cola.");
    catAndDogQueue_enqueue(shelter, dog1);
    catAndDogQueue_enqueue(shelter, cat1);
    catAndDogQueue_enqueue(shelter, dog2);
    catAndDogQueue_enqueue(shelter, cat2);
    catAndDogQueue_enqueue(shelter, dog3);

    CHECK(expectAndFree(catAndDogQueue_dequeueDog(shelter), dog1,
                        "El primer perro adoptado debía ser el perro 1.") == TRUE,
          "Falló el primer dequeueDog.");
    CHECK(expectAndFree(catAndDogQueue_dequeueDog(shelter), dog2,
                        "El segundo perro adoptado debía ser el perro 2.") == TRUE,
          "Falló el segundo dequeueDog.");
    CHECK(expectAndFree(catAndDogQueue_dequeueDog(shelter), dog3,
                        "El tercer perro adoptado debía ser el perro 3.") == TRUE,
          "Falló el tercer dequeueDog.");
    CHECK(expectAndFree(catAndDogQueue_dequeueCat(shelter), cat1,
                        "El primer gato adoptado debía ser el gato 1.") == TRUE,
          "Falló el primer dequeueCat.");
    CHECK(expectAndFree(catAndDogQueue_dequeueCat(shelter), cat2,
                        "El segundo gato adoptado debía ser el gato 2.") == TRUE,
          "Falló el segundo dequeueCat.");
    CHECK(catAndDogQueue_isEmpty(shelter) == TRUE, "La cola debería terminar vacía.");

    free(shelter);
    return TRUE;
}

static Bool testInterleavedAdoptions(void)
{
    //Comprueba que las tres formas de desencolar se puedan mezclar.
    CatAndDogQueue shelter = catAndDogQueue_create();
    Pet dog1 = pet_create(11, DOG);
    Pet cat1 = pet_create(12, CAT);
    Pet dog2 = pet_create(13, DOG);
    Pet cat2 = pet_create(14, CAT);
    Pet dog3 = pet_create(15, DOG);

    CHECK(shelter != NULL, "No se pudo crear la cola.");
    catAndDogQueue_enqueue(shelter, dog1);
    catAndDogQueue_enqueue(shelter, cat1);
    catAndDogQueue_enqueue(shelter, dog2);
    catAndDogQueue_enqueue(shelter, cat2);
    catAndDogQueue_enqueue(shelter, dog3);

    CHECK(expectAndFree(catAndDogQueue_dequeueCat(shelter), cat1,
                        "El primer gato debía poder salir desde en medio de la cola.") == TRUE,
          "Falló dequeueCat intercalado.");
    CHECK(expectAndFree(catAndDogQueue_dequeue(shelter), dog1,
                        "Después debía salir el primer perro de la fila general.") == TRUE,
          "Falló dequeue general intercalado.");
    CHECK(expectAndFree(catAndDogQueue_dequeueDog(shelter), dog2,
                        "El siguiente perro debía ser el perro 13.") == TRUE,
          "Falló dequeueDog intercalado.");
    CHECK(expectAndFree(catAndDogQueue_dequeue(shelter), cat2,
                        "Después debía salir el gato 14 en la fila general.") == TRUE,
          "Falló el segundo dequeue general intercalado.");
    CHECK(expectAndFree(catAndDogQueue_dequeueDog(shelter), dog3,
                        "El último perro debía ser el perro 15.") == TRUE,
          "Falló el último dequeueDog intercalado.");
    CHECK(catAndDogQueue_isEmpty(shelter) == TRUE, "La cola debería terminar vacía.");

    free(shelter);
    return TRUE;
}

static Bool testNoPetOfRequestedType(void)
{
    //Comprueba que pedir un perro cuando sólo hay gatos no cambie la cola.
    CatAndDogQueue shelter = catAndDogQueue_create();
    Pet cat1 = pet_create(31, CAT);
    Pet cat2 = pet_create(32, CAT);

    CHECK(shelter != NULL, "No se pudo crear la cola.");
    catAndDogQueue_enqueue(shelter, cat1);
    catAndDogQueue_enqueue(shelter, cat2);

    CHECK(catAndDogQueue_dequeueDog(shelter) == NULL,
          "No debía regresar un perro si sólo hay gatos.");
    CHECK(catAndDogQueue_size(shelter) == 2,
          "Pedir un tipo inexistente no debe cambiar el tamaño.");
    CHECK(expectAndFree(catAndDogQueue_dequeueCat(shelter), cat1,
                        "El primer gato debía mantenerse en la cola.") == TRUE,
          "Falló el primer gato después de pedir un perro inexistente.");
    CHECK(expectAndFree(catAndDogQueue_dequeueCat(shelter), cat2,
                        "El segundo gato debía mantenerse en la cola.") == TRUE,
          "Falló el segundo gato después de pedir un perro inexistente.");

    free(shelter);
    return TRUE;
}

static Bool testReenqueueAfterEmptyType(void)
{
    // Comprueba que un tipo se pueda volver a encolar después de agotarse.
    CatAndDogQueue shelter = catAndDogQueue_create();
    Pet cat1 = pet_create(41, CAT);
    Pet dog1 = pet_create(42, DOG);
    Pet cat2 = pet_create(43, CAT);
    Pet dog2 = pet_create(44, DOG);

    CHECK(shelter != NULL, "No se pudo crear la cola.");
    catAndDogQueue_enqueue(shelter, cat1);
    catAndDogQueue_enqueue(shelter, dog1);
    CHECK(expectAndFree(catAndDogQueue_dequeueCat(shelter), cat1,
                        "El gato 41 debía salir correctamente.") == TRUE,
          "Falló el primer gato.");
    CHECK(expectAndFree(catAndDogQueue_dequeueDog(shelter), dog1,
                        "El perro 42 debía salir correctamente.") == TRUE,
          "Falló el primer perro.");

    catAndDogQueue_enqueue(shelter, cat2);
    catAndDogQueue_enqueue(shelter, dog2);
    CHECK(expectAndFree(catAndDogQueue_dequeueDog(shelter), dog2,
                        "El perro 44 debía salir después de volver a encolar perros.") == TRUE,
          "Falló el perro reencontrado.");
    CHECK(expectAndFree(catAndDogQueue_dequeueCat(shelter), cat2,
                        "El gato 43 debía salir después de volver a encolar gatos.") == TRUE,
          "Falló el gato reencontrado.");
    CHECK(catAndDogQueue_isEmpty(shelter) == TRUE, "La cola debería terminar vacía.");

    free(shelter);
    return TRUE;
}

static Bool runTest(const char *name, TestFunction test)
{
    // Ejecuta una prueba y muestra un resultado fácil de leer.
    printf("Probando: %s\n", name);
    if (test() == TRUE)
    {
        printf("  PASS\n");
        return TRUE;
    }

    printf("  FAIL\n");
    return FALSE;
}

int main(void)
{
    int passed = 0;
    int total = 6;

    passed += runTest("cola vacia", testEmptyQueue);
    passed += runTest("FIFO general", testGeneralFifo);
    passed += runTest("FIFO por tipo", testFifoByType);
    passed += runTest("adopciones intercaladas", testInterleavedAdoptions);
    passed += runTest("tipo inexistente", testNoPetOfRequestedType);
    passed += runTest("reencolar despues de agotar un tipo", testReenqueueAfterEmptyType);

    printf("\nResultado final: %d de %d pruebas aprobadas.\n", passed, total);
    return passed == total ? 0 : 1;
}
