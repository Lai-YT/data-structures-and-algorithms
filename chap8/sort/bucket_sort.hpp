#ifndef BUCKET_SORT_HPP_
#define BUCKET_SORT_HPP_

#include <cmath>
#include <vector>

#include "../../chap2/sort/insert_sort.hpp"

// at p.201

void BucketSort(std::vector<double>& a, size_t num_of_bucket = 10) {
  std::vector<std::vector<double>> bucket(num_of_bucket);
  for (double n : a) {
    bucket.at(floor(n * num_of_bucket)).push_back(n);
  }
  int index = 0;
  for (auto& vec : bucket) {
    if (vec.size() > 1) {
      InsertSort(vec);
    }
    if (vec.size()) {
      for (double n : vec) {
        a.at(index++) = n;
      }
    }
  }
}

#endif /* end of include guard: BUCKET_SORT_HPP_ */
