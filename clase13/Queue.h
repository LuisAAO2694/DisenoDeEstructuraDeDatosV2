#ifndef QUEUE_H_
#define QUEUE_H_

typedef void *Type;

typedef struct strQueue *Queue;

typedef enum
{
    False,
    True
} Bool;

Queue queue_create();
int   queue_size(Queue q);
Bool  queue_isEmpty(Queue q);
Type  queue_peek(Queue q);
void  queue_offer(Queue q, Type d);
Type  queue_poll(Queue q);
void  queue_destroy(Queue q);

#endif