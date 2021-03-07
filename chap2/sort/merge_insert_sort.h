#ifndef MERGE_INSERT_SORT_H_
#define MERGE_INSERT_SORT_H_

#include <vector>

#include "merge_sort.h"

// best case: nlogn
// worst case: nlogn
// excersise p.40

void Merge(std::vector<int>& a, int head, int mid, int tail);

namespace MISort {
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

} // end namespace misort

// head and tail are both included, so notice that the size is (tail - head + 1)
void MergInsertSort(std::vector<int>& a, int head, int tail) {
  if (tail - head <= 7) {
    MISort::PtrInsertSort(a.begin() + head, tail - head + 1);
    return;
  }
  int mid = (head + tail) / 2;
  MergInsertSort(a, head, mid);
  MergInsertSort(a, mid + 1, tail);
  Merge(a, head, mid, tail);
}

#endif /* end of include guard: MERGE_INSERT_SORT_H_ */
