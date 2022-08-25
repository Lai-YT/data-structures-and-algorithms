#include "../sort/select_sort.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "../util/random.hpp"

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if selection sort sorts correctly

TEST(SsortTest, Size500Time1000) {
  std::srand(std::time(0));
  const int TEST_ARRAY_SIZE = 500;
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> actual = RandomArray(TEST_ARRAY_SIZE, 0, TEST_ARRAY_SIZE * 2);
    std::vector<int> expected(actual);
    std::sort(expected.begin(), expected.end());

    SelectSort(actual);

    ASSERT_EQ(expected, actual);
  }
}
