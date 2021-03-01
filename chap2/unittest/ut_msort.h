#ifndef UT_MSORT_H_
#define UT_MSORT_H_

#include "../sort/merge_sort.h"

#include <algorithm>
#include <cstdlib>
#include <vector>

TEST(MsortTest, i500) {
  std::srand(std::time(0));
  std::vector<int> a(500);
  for (size_t i = 0; i < 1000; ++i) {
    for (size_t j = 0; j < 500; ++j) {
      a.at(j) = (std::rand() % 1000);
    }
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    MergeSort(a, 0, a.size() - 1);
    EXPECT_EQ(stdSorted, a);
  }
}

#endif /* end of include guard: UT_MSORT_H_ */
