#include <iostream>
#include <vector>

#include "sort/insert_sort.h"
#include "sort/select_sort.h"

// array at p.43
int main(int argc, char const *argv[]) {

  { // insertion sort test space
    std::vector<int> a = {31, 41, 59, 26, 41, 58};
    InsertSort(a);

    std::cout << "insertion sort: ";
    for (int n : a) {
      std::cout << n << ' ';
    }
    std::cout << '\n';
  } // end

  { // selection sort test space
   std::vector<int> a = {31, 41, 59, 26, 41, 58};
    SelectSort(a);

    std::cout << "selection sort: ";
    for (int n : a) {
      std::cout << n << ' ';
    }
    std::cout << '\n';
  } // end

  return 0;
}
