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

using Index = int;

std::vector<int> CopySubVector(
    const std::vector<int>& v, const Index begin_index, const Index end_index) {
  std::vector<int> copy(end_index - begin_index);
  for (size_t i = begin_index; i < end_index; ++i) {
    copy[i - begin_index] = v[i];
  }
  return copy;
}

void Merge(std::vector<int>& v, const Index head, const Index mid, const Index tail) {
  const std::vector<int> left_portion  = CopySubVector(v, head, mid);
  const std::vector<int> right_portion = CopySubVector(v, mid, tail);

  Index left  = 0;
  Index right = 0;
  Index curr  = head;
  while (left != left_portion.size() && right != right_portion.size()) {
    // put the smaller one back
    if (left_portion[left] <= right_portion[right]) {
      v[curr] = left_portion[left];
      ++left;
    } else {
      v[curr] = right_portion[right];
      ++right;
    }
    ++curr;
  }

  // put all remaining elements back
  while (left != left_portion.size()) {
    v[curr] = left_portion[left];
    ++left;
    ++curr;
  }
  while (right != right_portion.size()) {
    v[curr] = right_portion[right];
    ++right;
    ++curr;
  }
}  // end Merge

void MergeSort(std::vector<int>& v, const Index head, const Index tail) {
  if (tail - head <= 1) {
    return;
  }
  const Index mid = (head + tail) / 2;
  MergeSort(v, head, mid);
  MergeSort(v, mid, tail);
  Merge(v, head, mid, tail);
}

#endif /* tail of include guard: MERGE_SORT_HPP_ */
