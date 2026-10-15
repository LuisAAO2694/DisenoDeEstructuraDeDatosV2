#include "List.h"
#include <stdlib.h>
#include <stdio.h> // ← NUEVO: para los printf

struct strNode
{
    Type data;
    struct strNode *next, *prior;
};

typedef struct strNode *Node;

struct strList
{
    int size;
    Node first, last;
};

List list_create()
{
    // Reservar espacio para una estructura strList
    // Asignarle valores a sus propiedades
    // Devolver el apuntador tipo List al usuario

    printf("[CREATE] Creando nueva lista...\n");

    List l = malloc(sizeof(struct strList));
    if (l == NULL)
    {
        printf("[CREATE] ERROR: malloc fallo, no se pudo crear la lista.\n");
        return NULL;
    }

    l->size = 0;
    l->first = NULL;
    l->last = NULL;

    printf("[CREATE] Lista creada en %p (size=0, first=NULL, last=NULL)\n", (void *)l);

    return l;
}

void list_destroy(List l)
{
    // Elemento por elemento, liberar la memoria reservada para cada nodo
    // y, por último, liberar la memoria reservada para la estructura strList

    printf("[DESTROY] Iniciando destruccion de la lista...\n");

    if (l == NULL)
    {
        printf("[DESTROY] Lista es NULL, no hay nada que destruir.\n");
        return;
    }

    Node current = l->first;
    int contador = 0;
    while (current != NULL)
    {
        Node next = current->next;
        printf("[DESTROY]   Liberando nodo %d en %p (data=%p)\n",
               contador, (void *)current, current->data);
        free(current);
        current = next;
        contador++;
    }
    printf("[DESTROY] Se liberaron %d nodos.\n", contador);

    printf("[DESTROY] Liberando estructura strList en %p\n", (void *)l);
    free(l);
    printf("[DESTROY] Lista destruida completamente.\n");
}

int list_size(List l)
{
    // Devolver el tamaño de la lista

    if (l == NULL)
    {
        printf("[SIZE] Lista es NULL → devuelvo 0\n");
        return 0;
    }

    printf("[SIZE] Tamaño actual = %d\n", l->size);
    return l->size;
}

void list_add(List l, Type e)
{
    // Agregar un nuevo elemento al final de la lista
    // Si la lista está vacia:
    //   Actualizar first
    // Si la lista no está vacia:
    //   Actualizar la propiedad next del actual last
    // Actualizar last
    // Incrementar el tamaño de la lista

    printf("[ADD] Intentando agregar dato=%p\n", e);

    if (l == NULL)
    {
        printf("[ADD] ERROR: lista es NULL, no se puede agregar.\n");
        return;
    }

    // Crear el nuevo nodo
    Node n = (Node)malloc(sizeof(struct strNode));
    if (n == NULL)
    {
        printf("[ADD] ERROR: malloc fallo, no se pudo crear el nodo.\n");
        return;
    }

    // Guardo el dato que el pase
    n->data = e;

    // El nuevo nodo sera el ulitmo, por lo que no tiene sig
    // btw Su 'next' apunta a NULL.
    n->next = NULL;

    n->prior = l->last; // el anterior es el ultimo actual

    printf("[ADD] Nodo creado en %p (data=%p, prior=%p, next=NULL)\n",
           (void *)n, n->data, (void *)n->prior);

    // Conecto en la lista
    if (l->last == NULL)
    {
        // lista vacia
        printf("[ADD] Lista estaba vacia → nuevo nodo es first y last.\n");
        l->first = n;
    }
    else
    {
        // Ya habia elementos
        printf("[ADD] Lista NO vacia → enlazo last(%p)->next a nuevo(%p)\n",
               (void *)l->last, (void *)n);
        l->last->next = n;
    }
    // Actualizar last
    l->last = n;

    // Incremento el tamaño
    l->size++;

    printf("[ADD] Listo. size=%d, first=%p, last=%p\n",
           l->size, (void *)l->first, (void *)l->last);
}

Type list_get(List l, int i)
{
    printf("[GET] Buscando posicion i=%d\n", i);

    // Checo la lista nula o indice fuera de rango
    if (l == NULL || i < 0 || i >= l->size)
    {
        printf("[GET] indice inválido o lista NULL → devuelvo NULL\n");
        return NULL;
    }

    // Recorrer desde first hasta la posicion i
    Node current = l->first;
    for (int k = 0; k < i; k++)
    {
        printf("[GET]   Paso %d: current=%p → next=%p\n",
               k, (void *)current, (void *)current->next);
        current = current->next;
    }

    printf("[GET] Nodo encontrado en %p (data=%p)\n",
           (void *)current, current->data);

    // Devolver el dato (NO liberamos el nodo)
    return current->data;
}
//------------------------------------------------------------------------------

