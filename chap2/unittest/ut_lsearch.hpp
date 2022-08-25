#include "../srch/linear_search.hpp"

#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>

#include "../util/random.hpp"


class LsearchTest : public ::testing::Test {
protected:
  const int TEST_ARRAY_SIZE = 500;
  const int MAX_POSSIBLE_VAL_PLUS_ONE = 1000;
  const int ITERATION_COUNT = 1000;
};

TEST_F(LsearchTest, Found) {
  std::srand(std::time(0));
  for (size_t i = 0; i < ITERATION_COUNT; ++i) {
    std::vector<int> array = RandomArray(TEST_ARRAY_SIZE, 0, MAX_POSSIBLE_VAL_PLUS_ONE);
    const int target_index = Random(0, TEST_ARRAY_SIZE);
    const int target = MAX_POSSIBLE_VAL_PLUS_ONE;
    array[target_index] = target;

    const int actual_index = LinearSearch(array, target);

    ASSERT_EQ(target_index, actual_index);
  }
}

TEST_F(LsearchTest, NotFound) {
  std::srand(std::time(0));
  for (size_t i = 0; i < ITERATION_COUNT; ++i) {
    const std::vector<int> array = RandomArray(TEST_ARRAY_SIZE, 0, MAX_POSSIBLE_VAL_PLUS_ONE);

    const int actual_index = LinearSearch(array, MAX_POSSIBLE_VAL_PLUS_ONE);

    ASSERT_EQ(array.size(), actual_index);
  }
}
