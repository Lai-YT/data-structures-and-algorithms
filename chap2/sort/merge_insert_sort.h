#ifndef MERGE_INSERT_SORT_H_
#define MERGE_INSERT_SORT_H_

#include <vector>

#include "merge_sort.h"

// best case: nlogn
// worst case: nlogn
// excersise p.40

void Merge(std::vector<int>& a, int head, int mid, int tail);

namespace misort {

  void InsertSort(std::vector<int>::iterator a, size_t n) {
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

void MergInsertSort(std::vector<int>& a, int head, int tail) {
  if (tail - head <= 15) {
    misort::InsertSort(a.begin() + head, tail - head);
    return;
  }
  int mid = (head + tail) / 2;
  MergInsertSort(a, head, mid);
  MergInsertSort(a, mid + 1, tail);
  Merge(a, head, mid, tail);
}

#endif /* end of include guard: MERGE_INSERT_SORT_H_ */
