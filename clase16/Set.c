#include "Set.h"
#include <stdlib.h>
#include <stdio.h>

struct strNode {
    Type data;
    struct strNode *left, *right;
};

typedef struct strNode* Node;

struct strSet {
    Node root;
    int size;
    CompareFunc compareFunc;
};

// Creamos el conjunto
Set set_create(CompareFunc cf) 
{
    Set s = malloc(sizeof(struct strSet));
    s->root = NULL;
    s->size = 0;
    s->compareFunc = cf;
    return s;
}

int set_size(Set s) 
{
    return s->size;
}

bool set_add(Set s, Type t) {
    //Creo un nuevo nodo, guardar el dato y asignar nulos a los hijos
    Node n = malloc(sizeof(struct strNode));
    n->data = t;
    n->left = NULL;
    n->right = NULL;

    //Si el conjunto está vacío (la raíz es nula), la raíz será el nuevo nodo
    if (s->root == NULL) 
    {
        s->root = n;
        s->size++;
        return true;
    }

    //Si no, recorrer el árbol desde la raíz hacia abajo
    Node current = s->root;
    
    while (current != NULL) 
    {
        //Ejecutar la función de comparación
        int cmp = s->compareFunc(t, current->data);

        if (cmp == 0) 
        {
            //btw si devuelve 0, encontramos el valor. No se añade
            free(n); //Eliminamos de memoria al nuevo nodo creado
            return false; 
        } 
        else if (cmp < 0) {
            //Si devuelve negativo, vamos por la izquierda
            if (current->left == NULL) {
                //Si el hijo izquierdo no existe, será el nuevo nodo
                current->left = n;
                s->size++; //Incrementamos tamaño
                return true;
            }
            //Si existe, continuamos la búsqueda por ahí
            current = current->left;
        } 
        else {
            //Si devuelve positivo, vamos por la derecha
            if (current->right == NULL) {
                //Si el hijo derecho no existe, será el nuevo nodo
                current->right = n;
                s->size++; //Incrementamos tamaño
                return true;
            }
            //Si existe, continuamos la búsqueda por ahí
            current = current->right;
        }
    }
    
    return false;
}

// Imprime un nodo y sus descendientes en orden (in-order)
static void printNode(Node n, void(*PrintFunction) (Type e))
{
    if (n == NULL)
        return;

    printNode(n->left, PrintFunction);       // izquierda
    PrintFunction(n->data);                  // nodo
    printNode(n->right, PrintFunction);      // derecha
}

void set_print(Set s, void(*PrintFunction) (Type e))
{
    if (s->size == 0)
    {
        return;
    }

    printNode(s->root, PrintFunction);
}

// Imprime un nodo y sus descendientes en pre-orden (nodo -> izquierda -> derecha)
static void printNodePre(Node n, void(*PrintFunction) (Type e))
{
    if (n == NULL)
        return;

    PrintFunction(n->data);                  // nodo
    printNodePre(n->left, PrintFunction);    // izquierda
    printNodePre(n->right, PrintFunction);   // derecha
}

void set_printPre(Set s, void(*PrintFunction) (Type e))
{
    if (s->size == 0)
    {
        return;
    }

    printNodePre(s->root, PrintFunction);
}
void freeNode(Node n)
{
    if(n->left !=NULL) freeNode(n->left);
    if(n->right !=NULL) freeNode(n->right);
    free(n);
}

void set_destroy(Set s)
{
    if(s->root !=NULL) freeNode(s->root);
    free(s);
}

bool set_remove(Set s, Type e)
{
    //Encontrar al elemento que pretendemos remover
    //Si no lo encontramos, devolver falso. Si lo encontramos:
    //Determinar la situación en la que se encuentra (sin hijos, con un hijo, o con dos hijos)
    //a) Sin hijos: Liberar la memoria correspondiente al nodo y actualizar la referencia
    //   del padre a nulo
    //b) Con un hijo: Conectar al padre con el hijo y liberar la memoria correspondiente al nodo
    //c) Con dos hijos: Encontrar al sucesor o al predecesor, sobreescribir con su dato al
    //   del nodo que se va a eliminar, y eliminar al sucesor o predecesor según la situación
    //   en la que se encuentre.
    //Disminuir el tamaño del conjunto
    //Si el elemento removido es la raíz, actualizar la propiedad correspondiente del conjunto
    //Devolver verdadero

    //L apunta a la referencia que apunta al nodo act
    //btw al inicio es  &s->root despues &padre->left
    Node *L = &s->root;

    //Aqui ponemos un while para buscar el elemento 
    while (*L != NULL)
    {
        int cmp = s->compareFunc(e, (*L)->data);
        //encontrado
        if (cmp == 0)
            break;

        //me voy por la izquierda
        if (cmp < 0)
        {
            L = &(*L)->left;          
        }
        else
        {
            //me voy por la derecha
            L = &(*L)->right; 
        }
    }

    //Si no lo ecuentro, devolvemos falso
    if (*L == NULL)
        return false;

    //nodo a eliminar
    Node target = *L;                    

    if (target->left == NULL)
    {
        //a) Sin hijo izquierdo (sin hijos o solo hijo derecho):
        //el padre debe apuntar al hijo derecho o a NULL
        *L = target->right;
        free(target);
    }
    else if (target->right == NULL)
    {
        //b) Solo hijo izquierdo: el padre apunta al hijo izquierdo
        *L = target->left;
        free(target);
    }
    else
    {
        //c) Dos hijos: usar el sucesor (el menor del subarbol derecho)
        Node *succLink = &target->right;
        while ((*succLink)->left != NULL)
        {
            succLink = &(*succLink)->left;
        }

        //Sucesor
        Node succ = *succLink; 

        //sobreescribir el dato
        target->data = succ->data;
        
        //el sucesor no tiene hijo izquierdo, puede tener derecho: lo conectamos
        *succLink = succ->right;

        //Libero el nodo del sucesor
        free(succ);
    }
    //Disminuir el tamaño del conjunto
    s->size--;

    //Entonces la raiz queda actualizada sola: si target era la raíz, L era &s->root, y ya se asignó *L = arriba segun yo
    return true;
}