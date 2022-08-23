#include "../sort/merge_sort.hpp"

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "../util/random.hpp"


TEST(MsortTest, EmptyArray) {
  std::vector<int> array;

  MergeSort(array, 0, array.size());
}

TEST(MsortTest, OnlyOneElement) {
  std::vector<int> array = {100};

  MergeSort(array, 0, array.size());

  ASSERT_EQ(1, array.size());
  ASSERT_EQ(100, array.at(0));
}

TEST(MsortTest, AlreadySorted) {
  std::vector<int> array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  const std::vector<int> expected = array;

  MergeSort(array, 0, array.size());

  ASSERT_EQ(expected, array);
}

TEST(MsortTest, ReverseOrder) {
  std::vector<int> array = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  const std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  MergeSort(array, 0, array.size());

  ASSERT_EQ(expected, array);
}

TEST(MsortTest, Unsorted) {
  std::vector<int> array = {2, 7, 6, 3, 10, 9, 5, 8, 1, 4};
  const std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  MergeSort(array, 0, array.size());

  ASSERT_EQ(expected, array);
}

// randomly generate 1000 arrays, each with length 500,
// use std::sort to test if merge sort sorts correctly

TEST(MsortTest, Size500Time1000) {
  std::srand(std::time(0));
  const int TEST_ARRAY_SIZE = 500;
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> actual = RandomArray(TEST_ARRAY_SIZE, 0, TEST_ARRAY_SIZE * 2);
    std::vector<int> expected(actual);
    std::sort(expected.begin(), expected.end());

    MergeSort(actual, 0, actual.size());

    ASSERT_EQ(expected, actual);
  }
}
