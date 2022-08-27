#include <iostream>
#include <vector>

#include "sort/insert_sort.hpp"
#include "sort/merge_insert_sort.hpp"
#include "sort/merge_sort.hpp"
#include "sort/select_sort.hpp"


void PrintArray(const std::vector<int>& array);

// array at p.22
int main(int argc, char const *argv[]) {

  const std::vector<int> ARRAY = {31, 41, 59, 26, 41, 58};

  { // insertion sort test space

    std::vector<int> a = ARRAY;
    InsertSort(a);
    std::cout << "insertion sort (iterative): ";
    PrintArray(a);

    std::vector<int> b = ARRAY;
    RecurInsertSort(b);
    std::cout << "insertion sort (recursive): ";
    PrintArray(b);

  } // end

  { // selection sort test space

    std::vector<int> a = ARRAY;
    SelectSort(a);
    std::cout << "selection sort: ";
    PrintArray(a);

  } // end

  { // merge sort test space

    std::vector<int> a = ARRAY;
    MergeSort(a, 0, a.size());
    std::cout << "merge sort: ";
    PrintArray(a);

  } // end

  { // merge-insertion sort test space

    std::vector<int> a = ARRAY;
    MergInsertSort(a, 0, a.size());
    std::cout << "merge-insertion sort: ";
    PrintArray(a);

  } // end

  return 0;
}


void PrintArray(const std::vector<int>& array) {
  for (const int n : array) {
    std::cout << n << ' ';
  }
  std::cout << '\n';
}
