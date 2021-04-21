#include "../sort/counting_sort.hpp"

#include <gtest/gtest.h>
#include <vector>

// #include "../../chap2/util/random.hpp"

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

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
