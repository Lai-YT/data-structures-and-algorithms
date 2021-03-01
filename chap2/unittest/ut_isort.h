#ifndef UT_ISORT_H_
#define UT_ISORT_H_

#include "../sort/insert_sort.h"

#include <algorithm>
#include <vector>

#include "../util/random.h"

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if insertion sort (and iterative) sorts correctly

TEST(IsortTest, i500) {
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    InsertSort(a);
    EXPECT_EQ(stdSorted, a);
  }
}

TEST(IterIsortTest, i500) {
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    IterInsertSort(a);
    EXPECT_EQ(stdSorted, a);
  }
}

#endif /* end of include guard: UT_ISORT_H_ */
