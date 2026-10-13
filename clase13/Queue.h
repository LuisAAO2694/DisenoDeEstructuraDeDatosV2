#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct strQueue* Queue;
typedef enum { False, True } Bool;
typedef void* Type;
typedef void (*printFunc) (void*);

Queue queue_create(printFunc); //Crea una nueva cola
int queue_size(Queue q); //Extrae el tamaño de la cola
Bool queue_isEmpty(Queue q); //¿El primero es nulo?
Type queue_peek (Queue q); //Consulta quién está al frente (no elimina)
void queue_offer(Queue q, Type d); //Se forma uno nuevo (colocarlo al final)
Type queue_poll(Queue q); //Atiende al que está al frente (elimina)
void queue_destroy(Queue q); //Elimina a todos los nodos y a la cola misma
void queue_print(Queue q);


#endif /* QUEUE_H_ */
