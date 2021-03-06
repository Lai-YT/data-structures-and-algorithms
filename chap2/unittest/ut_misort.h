#ifndef UT_MISORT_H_
#define UT_MISORT_H_

#include "../sort/merge_insert_sort.h"

#include <vector>

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if merge-insert sort sorts correctly

TEST(MIsortTest, i500) {
  std::srand(std::time(0));
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    MergInsertSort(a, 0, a.size() - 1);
    EXPECT_EQ(stdSorted, a);
  }
}

#endif /* end of include guard: UT_MISORT_H_ */
