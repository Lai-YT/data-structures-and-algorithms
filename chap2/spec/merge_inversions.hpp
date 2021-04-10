#ifndef MERGE_INVERSIONS_HPP_
#define MERGE_INVERSIONS_HPP_

#include <vector>

// time complexity: nlgn

int MergeInversions(std::vector<int>& a, int head, int mid, int tail) {
  int n1 = mid - head + 1;
  int n2 = tail - mid;
  std::vector<int> left(a.begin() + head, a.begin() + mid + 1);
  std::vector<int> right(a.begin() + mid + 1, a.begin() + tail + 1);

  int i = 0, j = 0, k = 0;  // i for left, j for right, k for a
  int inversions = 0;
  bool counted = false;
  while (k <= tail && i <= n1 && j <= n2) {
    if (!counted && right[j] < left[i]) {
      // every remain element in left is a inversion-count
      inversions += n1 - i + 1;
      counted = true;
    }
    if (left[i] <= right[j]) {
      a[k] = left[i];
      i = i + 1;
    } else {
      a[k] = right[j];
      j = j + 1;
      counted = false;
    }
    k = k + 1;
  }
  while (j <= n2) {
    a[k] = right[j];
    j = j + 1;
    k = k + 1;
  }
  while (i <= n1) {
    a[k] = left[i];
    i = i + 1;
    k = k + 1;
  }

  return inversions;
}

int CountInversions(std::vector<int>& a, int head, int tail) {
  int inversions = 0;
  if (head < tail) {
    int mid = (head + tail) / 2;
    inversions += CountInversions(a, head, mid);
    inversions += CountInversions(a, mid + 1, tail);
    inversions += MergeInversions(a, head, mid, tail);
  }
  return inversions;
}

#endif /* end of include guard: MERGE_INVERSIONS_HPP_ */
