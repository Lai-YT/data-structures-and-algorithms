#ifndef BUCKET_SORT_HPP_
#define BUCKET_SORT_HPP_

#include <cmath>
#include <vector>

#include "../../chap2/sort/insert_sort.hpp"

// at p.201

void BucketSort(std::vector<double>& a, size_t num_of_buckets = 10) {
  std::vector<std::vector<double>> buckets(num_of_buckets);
  // put into buckets
  for (double n : a) {
    buckets.at(floor(n * num_of_buckets)).push_back(n);
  }
  int index = 0;
  for (auto& vec : buckets) {
    // inner sort
    if (vec.size() > 1) {
      InsertSort(vec);
    }
    // put sorted elements back
    if (vec.size()) {
      for (double n : vec) {
        a.at(index++) = n;
      }
    }
  }
}

#endif /* end of include guard: BUCKET_SORT_HPP_ */