void list_set(List l, Type e, int i)
{
    printf("[SET] Reemplazando en i=%d por dato=%p\n", i, e);

    // Validar
    if (l == NULL || i < 0 || i >= l->size)
    {
        printf("[SET] indice inválido o lista NULL → no hago nada.\n");
        return;
    }

    // Localizar el nodo en la pos i
    Node current = l->first;
    for (int k = 0; k < i; k++)
    {
        current = current->next;
    }

    printf("[SET] Nodo en i=%d es %p. Dato viejo=%p, dato nuevo=%p\n",
           i, (void *)current, current->data, e);

    // Reemplazar el dato
    current->data = e;

    printf("[SET] Reemplazo hecho.\n");
}

Type list_remove(List l, int i)
{
    printf("[REMOVE] Intentando eliminar posicion i=%d\n", i);

    //Validar
    if (l == NULL || i < 0 || i >= l->size)
    {
        printf("[REMOVE] indice inválido o lista NULL → devuelvo NULL\n");
        return NULL;
    }

    //Busco el nodo a eliminar
    Node target = l->first;
    for (int k = 0; k < i; k++)
    {
        target = target->next;
    }

    printf("[REMOVE] Nodo a eliminar en %p (data=%p)\n",
           (void *)target, target->data);

    //Btw Guardar el dato a devolver
    Type toReturn = target->data;

    //bt reconoce segun se necesite
    if (l->size == 1)
    {
        //unique elemento
        printf("[REMOVE] Caso: único elemento en la lista.\n");
        l->first = NULL;
        l->last = NULL;
    }
    else if (target == l->first)
    {
        //Es el primero
        printf("[REMOVE] Caso: es el PRIMERO.\n");
        l->first = target->next;
        l->first->prior = NULL;
    }
    else if (target == l->last)
    {
        //Es el último
        printf("[REMOVE] Caso: es el ÚLTIMO.\n");
        l->last = target->prior;
        l->last->next = NULL;
    }
    else
    {
        //Esta en medio
        printf("[REMOVE] Caso: está en MEDIO.\n");
        target->prior->next = target->next;
        target->next->prior = target->prior;
    }

    //btw free nodo
    free(target);
    l->size--;

    printf("[REMOVE] Listo. size=%d, dato devuelto=%p\n", l->size, toReturn);

    return toReturn;
}

void list_insert(List l, Type e, int i)
{
    printf("[INSERT] Insertando dato=%p en posicion i=%d\n", e, i);

    // Checo: aqui i == size si es válido (insertar al final)
    if (l == NULL || i < 0 || i > l->size)
    {
        printf("[INSERT] indice inválido o lista NULL → no hago nada.\n");
        return;
    }

    // Crear el nuevo nodo
    Node n = malloc(sizeof(struct strNode));
    if (n == NULL)
    {
        printf("[INSERT] ERROR: malloc fallo.\n");
        return;
    }

    n->data = e;
    n->next = NULL;
    n->prior = NULL;

    printf("[INSERT] Nodo nuevo en %p\n", (void *)n);

    // List vacia
    if (l->size == 0)
    {
        printf("[INSERT] Caso: lista vacia.\n");
        l->first = n;
        l->last = n;
    }
    // insertar al inicio
    else if (i == 0)
    {
        printf("[INSERT] Caso: insertar al INICIO.\n");
        n->next = l->first;
        l->first->prior = n;
        l->first = n;
    }
    // insertar al final
    else if (i == l->size)
    {
        printf("[INSERT] Caso: insertar al FINAL.\n");
        n->prior = l->last;
        l->last->next = n;
        l->last = n;
    }
    // insertar en medio
    else
    {
        // Hallar el nodo que esta en i
        Node target = l->first;
        for (int k = 0; k < i; k++)
        {
            target = target->next;
        }

        printf("[INSERT] Caso: insertar en MEDIO. target=%p\n", (void *)target);

        // Conecto ya bien los 4 apuntadores
        n->prior = target->prior;
        n->next = target;
        target->prior->next = n;
        target->prior = n;
    }

    // incremento tamaño
    l->size++;

    printf("[INSERT] Listo. size=%d, first=%p, last=%p\n",
           l->size, (void *)l->first, (void *)l->last);
}