#include "queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(void)
{
    printf("Creating queue...\n");
    queue_t *queue = queue_create();
    assert(queue != NULL);
    assert(queue_is_empty(queue));

    printf("Enqueuing elements onto queue...\n");
    queue_enqueue(queue, 10);
    queue_enqueue(queue, 20);
    queue_enqueue(queue, 30);

    assert(!queue_is_empty(queue));

    printf("Dequeuing elements from queue...\n");
    int value;
    assert(queue_dequeue(queue, &value) && value == 10);
    assert(queue_dequeue(queue, &value) && value == 20);
    assert(queue_dequeue(queue, &value) && value == 30);

    assert(queue_is_empty(queue));

    printf("Testing dequeue on empty queue...\n");
    assert(queue_dequeue(queue, &value) == 0);

    printf("Destroying queue...\n");
    queue_destroy(queue);

    printf("All tests passed ✅\n");
    return 0;
}