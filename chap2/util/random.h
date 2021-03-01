#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>
#include <utility>
#include <vector>

// lower_bound included, upper_bound excluded
std::vector<int> RandomArray(int size, int lower_bound, int upper_bound) {
  std::srand(std::time(0));
  std::vector<int> v(size);
  for (int n : v) {
    n = std::rand() % (upper_bound - lower_bound) + lower_bound;
  }
  return std::move(v);
}

#endif /* end of include guard: RANDOM_H_ */
