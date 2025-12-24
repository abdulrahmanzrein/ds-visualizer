#include "stack.h"
#include <stdlib.h>
#include <assert.h>

stack_t *stack_create(void)
{
    stack_t *stack = malloc(sizeof(stack_t));
    assert(stack != NULL);

    stack->list = list_create();
    assert(stack->list != NULL);

    return stack;
}

void stack_destroy(stack_t *stack)
{
    if (stack == NULL)
        return;

    list_destroy(stack->list);
    free(stack);
}

void stack_push(stack_t *stack, int value)
{
    assert(stack != NULL);
    list_push_front(stack->list, value);
}

int stack_pop(stack_t *stack, int *out_value)
{
    assert(stack != NULL);
    return list_pop_front(stack->list, out_value);
}

int stack_is_empty(const stack_t *stack)
{
    assert(stack != NULL);
    return list_size(stack->list) == 0;
}