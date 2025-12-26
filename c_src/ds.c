#include "ds.h"
#include <stdlib.h> // malloc, free
#include <assert.h>

/* =========================
   List creation / destruction
   ========================= */

// creates an empty list
list_t *list_create(void)
{
    list_t *list = malloc(sizeof(list_t)); // allocates memory for the list

    if (list == NULL)
    {
        return NULL; // allocation failed → caller handles
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// deletes the whole list and frees the memory
void list_destroy(list_t *list)
{
    if (list == NULL)
    {
        return; // nothing to free
    }

    node_t *current = list->head;
    while (current != NULL)
    {
        node_t *tofree = current;
        current = current->next;
        free(tofree);
    }
    free(list);
}

/* =========================
   List operations
   ========================= */
void list_push_front(list_t *list, int value)
{
    assert(list != NULL);

    node_t *new_node = malloc(sizeof(node_t));
    assert(new_node != NULL); // ensure memory allocation succeeded

    new_node->value = value;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void list_push_back(list_t *list, int value)
{
    assert(list != NULL);

    node_t *new_node = malloc(sizeof(node_t));
    assert(new_node != NULL); // ensure memory allocation succeeded

    new_node->value = value;
    new_node->next = NULL;

    if (list->tail == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
}

int list_pop_front(list_t *list, int *out_value)
{
    assert(list != NULL);

    if (list->head == NULL)
    {
        return 0; // list is empty
    }

    node_t *tofree = list->head;

    if (out_value != NULL)
    {
        *out_value = tofree->value;
    }

    list->head = tofree->next;

    if (list->head == NULL)
    {
        list->tail = NULL;
    }

    free(tofree);
    list->size--;

    return 1; // success
}

/* =========================
   Accessors (for visualization)
   ========================= */

size_t list_size(const list_t *list)
{
    assert(list != NULL);
    return list->size;
}

node_t *list_head(const list_t *list)
{
    assert(list != NULL);
    return list->head;
}