#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

#ifndef HT_BASE_CAPACITY
#define HT_BASE_CAPACITY 53
#endif

typedef struct ht_item {
  int key;
  void* val;
} ht_item_t;

ht_item_t* ht_new_item(int key, void* val);

/// @note The val in the item is not freed.
void ht_free_item(ht_item_t* item);

typedef struct ht_hash_table {
  size_t capacity;
  size_t size;
  ht_item_t** items;
} ht_hash_table_t;

ht_hash_table_t* ht_new_hash_table();
void ht_free_hash_table(ht_hash_table_t*);

/// @brief Inserts the key-val pair into the hash table. val is updated if key
/// already exists.
/// @note The val may or may not be heap-allocated since the hash table does
/// not take the ownership. If val is heap allocated, the caller has to free it
/// manually.
void ht_insert(ht_hash_table_t* ht, int key, void* val);
void* ht_search(ht_hash_table_t*, int key);
void ht_delete(ht_hash_table_t*, int key);

int ht_hash1(int n, int prime);

/// @note Does not yield 0.
int ht_hash2(int n, int prime);
int ht_get_hashed_key(int key, size_t ht_capacity, int attempt);

void ht_resize_hash_table(ht_hash_table_t*, size_t capacity);

#endif /* end of include guard: HASH_TABLE_H */
