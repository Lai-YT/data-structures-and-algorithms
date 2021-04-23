#include "../sort/counting_sort.hpp"
#include "../sort/radix_sort.hpp"

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

TEST(RadixTest, Single) {
  std::vector<std::string> a{
    "z", "y", "w", "x", "g", "f", "e", "d", "c", "b", "a"
  };
  RadixSort(a, 1);
  EXPECT_EQ("a", a.at(0));
  EXPECT_EQ("b", a.at(1));
  EXPECT_EQ("c", a.at(2));
  EXPECT_EQ("d", a.at(3));
  EXPECT_EQ("e", a.at(4));
  EXPECT_EQ("f", a.at(5));
  EXPECT_EQ("g", a.at(6));
  EXPECT_EQ("w", a.at(7));
  EXPECT_EQ("x", a.at(8));
  EXPECT_EQ("y", a.at(9));
  EXPECT_EQ("z", a.at(10));
}

TEST(RadixTest, LowestSame) {
  std::vector<std::string> a{
    "z0", "y0", "w0", "x0", "g0", "f0", "e0", "d0", "c0", "b0", "a0"
  };
  RadixSort(a, 2);
  EXPECT_EQ("a0", a.at(0));
  EXPECT_EQ("b0", a.at(1));
  EXPECT_EQ("c0", a.at(2));
  EXPECT_EQ("d0", a.at(3));
  EXPECT_EQ("e0", a.at(4));
  EXPECT_EQ("f0", a.at(5));
  EXPECT_EQ("g0", a.at(6));
  EXPECT_EQ("w0", a.at(7));
  EXPECT_EQ("x0", a.at(8));
  EXPECT_EQ("y0", a.at(9));
  EXPECT_EQ("z0", a.at(10));
}

TEST(RadixTest, TextbookExe) {
  std::vector<std::string> a{
    "COW", "DOG", "SEA", "RUG", "ROW", "MOB", "BOX",
    "TAB", "BAR", "EAR", "TAR", "DIG", "BIG", "TEA",
    "NOW", "FOX"
  };

  RadixSort(a, 3);

  ASSERT_EQ("BAR", a.at(0));
  ASSERT_EQ("BIG", a.at(1));
  ASSERT_EQ("BOX", a.at(2));
  ASSERT_EQ("COW", a.at(3));
  ASSERT_EQ("DIG", a.at(4));
  ASSERT_EQ("DOG", a.at(5));
  ASSERT_EQ("EAR", a.at(6));
  ASSERT_EQ("FOX", a.at(7));
  ASSERT_EQ("MOB", a.at(8));
  ASSERT_EQ("NOW", a.at(9));
  ASSERT_EQ("ROW", a.at(10));
  ASSERT_EQ("RUG", a.at(11));
  ASSERT_EQ("SEA", a.at(12));
  ASSERT_EQ("TAB", a.at(13));
  ASSERT_EQ("TAR", a.at(14));
  ASSERT_EQ("TEA", a.at(15));
}

TEST(RadixTest, IntegerSameDigit) {
  std::vector<int> a{
    123, 236, 856, 942, 875, 648, 256, 547
  };
  RadixSort(a, 3);

  ASSERT_EQ(123, a.at(0));
  ASSERT_EQ(236, a.at(1));
  ASSERT_EQ(256, a.at(2));
  ASSERT_EQ(547, a.at(3));
  ASSERT_EQ(648, a.at(4));
  ASSERT_EQ(856, a.at(5));
  ASSERT_EQ(875, a.at(6));
  ASSERT_EQ(942, a.at(7));
}

TEST(RadixTest, IntegerDiffDigit) {
  std::vector<int> a{
    123, 6, 856, 42, 875, 1648, 256
  };
  RadixSort(a, 4);

  ASSERT_EQ(6, a.at(0));
  ASSERT_EQ(42, a.at(1));
  ASSERT_EQ(123, a.at(2));
  ASSERT_EQ(256, a.at(3));
  ASSERT_EQ(856, a.at(4));
  ASSERT_EQ(875, a.at(5));
  ASSERT_EQ(1648, a.at(6));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
