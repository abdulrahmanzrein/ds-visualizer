#include "hashtable.h"
#include <stdlib.h>   // malloc, free
#include <assert.h>

/* =========================
   Hash helper
   ========================= */

/*
 * Convert an integer key into a bucket index.
 * For now this is just key % capacity — simple and predictable.
 */
static size_t hash_key(const hashtable_t *ht, int key)
{
    assert(ht != NULL);
    return (size_t)key % ht->capacity;
}

/* =========================
   Create / destroy
   ========================= */

hashtable_t *ht_create(size_t capacity)
{
    // A hash table with zero buckets doesn't make sense
    if (capacity == 0)
    {
        return NULL;
    }

    // Allocate the hash table struct
    hashtable_t *ht = malloc(sizeof(hashtable_t));
    if (ht == NULL)
    {
        return NULL;
    }

    ht->capacity = capacity;

    // Allocate the array of bucket pointers
    ht->buckets = malloc(sizeof(list_t *) * capacity);
    if (ht->buckets == NULL)
    {
        free(ht);
        return NULL;
    }

    // Create one linked list per bucket
    for (size_t i = 0; i < capacity; i++)
    {
        ht->buckets[i] = list_create();
        if (ht->buckets[i] == NULL)
        {
            // If anything fails, clean up everything created so far
            for (size_t j = 0; j < i; j++)
            {
                list_destroy(ht->buckets[j]);
            }
            free(ht->buckets);
            free(ht);
            return NULL;
        }
    }

    return ht;
}

void ht_destroy(hashtable_t *ht)
{
    if (ht == NULL)
    {
        return;
    }

    // Free all entries inside each bucket, then the bucket itself
    for (size_t i = 0; i < ht->capacity; i++)
    {
        list_t *bucket = ht->buckets[i];

        node_t *current = bucket->head;
        while (current != NULL)
        {
            ht_entry_t *entry = current->data;
            free(entry);          // free the entry, NOT the value
            current = current->next;
        }

        list_destroy(bucket);
    }

    free(ht->buckets);
    free(ht);
}

/* =========================
   Operations
   ========================= */

int ht_put(hashtable_t *ht, int key, void *value)
{
    assert(ht != NULL);

    size_t index = hash_key(ht, key);
    list_t *bucket = ht->buckets[index];

    // First, check if the key already exists
    for (node_t *cur = bucket->head; cur != NULL; cur = cur->next)
    {
        ht_entry_t *entry = cur->data;
        if (entry->key == key)
        {
            // Key found — just replace the value
            entry->value = value;
            return 0;
        }
    }

    // Key not found, so create a new entry
    ht_entry_t *new_entry = malloc(sizeof(ht_entry_t));
    if (new_entry == NULL)
    {
        return 0;
    }

    new_entry->key = key;
    new_entry->value = value;

    list_push_back(bucket, new_entry);
    return 1;
}

void *ht_get(const hashtable_t *ht, int key)
{
    assert(ht != NULL);

    size_t index = hash_key(ht, key);
    list_t *bucket = ht->buckets[index];

    // Search the bucket for the matching key
    for (node_t *cur = bucket->head; cur != NULL; cur = cur->next)
    {
        ht_entry_t *entry = cur->data;
        if (entry->key == key)
        {
            return entry->value;
        }
    }

    return NULL; // key not found
}

int ht_remove(hashtable_t *ht, int key)
{
    assert(ht != NULL);

    size_t index = hash_key(ht, key);
    list_t *bucket = ht->buckets[index];

    node_t *prev = NULL;
    node_t *cur = bucket->head;

    while (cur != NULL)
    {
        ht_entry_t *entry = cur->data;

        if (entry->key == key)
        {
            // Unlink the node from the list
            if (prev == NULL)
            {
                bucket->head = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }

            // Update tail if we removed the last node
            if (bucket->tail == cur)
            {
                bucket->tail = prev;
            }

            free(entry);     // free the entry, NOT the value
            free(cur);       // free the list node
            bucket->size--;

            return 1;
        }

        prev = cur;
        cur = cur->next;
    }

    return 0; // key not found
}
