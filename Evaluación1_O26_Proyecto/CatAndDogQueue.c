#include "CatAndDogQueue.h"
#include <stdlib.h>

//Estructura de la info de la mascota
struct strPet 
{
    int id;
    Type type;
};

//Nuestro nodo dentro de la cola
struct strNode 
{
    //Pet apunta a la mascota que este alamcendad en el nodo
    Pet pet;
    struct strNode* next; //apunta a su siguiente segun la llegada
    struct strNode* previous; //apunta al nodo anterior en el orden de llegada
    // En si sirve para savar a un dog o cat que este en medio de la cola
    
    //Apunta al siguiente nodo que tenga el mismo tipo de mascota
    //No crea otra cola: btw solo conecta nodos que ya pertenecen a la misma cola general
    struct strNode* nextOfType;
};

typedef struct strNode* Node;

//Es nuestra estructura de datos del refugio
struct strCatAndDogQueue 
{
    //Primer y ultimo nodo de la fila general
    Node first, last;
    //Primer y ultimo gato dentro de la misma fila general
    Node firstCat, lastCat;

    //igual primer y ulitmo perro
    Node firstDog, lastDog;

    //Cant de mascotas que hay en el refugio
    int size;
};

//Creamos un nodo para almacenar una mascota
static Node node_create(Pet p) 
{
    //Reservo memoria para el nodo pd: agregamos el cast directo
    Node n = (Node) malloc(sizeof(struct strNode));

    if (n == NULL) 
    {
        return NULL;
    }

    //Guardamos el pet que recibimos
    n->pet = p;

    //El nodo todavio no esta conectado a otro nodo 
    n->next = NULL;
    n->previous = NULL;
    n->nextOfType = NULL;
    return n;
}

//En esta fnucioin desconectamos un nodo de la fila
static void catAndDogQueue_unlink(CatAndDogQueue q, Node n) 
{
    //Desconectamos un nodo de la cola general y mantiene first y last correctos
    if (n->previous == NULL) 
    {
        //Sig nodo es el first
        q->first = n->next;
    }else{
        //Nodo anterior deja de apuntar a n
        n->previous->next = n->next;
    }

    //Si no hay sig nodo, n era el ulitmo
    if (n->next == NULL) 
    {
        //El nodo anterior se convierte en el ulitmo
        q->last = n->previous;
    }else{
        //El sig nodo deja de apuntar hacia n
        n->next->previous = n->previous;
    }

    //Hay una mascota menos en el refugio
    q->size--;
}

//Funcion para eliminar un nodo y devuelve la mascota
static Pet catAndDogQueue_removeNode(CatAndDogQueue q, Node n) 
{
    //Actualiza la referencia del tipo correspondiente antes de retirar el nodo
    Pet toReturn = n->pet;

    //Si la mascota es eliminada era un cat
    if (pet_isCat(toReturn)) 
    {
        //Sig gato pasa a ser el primero, pero solo de los cat's
        q->firstCat = n->nextOfType;
        if (q->firstCat == NULL) //Si ya bo hay, limpio lastCat
        {
            q->lastCat = NULL;
        }
    }else{
        //Si era perro, el sig perro pasa a ser el firstdog
        q->firstDog = n->nextOfType;
        if (q->firstDog == NULL) //Si ya no hay perros, tambien se limpia el dog
        {
            q->lastDog = NULL;
        }
    }

    //Elimino el nodo de la fila general
    catAndDogQueue_unlink(q, n);

    //Le hago free
    free(n);
    return toReturn;
}

//Checamos si es un perro
Bool pet_isDog(Pet p) 
{
    //Primero checamos que p no se null
    //ya despues comparamos el tipo con dog
    return p != NULL && p->type == DOG;
}

//Checamos si un gato
Bool pet_isCat(Pet p) 
{
    //Primero checamos que p no se null
    //ya despues comparamos el tipo con cat
    return p != NULL && p->type == CAT;
}

//Obtenemos el id de una mascota
int pet_getId(Pet p) 
{
    //Si es null mandamos un -1
    //y ps si no deveulve el id de la mascota
    return p == NULL ? -1 : p->id;
}

