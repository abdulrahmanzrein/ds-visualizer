#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>   // for size_t
#include "ds.h"       // for list_t (used for chaining)

/* =========================
   Hash Table Structures
   ========================= */

/*
 * A single key/value pair stored in the table.
 * The hash table manages this struct itself,
 * but the value is owned by the caller.
 */
typedef struct
{
    int key;          // integer key
    void *value;      // pointer to the stored value
} ht_entry_t;

/*
 * Hash table implemented using separate chaining.
 * Each bucket is just a linked list of entries.
 */
typedef struct
{
    size_t capacity;   // how many buckets the table has
    list_t **buckets;  // array of linked lists (one per bucket)
} hashtable_t;

/* =========================
   Hash Table API
   ========================= */

// Create a hash table with a fixed number of buckets
hashtable_t *ht_create(size_t capacity);

// Free the table and all internal structures
void ht_destroy(hashtable_t *ht);

// Insert or update a key/value pair
int   ht_put(hashtable_t *ht, int key, void *value);

// Look up a value by key (returns NULL if not found)
void *ht_get(const hashtable_t *ht, int key);

// Remove a key/value pair (returns 1 if removed, 0 if not found)
int   ht_remove(hashtable_t *ht, int key);

#endif // HASHTABLE_H
