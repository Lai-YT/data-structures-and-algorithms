#include "../sort/insert_sort.hpp"

#include <algorithm>
#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>


#include "../util/random.hpp"

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if insertion sort (and iterative) sorts correctly
class IsortTest : public ::testing::Test {
protected:
  const int TEST_ARRAY_SIZE = 500;
  const int ITERATION_COUNT = 1000;
};

TEST_F(IsortTest, Size500Time1000) {
  std::srand(std::time(0));
  for (size_t i = 0; i < ITERATION_COUNT; ++i) {
    std::vector<int> actual = RandomArray(TEST_ARRAY_SIZE, 0, TEST_ARRAY_SIZE * 2);
    std::vector<int> expected(actual);
    std::sort(expected.begin(), expected.end());

    InsertSort(actual);

    ASSERT_EQ(expected, actual);
  }
}

TEST_F(IsortTest, RecursiveSize500Time1000) {
  std::srand(std::time(0));
  for (size_t i = 0; i < ITERATION_COUNT; ++i) {
    std::vector<int> actual = RandomArray(TEST_ARRAY_SIZE, 0, TEST_ARRAY_SIZE * 2);
    std::vector<int> expected(actual);
    std::sort(expected.begin(), expected.end());

    RecurInsertSort(actual);

    ASSERT_EQ(expected, actual);
  }
}
