#include "../sort/insert_sort.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "../util/random.hpp"

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if insertion sort (and iterative) sorts correctly

TEST(IsortTest, Size500Time1000) {
  std::srand(std::time(0));
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    InsertSort(a);
    ASSERT_EQ(stdSorted, a);
  }
}

TEST(IterIsortTest, Size500Time1000) {
  std::srand(std::time(0));
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    std::vector<int> stdSorted(a);
    std::sort(stdSorted.begin(), stdSorted.end());
    IterInsertSort(a);
    ASSERT_EQ(stdSorted, a);
  }
}
