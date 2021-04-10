#ifndef BRUTE_FORCE_INVERSIONS_HPP_
#define BRUTE_FORCE_INVERSIONS_HPP_

#include <vector>

// time complexity: n-squared

int BruteForceInversions(std::vector<int>& a) {
  int inversions = 0;
  for (size_t i = 0; i < a.size(); i++) {
    for (size_t j = i + 1; j < a.size(); j++) {
      if (a[i] > a[j]) {
        inversions += 1;
      }
    }
  }
  return inversions;
}

#endif /* end of include guard: BRUTE_FORCE_INVERSIONS_HPP_ */
