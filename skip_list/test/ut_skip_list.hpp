#include <gtest/gtest.h>

#include "../src/skip_list.hpp"
#include "../src/skip_node.hpp"


/// The first value of the list should be inserted without any exception thrown.
TEST(SkipListTest, InsertFirstNode) {
  SkipList<int> list{};

  ASSERT_NO_THROW(list.Insert(1));
}


/// Inserts 10 numbers, all of them should be inserted without any exceptions thrown.
TEST(SkipListTest, InsertNumberOneToTen) {
  SkipList<int> list{};

  ASSERT_NO_THROW({
    for (int i = 1; i <= 10; ++i) {
      list.Insert(i);
    }
  });
}


/// Though dummy value "0" is used in SkipList<int>, `value` insertion shouldn't be affected.
TEST(SkipListTest, InsertNumberNegativeTenToPositiveTen) {
  SkipList<int> list{};

  ASSERT_NO_THROW({
    for (int i = -10; i <= 10; ++i) {
      list.Insert(i);
    }
  });
}


/// Finds from an empty list, should get a null pointer.
TEST(SkipListTest, FindEmptyList) {
  SkipList<int> list{};

  auto* node = list.Find(-100);

  ASSERT_TRUE(node == nullptr);
}


/// Finds value from a one value list.
TEST(SkipListTest, FindOnlyValueInList) {
  SkipList<int> list{};
  list.Insert(1);

  auto* node = list.Find(1);

  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(1, node->value());
}


/// Inserts 50 values and finds all of them one by one.
TEST(SkipListTest, FindValues) {
  SkipList<int> list{};
  for (int i = 1; i <= 50; ++i) {
    list.Insert(i);
  }

  const int order[] = {  /* a random generated order */
    47, 42, 39, 12, 24, 23, 17, 7, 40, 33, 1, 3, 15, 2, 30, 34, 26, 44, 5, 36,
    20, 22, 10, 29, 50, 6, 38, 37, 31, 32, 8, 49, 27, 28, 48, 43, 13, 35, 45,
    19, 41, 16, 9, 14, 25, 18, 11, 21, 46, 4,
  };
  for (const int i : order) {
    auto* node = list.Find(i);

    ASSERT_TRUE(node != nullptr);
    ASSERT_EQ(i, node->value());
  }
}
