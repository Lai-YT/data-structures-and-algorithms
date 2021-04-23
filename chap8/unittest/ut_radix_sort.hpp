#include "../sort/radix_sort.hpp"

#include <algorithm>
#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>

#include "../../chap2/util/random.hpp"

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

TEST(RadixSort, Random) {
  std::srand(std::time(0));
  std::vector<int> a = RandomArray(100, 0, 10000);
  std::vector<int> b(a);

  RadixSort(a, 4);
  std::sort(b.begin(), b.end());

  for (size_t i = 0; i < a.size(); i++) {
    ASSERT_EQ(a.at(i), b.at(i));
  }
}
