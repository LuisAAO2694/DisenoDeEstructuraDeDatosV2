#include "CatAndDogQueue.h"
#include <stdio.h>
#include <stdlib.h>

static void printDogAdoption(Pet p) {
    // Imprime el resultado de intentar adoptar al siguiente perro.
    if (p != NULL) {
        printf("Dog #%03d has been adopted. Woof!\n", pet_getId(p));
        free(p);
    } else {
        printf("All dogs have been adopted!\n");
    }
}

static void printCatAdoption(Pet p) {
    // Imprime el resultado de adoptar al siguiente gato.
    if (p != NULL) {
        printf("Cat #%03d has been adopted. Meow!\n", pet_getId(p));
        free(p);
    } else {
        printf("All cats have been adopted!\n");
    }
}

int main(void) {
    Pet myDogs[10];
    Pet myCats[10];
    Pet currentPet;
    CatAndDogQueue animalShelter;
    int i;

    // 1. Crea la única cola que representa al refugio.
    animalShelter = catAndDogQueue_create();
    if (animalShelter == NULL) {
        printf("No se pudo crear el refugio.\n");
        return 1;
    }

    // 2. Crea diez perros y diez gatos con identificadores del 1 al 10.
    for (i = 0; i < 10; i++) {
        myDogs[i] = pet_create(i + 1, DOG);
        myCats[i] = pet_create(i + 1, CAT);
    }

    // 3. Forma primero al perro 1, después a todos los gatos y al perro 2.
    catAndDogQueue_enqueue(animalShelter, myDogs[0]);
    for (i = 0; i < 10; i++) {
        catAndDogQueue_enqueue(animalShelter, myCats[i]);
    }
    catAndDogQueue_enqueue(animalShelter, myDogs[1]);

    // 4. Intenta adoptar tres perros: los dos primeros existen y el tercero no.
    for (i = 0; i < 3; i++) {
        currentPet = catAndDogQueue_dequeueDog(animalShelter);
        printDogAdoption(currentPet);
    }

    // 5. Adopta a los diez gatos respetando el orden FIFO entre gatos.
    for (i = 0; i < 10; i++) {
        currentPet = catAndDogQueue_dequeueCat(animalShelter);
        printCatAdoption(currentPet);
    }

    // 6. Libera los perros que se crearon para la prueba pero no se formaron.
    for (i = 2; i < 10; i++) {
        free(myDogs[i]);
    }

    // 7. La cola ya está vacía; sólo falta liberar su estructura principal.
    free(animalShelter);
    return 0;
}
