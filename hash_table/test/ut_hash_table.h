#include <stddef.h>  // size_t

#include "../src/hash_table.h"
#include "assertion.h"

void test_insert_and_search() {
  ht_hash_table_t* ht = ht_new_hash_table();
  int keys[] = {9, 100, 217};
  char vals[] = {'a', 'Z', '-'};

  for (size_t i = 0; i < 3; i++) {
    ht_insert(ht, keys[i], vals + i);
  }

  for (size_t i = 0; i < 3; i++) {
    ASSERT_EQ(ht_search(ht, keys[i]), vals + i);
  }
  ASSERT_TRUE(!ht_search(ht, 10));
  ASSERT_TRUE(!ht_search(ht, 99));

  ht_free_hash_table(ht);
}

void test_delete() {
  ht_hash_table_t* ht = ht_new_hash_table();
  int keys[] = {9, 100, 217};
  char vals[] = {'a', 'Z', '-'};
  for (size_t i = 0; i < 3; i++) {
    ht_insert(ht, keys[i], vals + i);
  }

  ht_delete(ht, keys[1]);

  ASSERT_TRUE(ht_search(ht, keys[0]));
  ASSERT_TRUE(!ht_search(ht, keys[1]));
  ASSERT_TRUE(ht_search(ht, keys[2]));

  ht_free_hash_table(ht);
}

void test_update_with_insert() {
  ht_hash_table_t* ht = ht_new_hash_table();
  int key = 5;
  char* old_val = "old";
  char* new_val = "new";

  ht_insert(ht, key, old_val);
  ht_insert(ht, key, new_val);

  ASSERT_EQ(ht_search(ht, key), new_val);

  ht_free_hash_table(ht);
}

/// @brief Inserts enough many key-values and the capacity of the hash table
/// should grow.
void test_resize_double_up() {
  ht_hash_table_t* ht = ht_new_hash_table();
  int val = 0;  // a val that all keys correspond to
  const size_t base_capacity = ht->capacity;
  for (size_t i = 0; i < base_capacity; i++) {
    ht_insert(ht, i, &val);
  }

  ASSERT_TRUE(ht->capacity >= base_capacity * 2);

  ht_free_hash_table(ht);
}