//Creamos una mascota
Pet pet_create(int id, Type t) 
{
    //Reserva espacio para una mascota
    Pet pet = (Pet) malloc(sizeof(struct strPet));

    if (pet == NULL) 
    {
        return NULL;
    }

    //Guardamos el id recibido
    pet->id = id;
    //Guardamos si es gato o perro
    pet->type = t;

    return pet;
}

//Creamos una cola vacia para el refugio
CatAndDogQueue catAndDogQueue_create(void) 
{
    //Reservamos mem para la struct principal
    CatAndDogQueue q = (CatAndDogQueue) malloc(sizeof(struct strCatAndDogQueue));

    if (q == NULL) 
    {
        return NULL;
    }

    //Como la cola inicia vacia, no hay first ni last
    q->first = NULL;
    q->last = NULL;
    q->firstCat = NULL;
    q->lastCat = NULL;
    q->firstDog = NULL;
    q->lastDog = NULL;

    //Iniciamos en 0
    q->size = 0;
    return q;
}

//Devuelve la cantidad de mascotas en la cola
int catAndDogQueue_size(CatAndDogQueue q) 
{
    //Si la cola no exist, se considera tamaño 0
    return q == NULL ? 0 : q->size;
}

//Checa si la cola no tiene mascotas
Bool catAndDogQueue_isEmpty(CatAndDogQueue q) 
{
    //Si q es null o su tamañño es 0, esta vacia
    return q == NULL || q->size == 0;
}

//Agrega una mascota al final de la cola
void catAndDogQueue_enqueue(CatAndDogQueue q, Pet p) 
{
    //Nodo de nuestra mascota
    Node n;

    //No se puede encolar
    if (q == NULL || p == NULL) 
    {
        return;
    }

    //Creamos el nodo donde vive nuestra mascota
    n = node_create(p);
    if (n == NULL) 
    {
        return;
    }

    //El ant del new nodo sera el ulitmo act
    n->previous = q->last;
    //Si la cola estaba vacia, el nuevo nodo es el primero
    if (catAndDogQueue_isEmpty(q)) 
    {
        q->first = n;
    }else{
        //Si habia mas, el ulitmo ant apunta al new
        q->last->next = n;
    }
    q->last = n; //El new nodo se vuelve el ulitimo de la fila 

    //Si la mascota es gato
    if (pet_isCat(p)) 
    {
        //Si no habia gatos, este nodo es el primer gato
        if (q->lastCat == NULL) {
            q->firstCat = n;
        }else{
            //Si ya habia gatos, el ulitmo gato apunta a este nuevo gato
            q->lastCat->nextOfType = n;
        }
        //El nuevo gato se vuelve ultimo gato
        q->lastCat = n;

    }
    else
    {
        //Si no habia perros, este nodo es el primer perro
        if (q->lastDog == NULL) 
        {
            q->firstDog = n;
        }else{
            //Si ya habia perros, el ultimo perro apunta al new perro
            q->lastDog->nextOfType = n;
        }
        //El new perro se vuelve el ulitmo perro
        q->lastDog = n;
    }

    //Aumentamos el total de pets
    q->size++;
}

//Desencolamos a la mascota que llego primerp
Pet catAndDogQueue_dequeue(CatAndDogQueue q) 
{
    //Si no hay mascotas no hay nada que devolver
    if (catAndDogQueue_isEmpty(q)) 
    {
        return NULL;
    }
    //First nodo es la mascota que llego primero
    return catAndDogQueue_removeNode(q, q->first);
}

//Desencola al gato que llego primero entre los gatos
Pet catAndDogQueue_dequeueCat(CatAndDogQueue q) 
{
    //Si la cola esta vacia o no hay gatos, va directo a null
    if (catAndDogQueue_isEmpty(q) || q->firstCat == NULL) 
    {
        return NULL;
    }

    //Elimina directamente al primer gato, sin recorrer la cola
    return catAndDogQueue_removeNode(q, q->firstCat);
}

//Desencola al perro que llego primero entre todos los perros
Pet catAndDogQueue_dequeueDog(CatAndDogQueue q) 
{
    //Si la cola esta vacia o no hay perrosm devuelvo null
    if (catAndDogQueue_isEmpty(q) || q->firstDog == NULL) 
    {
        return NULL;
    }

    //Eliminamos directo al primer perr, sin recorrer la cola
    return catAndDogQueue_removeNode(q, q->firstDog);
}
