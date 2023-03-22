#include <stdio.h>

#include "hash_table.h"

// example

int main() {
  ht_hash_table_t* employees = ht_new_hash_table();

  ht_insert(employees, 1901, "Bob");
  ht_insert(employees, 2377, "David");

  printf("The employee with number 1901 is %s.\n",
         (char*)ht_search(employees, 1901));

  printf("Dismiss the employee with number 2377.\n");
  ht_delete(employees, 2377);
  printf("Now, there %s an employee with number 2377.\n",
         ht_search(employees, 2377) ? "is" : "isn't");

  ht_free_hash_table(employees);
  return 0;
}
