#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

#ifndef HT_BASE_CAPACITY
/// @brief Define before including this file if you want to use another base
/// capacity. The actual capacity will be the greater closest prime.
#define HT_BASE_CAPACITY 53
#endif

typedef struct ht_item ht_item_t;

typedef struct ht_hash_table {
  size_t capacity;
  size_t size;
  ht_item_t** items;
} ht_hash_table_t;

/// @note Should be freed after use with ht_free_hash_table.
ht_hash_table_t* ht_new_hash_table();

/// @note Frees the hash table created previously with ht_new_hash_table.
void ht_free_hash_table(ht_hash_table_t*);

/// @brief Inserts the key-val pair into the hash table. val is updated if key
/// already exists.
/// @note The val may or may not be heap-allocated since the hash table does
/// not take the ownership. If val is heap allocated, the caller has to free it
/// manually.
void ht_insert(ht_hash_table_t* ht, int key, void* val);

/// @return The val mapped by key; NULL if not exists.
void* ht_search(ht_hash_table_t*, int key);

/// @brief Deletes the key and its val from the table if the key exists.
/// @note The val is not freed since its ownership isn't taken.
void ht_delete(ht_hash_table_t*, int key);

#endif /* end of include guard: HASH_TABLE_H */
