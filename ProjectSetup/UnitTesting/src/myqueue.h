#ifndef MYQUEUE_H_
#define MYQUEUE_H_

#include <stdbool.h>
#include <limits.h>

#define QUEUE_EMPTY INT_MIN 

typedef struct myq queue;

queue*  q_create(int max_size);
void    q_destroy(queue *q);
bool    q_empty(queue* q);
bool    q_full(queue* q);
bool    q_enqueue(queue *q, int value);
int     q_dequeue(queue *q);

#endif //MYQUEUE_H_