#include "../sort/bucket_sort.hpp"

#include <algorithm>
#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>

#include "../../chap2/util/random.hpp"

TEST(BucketTest, TextbookExe) {
  std::vector<double> a{
    0.79, 0.13, 0.16, 0.64, 0.39, 0.20, 0.89, 0.53, 0.71, 0.42
  };
  std::vector<double> b(a);

  BucketSort(a);
  std::sort(b.begin(), b.end());

  for (size_t i = 0; i < a.size(); ++i) {
    ASSERT_EQ(b.at(i), a.at(i));
  }
}

TEST(BucketTest, Random) {
  std::srand(std::time(0));
  std::vector<int> a = RandomArray(100, 0, 1000);
  std::vector<double> b(100, 0);
  for (size_t i = 0; i < 100; i++) {
    b.at(i) = a.at(i) / 1000;
  }
  std::vector<double> c(b);
  BucketSort(b, 20);
  std::sort(c.begin(), c.end());

  for (size_t i = 0; i < 100; ++i) {
    ASSERT_EQ(c.at(i), b.at(i));
  }
}
