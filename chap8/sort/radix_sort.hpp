#ifndef RADIX_SORT_HPP_
#define RADIX_SORT_HPP_

#include <algorithm>
#include <string>
#include <vector>

// at p.198
// self-implementation

void RadixSort(std::vector<std::string>& a, int digit) {
  // notice that the most right bit of string has the biggest index,
  // so count backward
  for (int i = digit - 1; i >= 0; --i) {
    std::stable_sort(a.begin(), a.end(),
      [i](const std::string& latter, const std::string& former) -> bool {
        return latter.at(i) < former.at(i);
      }  // lambda
    );  // stable sort
  }  // for-loop
}  // end

void RadixSort(std::vector<int>& a, int digit) {
  for (int i = 0, factor = 1; i < digit; ++i, factor *= 10) {
    std::stable_sort(a.begin(), a.end(),
      [factor](int latter, int former) -> bool {
        latter /= factor;
        former /= factor;
        return latter % 10 < former % 10;
      }  // lambda
    );  // stable sort
  }  // for-loop
}  // end


#endif /* end of include guard: RADIX_SORT_HPP_ */
