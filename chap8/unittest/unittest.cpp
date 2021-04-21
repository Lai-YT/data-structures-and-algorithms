#include "../sort/counting_sort.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

#include "../../chap2/util/random.hpp"

TEST(CountingTest, TextbookFig) {
  std::vector<int> a{2, 5, 3, 0, 2, 3, 0, 3}, b(8);
  CountingSort(a, b, 5);
  ASSERT_EQ(0, b.at(0));
  ASSERT_EQ(0, b.at(1));
  ASSERT_EQ(2, b.at(2));
  ASSERT_EQ(2, b.at(3));
  ASSERT_EQ(3, b.at(4));
  ASSERT_EQ(3, b.at(5));
  ASSERT_EQ(3, b.at(6));
  ASSERT_EQ(5, b.at(7));
}

TEST(CountingTest, TextbookExe) {
  std::vector<int> a{6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2}, b(11);
  CountingSort(a, b, 6);
  std::sort(a.begin(), a.end());
  for (size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(a.at(i), b.at(i));
  }
}

TEST(CountingTest, Random) {
  std::vector<int> a = RandomArray(100, 0, 100), b(100);
  CountingSort(a, b, 99);
  std::sort(a.begin(), a.end());
  for (size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(a.at(i), b.at(i));
  }
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
