#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>
#include <utility>
#include <vector>

// lower_bound included, upper_bound excluded: [lower_bound, upper_bound)
std::vector<int> RandomArray(int size, int lower_bound, int upper_bound) {
  std::vector<int> v(size);
  for (int n : v) {
    n = std::rand() % (upper_bound - lower_bound) + lower_bound;
  }
  return std::move(v);
}

// a random number in range [lower_bound, upper_bound)
int Random(int lower_bound, int upper_bound) {
  return std::rand() % (upper_bound - lower_bound) + lower_bound;
}

#endif /* end of include guard: RANDOM_H_ */
