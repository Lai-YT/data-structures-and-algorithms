#ifndef INSERT_SORT_HPP_
#define INSERT_SORT_HPP_

#include <vector>

// best case: n
// worst case: n-squared
// pseudocode at p.20, iterative at p.39

void InsertSort(std::vector<int>& a) {
  for (size_t j = 1; j < a.size(); ++j) {
    int key = a[j];
    int i = j - 1;
    while (i >= 0 && a[i] > key) {
      a[i + 1] = a[i];
      i = i - 1;
    }
    a[i + 1] = key;
  }
}

// subarray a[0, ..., j - 1] is sorted
void IterInsertSort(std::vector<int>& a, int j = 0) {
  if (j == a.size()) return;
  int key = a[j];
  int i = j - 1;
  while (i >= 0 && a[i] > key) {
    a[i + 1] = a[i];
    i = i - 1;
  }
  a[i + 1] = key;
  IterInsertSort(a, j + 1);
}

#endif /* end of include guard: INSERT_SORT_HPP_ */
