#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>

typedef struct ht_node {
    int key;
    int value;
    struct ht_node *next;
} ht_node_t;

typedef struct hashtable {
    ht_node_t **buckets;
    size_t capacity;
    size_t size;
} hashtable_t;

/* Creation / Destruction */
hashtable_t *hashtable_create(size_t capacity);
void hashtable_destroy(hashtable_t *ht);

/* Operations */
int hashtable_insert(hashtable_t *ht, int key, int value);
int hashtable_get(const hashtable_t *ht, int key, int *out_value);
int hashtable_remove(hashtable_t *ht, int key);

/* Utilities */
size_t hashtable_size(const hashtable_t *ht);

#endif