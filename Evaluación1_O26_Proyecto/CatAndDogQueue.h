#ifndef CAT_AND_DOG_QUEUE_H
#define CAT_AND_DOG_QUEUE_H

//Pet es mi apuntador a la struct strPet
typedef struct strPet* Pet;

//CatAndDogQueue sera un apuntador a la estructura de la cola del refugio
typedef struct strCatAndDogQueue* CatAndDogQueue;
typedef enum { FALSE, TRUE } Bool;
typedef enum { CAT, DOG } Type;

//Devulve true so la mascota es un tipo dog
Bool pet_isDog(Pet p);

//Devuelve ture si la mascota que recibe es tipo cat
Bool pet_isCat(Pet p);

//Nos devuelve el id de la mascota
int pet_getId(Pet p);

//Creo una mascota en mem dinamica con su it y el tipo
Pet pet_create(int id, Type t);

//Nueva cola vacia para el refugio
CatAndDogQueue catAndDogQueue_create(void);

//Develve cuantas mascotas estan esperando en la cola
int catAndDogQueue_size(CatAndDogQueue q);

//Regresa true si no hay mascotas dentro de la cola
Bool catAndDogQueue_isEmpty(CatAndDogQueue q);

//Agrega una mascota al final de la fila del refugio
void catAndDogQueue_enqueue(CatAndDogQueue q, Pet p);

//Desencola btw saca a la mascota que llego primero, sin considear el tipo
Pet catAndDogQueue_dequeue(CatAndDogQueue q);

//Desencola el gato que lleve mas timepo
Pet catAndDogQueue_dequeueCat(CatAndDogQueue q);

//Desencila al perro que lleve mas tiempo
Pet catAndDogQueue_dequeueDog(CatAndDogQueue q);

#endif /* CAT_AND_DOG_QUEUE_H */
