#include "hash_table.h"

#include <stddef.h>  // size_t
#include <stdlib.h>

#include "prime.h"

struct ht_item {
  int key;
  void* val;  // void* is used for generic
};

/// @note val may or may not be heap-allocated, its ownership isn't taken.
static ht_item_t* ht_new_item(int key, void* val) {
  ht_item_t* item = malloc(sizeof(ht_item_t));
  item->key = key;
  item->val = val;
  return item;
}

/// @note The val in the item is not freed.
static void ht_free_item(ht_item_t* item) {
  free(item);
}

static ht_hash_table_t* ht_new_hash_table_with_capacity(size_t capacity) {
  ht_hash_table_t* ht = malloc(sizeof(ht_hash_table_t));
  ht->capacity = capacity;
  ht->size = 0;
  // initialize to NULL, which means unused
  ht->items = calloc(ht->capacity, sizeof *ht->items);
  return ht;
}

ht_hash_table_t* ht_new_hash_table() {
  return ht_new_hash_table_with_capacity(next_prime(HT_BASE_CAPACITY));
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

/// @return An integer in [0, prime - 1].
/// @details Division hashing.
static int ht_hash1(int n, int prime) {
  return n % prime;
}

/// @return A integer in [1, prime].
/// @note Does not yield 0.
/// @details Division hashing.
static int ht_hash2(int n, int prime) {
  return prime - n % prime;
}

/// @brief A double hashing function that hashes the key into [0, ht_capacity).
/// @note Hashing is a large topic. This hash function is easy but may not be
/// good.
static int ht_get_hashed_key(int key, size_t ht_capacity, int attempt) {
  // the capacity we used is already a prime number
  int prime_1 = ht_capacity;
  // a smaller prime in comparison with prime_1
  // and should be relatively prime with the capacity
  int prime_2 = 7;
  return (ht_hash1(key, prime_1) + ht_hash2(key, prime_2) * attempt)
         % ht_capacity;
}

static ht_item_t* HT_DELETE_MARKER = NULL;

/// @return Whether the key of the item is "key".
/// @note Not null-safe.
static bool ht_has_key(ht_item_t* item, int key) {
  return item != HT_DELETE_MARKER && item->key == key;
}

/// @note An internal-use-only helper that returns the item for modification.
/// @return The pointer to the position of the item with key. If the key does
/// not exist, returns the position where the key will be if it is inserted.
static ht_item_t** ht_search_item(ht_hash_table_t* ht, int key) {
  int attempt = 0;
  int i;
  do {
    i = ht_get_hashed_key(key, ht->capacity, attempt++);
  } while (ht->items[i] && !ht_has_key(ht->items[i], key));
  return &ht->items[i];
}

/// @return An integer between 0 and 100.
static int ht_get_load_factor(ht_hash_table_t* ht) {
  // avoid floating-point arithmetic
  return ht->size * 100 / ht->capacity;
}

static bool ht_is_high_load(ht_hash_table_t* ht) {
  return ht_get_load_factor(ht) > 70;
}

static bool ht_is_low_load(ht_hash_table_t* ht) {
  return ht_get_load_factor(ht) < 10;
}

/// @note If the capacity is lower than HT_BASE_CAPACITY, HT_BASE_CAPACITY is
/// used; if the capacity is not a prime number, the closet larger prime number
/// is used.
static void ht_resize_hash_table(ht_hash_table_t* old, size_t capacity);

/// @details Double up the capacity if the table is under high load after the
/// insertion.
void ht_insert(ht_hash_table_t* ht, int key, void* val) {
  ht_item_t** item_p = ht_search_item(ht, key);
  if (*item_p) {
    ht_free_item(*item_p);
    ht->size--;
  }
  *item_p = ht_new_item(key, val);
  ht->size++;

  if (ht_is_high_load(ht)) {
    ht_resize_hash_table(ht, ht->capacity * 2);
  }
}

void* ht_search(ht_hash_table_t* ht, int key) {
  ht_item_t** item_p = ht_search_item(ht, key);
  return *item_p ? (*item_p)->val : NULL;
}

/// @details Half down the capacity if the table is under low load after the
/// deletion.
void ht_delete(ht_hash_table_t* ht, int key) {
  ht_item_t** item_p = ht_search_item(ht, key);
  if (*item_p) {
    ht_free_item(*item_p);
    *item_p = HT_DELETE_MARKER;
    ht->size--;

    if (ht_is_low_load(ht)) {
      ht_resize_hash_table(ht, ht->capacity / 2);
    }
  }
}

static void ht_resize_hash_table(ht_hash_table_t* old, size_t capacity) {
  if (capacity < HT_BASE_CAPACITY) {
    capacity = HT_BASE_CAPACITY;
  }
  if (!is_prime(capacity)) {
    capacity = next_prime(capacity);
  }

  // 1. Create a new hash table with the new capacity
  ht_hash_table_t* new = ht_new_hash_table_with_capacity(capacity);

  // 2. Insert the items of the old table into the new table
  for (size_t i = 0; i < old->capacity; i++) {
    ht_item_t* item = old->items[i];
    if (item && item != HT_DELETE_MARKER) {
      ht_insert(new, item->key, item->val);
    }
  }

  // 3. Point to the new table
  ht_hash_table_t ht_to_free = *old;
  *old = *new;

  // 4. Free the old table
  *new = ht_to_free;
  // free the items from old and the table itself from new
  ht_free_hash_table(new);
}
