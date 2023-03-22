#include "hash_table.h"

#include <stddef.h>  // size_t
#include <stdlib.h>

#include "prime.h"

ht_item_t* ht_new_item(int key, void* val) {
  ht_item_t* item = malloc(sizeof(ht_item_t));
  item->key = key;
  item->val = val;
  return item;
}

void ht_free_item(ht_item_t* item) {
  free(item);
}

static ht_hash_table_t* ht_new_hash_table_with_capacity(size_t capacity) {
  ht_hash_table_t* ht = malloc(sizeof(ht_hash_table_t));
  ht->capacity = next_prime(capacity);
  ht->size = 0;
  ht->items = calloc(ht->capacity, sizeof *ht->items);
  return ht;
}

ht_hash_table_t* ht_new_hash_table() {
  return ht_new_hash_table_with_capacity(HT_BASE_CAPACITY);
}

void ht_free_hash_table(ht_hash_table_t* ht) {
  for (size_t i = 0; i < ht->capacity; i++) {
    if (ht->items[i]) {
      ht_free_item(ht->items[i]);
      ht->items[i] = NULL;
    }
  }
  free(ht->items);
  free(ht);
}

int ht_hash1(int n, int prime) {
  return n % prime;
}

int ht_hash2(int n, int prime) {
  return prime - n % prime;
}

int ht_get_hashed_key(int key, size_t ht_capacity, int attempt) {
  int prime_1 = ht_capacity;
  int prime_2 = 7;  // a smaller prime in comparison with prime_1
  return (ht_hash1(key, prime_1) + ht_hash2(key, prime_2) * attempt)
         % ht_capacity;
}

static ht_item_t* HT_DELETE_MARKER = NULL;

/// @note An internal-use-only helper that returns the item for modification.
/// @return The pointer to the position of the item with key. If the key does
/// not exist, returns the position where the key will be if it is inserted.
static ht_item_t** ht_search_item(ht_hash_table_t* ht, int key) {
  int attempt = 0;
  int i;
  do {
    i = ht_get_hashed_key(key, ht->capacity, attempt++);
  } while (ht->items[i]
           && (ht->items[i] == HT_DELETE_MARKER || ht->items[i]->key != key));
  return &ht->items[i];
}

void ht_insert(ht_hash_table_t* ht, int key, void* val) {
  ht_item_t** item_p = ht_search_item(ht, key);
  if (*item_p) {
    ht_free_item(*item_p);
    ht->size--;
  }
  *item_p = ht_new_item(key, val);
  ht->size++;
  const size_t load = ht->size * 100 / ht->capacity;
  if (load > 70) {
    ht_resize_hash_table(ht, ht->capacity * 2);
  }
}

void* ht_search(ht_hash_table_t* ht, int key) {
  ht_item_t** item_p = ht_search_item(ht, key);
  return *item_p ? (*item_p)->val : NULL;
}

void ht_delete(ht_hash_table_t* ht, int key) {
  ht_item_t** item_p = ht_search_item(ht, key);
  if (*item_p) {
    ht_free_item(*item_p);
    *item_p = HT_DELETE_MARKER;
    ht->size--;
  }
  const size_t load = ht->size * 100 / ht->capacity;
  if (load < 10) {
    ht_resize_hash_table(ht, ht->capacity / 2);
  }
}

void ht_resize_hash_table(ht_hash_table_t* old, size_t capacity) {
  if (capacity < HT_BASE_CAPACITY) {
    return;
  }
  // 1. Create a new hash table with the new capacity
  // 2. Insert the items of the old table into the new table
  // 3. Point to the new table
  // 4. Free the old items

  // 1.
  ht_hash_table_t* new = ht_new_hash_table_with_capacity(capacity);

  // 2.
  for (size_t i = 0; i < old->capacity; i++) {
    ht_item_t* item = old->items[i];
    if (item && item != HT_DELETE_MARKER) {
      ht_insert(new, item->key, item->val);
    }
  }

  // 3.
  ht_hash_table_t ht_to_free = *old;
  *old = *new;

  // 4.
  *new = ht_to_free;
  // free the items from old and the table itself from new
  ht_free_hash_table(new);
}
