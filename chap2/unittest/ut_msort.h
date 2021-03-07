#ifndef UT_MSORT_H_
#define UT_MSORT_H_

#include "../sort/merge_sort.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "../util/random.h"

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if merge sort sorts correctly

TEST(MsortTest, Size500Time1000) {
  std::srand(std::time(0));
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    MergeSort(a, 0, a.size() - 1);
    ASSERT_EQ(stdSorted, a);
  }
}

#endif /* end of include guard: UT_MSORT_H_ */
