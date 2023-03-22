#include <stdio.h>

#include "ut_hash_table.h"

int main() {
  test_insert_and_search();
  test_delete();
  test_update_with_insert();
  test_resize_double_up();

  puts("Tests end.");
  puts("--");
  return 0;
}
