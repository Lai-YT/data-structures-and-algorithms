#include <iostream>
#include <vector>

#include "insert_sort.h"

// array at p.43
int main(int argc, char const *argv[]) {
  std::vector<int> a = {31, 41, 59, 26, 41, 58};
  insertSort(a);

  for (int n : a) {
    std::cout << n << ' ';
  }
  std::cout << '\n';

  return 0;
}
