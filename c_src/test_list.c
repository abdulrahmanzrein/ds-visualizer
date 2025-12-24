#include "ds.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
    printf("Creating list...\n");
    list_t *list = list_create();
    assert(list != NULL);

    printf("Pushing elements to front...\n");
    list_push_front(list, 10);
    list_push_front(list, 20);
    list_push_front(list, 30);

    assert(list_size(list) == 3);

    printf("Popping elements from front...\n");
    int value;
    while (list_pop_front(list, &value)) {
        printf("Popped: %d\n", value);
    }

    assert(list_size(list) == 0);

    printf("Testing pop on empty list...\n");
    assert(list_pop_front(list, &value) == 0);

    printf("Destroying list...\n");
    list_destroy(list);

    printf("All tests passed ✅\n");
    return 0;
}
