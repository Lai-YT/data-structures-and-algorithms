#ifndef MERGE_INVERSIONS_HPP_
#define MERGE_INVERSIONS_HPP_

/**
 * What Merge Sort does when merging is exactly moving the inversions,
 * so by performing a single merge sort and counting these moves,
 * we obtain the number of inversions.
 * This takes O(nlgn)
 */

#include <vector>


namespace inv {

std::vector<int> CopySubVector(
    const std::vector<int>& array, const size_t begin_index, const size_t end_index) {
  std::vector<int> copy(end_index - begin_index);
  for (size_t i = begin_index; i < end_index; ++i) {
    copy[i - begin_index] = array[i];
  }
  return copy;
}

int CountInversionsInMerge(
    std::vector<int>& array, const size_t head, const size_t mid, const size_t tail) {
  const std::vector<int> left = CopySubVector(array, head, mid);
  const std::vector<int> right = CopySubVector(array, mid, tail);

  int inversions = 0;
  int left_index = 0;
  int right_index = 0;
  int array_index = head;
  while (left_index != left.size() && right_index != right.size()) {
    if (left[left_index] > right[right_index]) {
      array[array_index++] = right[right_index++];
      // Left greater than right, inversion!
      // All remainings in left is a count.
      inversions += left.size() - left_index;
    } else {
      array[array_index++] = left[left_index++];
    }
  }

  while (left_index != left.size()) {
    array[array_index++] = left[left_index++];
  }
  while (right_index != right.size()) {
    array[array_index++] = right[right_index++];
  }
  return inversions;
}  // end Merge

/* NOTICE: Don't directly use this function to count inversions, which modifies the input array. */
int CountInversions(std::vector<int>& array, const size_t head, const size_t tail) {
  if (tail - head <= 1) {
    return 0;
  }
  int inversions = 0;
  const size_t mid = (head + tail) / 2;
  inversions += CountInversions(array, head, mid);
  inversions += CountInversions(array, mid, tail);
  inversions += CountInversionsInMerge(array, head, mid, tail);
  return inversions;
}

int CountInversions(const std::vector<int>& array) {
  std::vector<int> copy_to_avoid_modification{array};
  return CountInversions(copy_to_avoid_modification, 0, array.size());
}

}


#endif /* end of include guard: MERGE_INVERSIONS_HPP_ */
