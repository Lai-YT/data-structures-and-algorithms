#ifndef COUNTING_SORT_HPP_
#define COUNTING_SORT_HPP_

#include <algorithm>
#include <vector>

// at p.195

void CountingSort(const std::vector<int>& a, std::vector<int>& b, const int max) {
  std::vector<int> c(max + 1, 0);
  for (int n : a) {
    ++(c.at(n));
  }
  for (int i = 1; i <= max; ++i) {
    c.at(i) += c.at(i - 1);
  }
  for (auto itr = a.rbegin(); itr != a.rend(); ++itr) {
    // minus 1 because start from 0, text book start from 1
    b.at(c.at(*itr) - 1) = *itr;
    --c.at(*itr);
  }
}

#endif /* end of include guard: COUNTING_SORT_HPP_ */
