#ifndef UT_ISORT_H_
#define UT_ISORT_H_

#include "../sort/insert_sort.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if insertion sort (and iterative) sorts correctly

TEST(IsortTest, i500) {
  std::srand(std::time(0));
  std::vector<int> a(500);
  for (size_t i = 0; i < 1000; ++i) {
    for (size_t j = 0; j < 500; ++j) {
      a.at(j) = (std::rand() % 1000);
    }
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    InsertSort(a);
    EXPECT_EQ(stdSorted, a);
  }
}

TEST(IterIsortTest, i500) {
  std::srand(std::time(0));
  std::vector<int> a(500);
  for (size_t i = 0; i < 1000; ++i) {
    for (size_t j = 0; j < 500; ++j) {
      a.at(j) = (std::rand() % 1000);
    }
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    IterInsertSort(a);
    EXPECT_EQ(stdSorted, a);
  }
}

#endif /* end of include guard: UT_ISORT_H_ */
