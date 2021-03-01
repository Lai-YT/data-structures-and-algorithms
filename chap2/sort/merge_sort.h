#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include <vector>

// worst case: nlgn
// best case: nlgn
// pseudocode at p.31 and p.34, no sentinel at p.37

namespace {

  void Merge(std::vector<int>& a, int head, int mid, int tail) {
    int n1 = mid - head + 1, n2 = tail - mid;
    std::vector<int> left(n1), right(n2);
    for (size_t i = 0; i < n1; ++i) {
      left[i] = a[i + head];
    }
    for (size_t i = 0; i < n2; ++i) {
      right[i] = a[i + mid + 1];
    }

    int i = 0, j = 0, k = head;
    while (i != n1 && j != n2) {
      if (left[i] <= right[j]) {
        a[k] = left[i];
        i = i + 1;
      } else {
        a[k] = right[j];
        j = j + 1;
      }
      k = k + 1;
    }

    // no sentinel
    while (i != n1) {
      a[k] = left[i];
      i = i + 1;
      k = k + 1;
    }
    while (j != n2) {
      a[k] = right[j];
      j = j + 1;
      k = k + 1;
    }
  } // end Merge

} // namespace


// head and tail are both included
void MergeSort(std::vector<int>& a, int head, int tail) {
  if (head >= tail) return;
  int mid = (head + tail) / 2;
  MergeSort(a, head, mid);
  MergeSort(a, mid + 1, tail);
  Merge(a, head, mid, tail);
}

#endif /* tail of include guard: MERGE_SORT_H_ */
