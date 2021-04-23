#include "../sort/counting_sort.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <utility>
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

TEST(CountingTest, Stability) {
  std::vector<std::pair<int, char>> a{
    {2, 'a'}, {5, 'a'}, {3, 'a'}, {0, 'a'}, {2, 'b'}, {3, 'b'}, {0, 'b'}, {3, 'c'}
  }, b(8);
  CountingSort(a, b, 5);
  ASSERT_EQ(0, b.at(0).first);
  ASSERT_EQ(0, b.at(1).first);
  ASSERT_EQ(2, b.at(2).first);
  ASSERT_EQ(2, b.at(3).first);
  ASSERT_EQ(3, b.at(4).first);
  ASSERT_EQ(3, b.at(5).first);
  ASSERT_EQ(3, b.at(6).first);
  ASSERT_EQ(5, b.at(7).first);

  ASSERT_EQ('a', b.at(0).second);
  ASSERT_EQ('b', b.at(1).second);
  ASSERT_EQ('a', b.at(2).second);
  ASSERT_EQ('b', b.at(3).second);
  ASSERT_EQ('a', b.at(4).second);
  ASSERT_EQ('b', b.at(5).second);
  ASSERT_EQ('c', b.at(6).second);
  ASSERT_EQ('a', b.at(7).second);
}
