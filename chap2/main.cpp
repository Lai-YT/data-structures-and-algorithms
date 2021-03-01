#include <iostream>
#include <vector>

#include "sort/insert_sort.h"
#include "sort/merge_sort.h"
#include "sort/select_sort.h"

// array at p.22
int main(int argc, char const *argv[]) {

  { // insertion sort test space
    std::vector<int> a = {31, 41, 59, 26, 41, 58};
    InsertSort(a);

    std::cout << "insertion sort: ";
    for (int n : a) {
      std::cout << n << ' ';
    }
    std::cout << '\n';

    std::vector<int> b = {31, 41, 59, 26, 41, 58};
    IterInsertSort(b);

    std::cout << "insertion sort (iterative): ";
    for (int n : b) {
      std::cout << n << ' ';
    }
    std::cout << '\n';

  } // end

  { // selection sort test space

    // ---- case 1 ----

    std::vector<int> a = {31, 41, 59, 26, 41, 58};
    SelectSort(a);

    std::cout << "selection sort: ";
    for (int n : a) {
      std::cout << n << ' ';
    }
    std::cout << '\n';

    // ---- case 2 ----

    std::vector<int> b = {6, 5, 4, 3, 2, 1, 0};
    SelectSort(b);

    std::cout << "selection sort: ";
    for (int n : b) {
      std::cout << n << ' ';
    }
    std::cout << '\n';
  } // end

  { // merge sort test space

    // ---- case 1 ----

    std::vector<int> a = {31, 41, 59, 26, 41, 58};
    MergeSort(a, 0, a.size());

    std::cout << "merge sort: ";
    for (int n : a) {
      std::cout << n << ' ';
    }
    std::cout << '\n';

    // ---- case 2 ----

    std::vector<int> b = {6, 5, 4, 3, 2, 1, 0};
    MergeSort(b, 0, b.size() - 1);

    std::cout << "merge sort: ";
    for (int n : b) {
      std::cout << n << ' ';
    }
    std::cout << '\n';
  } // end

  return 0;
}
