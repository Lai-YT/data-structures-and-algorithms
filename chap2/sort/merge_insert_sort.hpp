#ifndef MERGE_INSERT_SORT_HPP_
#define MERGE_INSERT_SORT_HPP_

#include <vector>

#include "merge_sort.hpp"

// best case: nlogn
// worst case: nlogn
// excersise p.40

namespace misort {
  // an insertion sort that takes pointer is much more slower than a normol one,
  // which takes the whole vector
  void PtrInsertSort(std::vector<int>::iterator a, size_t n) {
    for (size_t j = 1; j < n; ++j) {
      int key = *(a + j);
      int i = j - 1;
      while (i >= 0 && *(a + i) > key) {
        *(a + i + 1) = *(a + i);
        i = i - 1;
      }
      *(a + i + 1) = key;
    }
  }

}  // end namespace misort

void MergInsertSort(std::vector<int>& a, int head, int tail) {
  if (tail - head <= 7) {
    misort::PtrInsertSort(a.begin() + head, tail - head);
    return;
  }
  int mid = (head + tail) / 2;
  MergInsertSort(a, head, mid);
  MergInsertSort(a, mid, tail);
  Merge(a, head, mid, tail);
}

#endif /* end of include guard: MERGE_INSERT_SORT_HPP_ */
