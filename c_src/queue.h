#ifndef QUEUE_H
#define QUEUE_H

#include "ds.h"

/* Queue is implemented using a linked list */
typedef struct
{
    list_t *list;
} queue_t;

/* Create / destroy */
queue_t *queue_create(void);
void queue_destroy(queue_t *queue);

/* Queue operations */
void queue_enqueue(queue_t *queue, int value);
int queue_dequeue(queue_t *queue, int *out_value);
int queue_is_empty(const queue_t *queue);

#endif