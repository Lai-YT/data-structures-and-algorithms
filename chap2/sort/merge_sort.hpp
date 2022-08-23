#ifndef MERGE_SORT_HPP_
#define MERGE_SORT_HPP_

#include <vector>

// worst case: nlgn
// best case: nlgn
// pseudocode at p.31 and p.34, no sentinel at p.37
// CHANGE_LOG:
//  8/23/2022: (1) No more following the pseudocode, but still not using C++ specific syntax,
//             such as range copy.
//             (2) Use closed-open interval, as the convention.

std::vector<int> CopySubVector(
    const std::vector<int>& v, const size_t begin_index, const size_t end_index) {
  std::vector<int> copy(end_index - begin_index);
  for (size_t i = begin_index; i < end_index; ++i) {
    copy[i - begin_index] = v[i];
  }
  return copy;
}

void Merge(std::vector<int>& v, const size_t head, const size_t mid, const size_t tail) {
  const std::vector<int> left  = CopySubVector(v, head, mid);
  const std::vector<int> right = CopySubVector(v, mid, tail);

  int left_index  = 0;
  int right_index = 0;
  int v_index     = head;
  while (left_index != left.size() && right_index != right.size()) {
    // put the smaller one back
    if (left[left_index] <= right[right_index]) {
      v[v_index] = left[left_index];
      ++left_index;
    } else {
      v[v_index] = right[right_index];
      ++right_index;
    }
    ++v_index;
  }

  // put all remaining elements back
  while (left_index != left.size()) {
    v[v_index] = left[left_index];
    ++left_index;
    ++v_index;
  }
  while (right_index != right.size()) {
    v[v_index] = right[right_index];
    ++right_index;
    ++v_index;
  }
}  // end Merge

void MergeSort(std::vector<int>& v, const size_t head, const size_t tail) {
  if (tail - head <= 1) {
    return;
  }
  const size_t mid = (head + tail) / 2;
  MergeSort(v, head, mid);
  MergeSort(v, mid, tail);
  Merge(v, head, mid, tail);
}

#endif /* tail of include guard: MERGE_SORT_HPP_ */
