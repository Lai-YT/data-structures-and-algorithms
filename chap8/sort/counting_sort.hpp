#ifndef COUNTING_SORT_HPP_
#define COUNTING_SORT_HPP_

#include <algorithm>
#include <utility>
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

template<typename T>
void CountingSort(
    const std::vector<std::pair<int, T>>& a,
    std::vector<std::pair<int, T>>& b,
    const int max)
{
  std::vector<int> c(max + 1, 0);
  for (auto n : a) {
    ++(c.at(n.first));
  }
  for (int i = 1; i <= max; ++i) {
    c.at(i) += c.at(i - 1);
  }
  for (auto itr = a.rbegin(); itr != a.rend(); ++itr) {
    // minus 1 because start from 0, text book start from 1
    b.at(c.at(itr->first) - 1) = *itr;
    --c.at(itr->first);
  }
}

#endif /* end of include guard: COUNTING_SORT_HPP_ */
