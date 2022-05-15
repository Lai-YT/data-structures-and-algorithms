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


/// Though dummy value "0" is used in SkipList<int>, `value` find shouldn't be affected.
TEST(SkipListTest, FindValuesNegativeTenToPositiveTen) {
  SkipList<int> list{};

  for (int i = -10; i <= 10; ++i) {
    list.Insert(i);
  }

  const int order[] = {  /* a random generated order */
    -10, 7, -9, -1, 3, 6, 0, 10, 1, -2, -6, 8, -4, 2, -3, 4, -5, 9, -7, -8, 5,
  };
  for (const int i : order) {
    auto* node = list.Find(i);

    ASSERT_TRUE(node != nullptr);
    ASSERT_EQ(i, node->value());
  }
}


/// The last value in the list should be deleted properly.
TEST(SkipListTest, DeleteOnlyValueInList) {
  SkipList<int> list{};
  list.Insert(1);

  ASSERT_NO_THROW(list.Delete(1));
  ASSERT_TRUE(list.Find(1) == nullptr);
}


/// Deletes all 50 values from the list, so we should get nullptrs when we try to find those values.
TEST(SkipListTest, DeleteValues) {
  SkipList<int> list{};
  /* insert values */
  for (int i = 1; i <= 50; ++i) {
    list.Insert(i);
  }

  /* delete all */
  const int order[] = {  /* a random generated order */
    47, 42, 39, 12, 24, 23, 17, 7, 40, 33, 1, 3, 15, 2, 30, 34, 26, 44, 5, 36,
    20, 22, 10, 29, 50, 6, 38, 37, 31, 32, 8, 49, 27, 28, 48, 43, 13, 35, 45,
    19, 41, 16, 9, 14, 25, 18, 11, 21, 46, 4,
  };
  ASSERT_NO_THROW({
    for (const int i : order) {
      list.Delete(i);
    }
  });

  /* find all */
  for (int i = 1; i <= 50; ++i) {
    ASSERT_TRUE(list.Find(i) == nullptr);
  }
}


/// Though dummy value "0" is used in SkipList<int>, `value` deletion shouldn't be affected.
TEST(SkipListTest, DeleteValuesNegativeTenToPositiveTen) {
  SkipList<int> list{};

  for (int i = -10; i <= 10; ++i) {
    list.Insert(i);
  }

  const int order[] = {  /* a random generated order */
    -10, 7, -9, -1, 3, 6, 0, 10, 1, -2, -6, 8, -4, 2, -3, 4, -5, 9, -7, -8, 5,
  };
  ASSERT_NO_THROW({
    for (const int i : order) {
      list.Delete(i);
    }
  });

  for (int i = -10; i <= 10; ++i) {
    ASSERT_TRUE(list.Find(i) == nullptr);
  }
}


/// Deletion should clean up and re-link nodes properly so the coming insertion isn't broken.
TEST(SkipListTest, InsertAndDeleteAlternately) {
  SkipList<int> list{};

  for (int i = 0; i < 10; ++i) {
    for (int i = -10; i <= 10; ++i) {
      list.Insert(i);
    }
    for (int i = -10; i <= 10; ++i) {
      auto* node = list.Find(i);
      ASSERT_TRUE(node != nullptr);
      ASSERT_EQ(i, node->value());
    }
    for (int i = -10; i <= 10; ++i) {
      list.Delete(i);
    }
    for (int i = -10; i <= 10; ++i) {
      ASSERT_TRUE(list.Find(i) == nullptr);
    }
  }
}


#ifdef MEM_DEBUG

/// The number of allocation and deallocation count should match, otherwise memory leaks.
TEST(SkipListTest, DeallocateNodesProperly) {
  /* reset the counters */
  SkipNode<int>::alloc_count = 0;
  SkipNode<int>::dealloc_count = 0;

  /* both counts should be 50 + 1 (header) after exiting the block */
  {
    SkipList<int> list{};
    for (int i = 1; i <= 50; ++i) {
      list.Insert(i);
    }
  }

  ASSERT_EQ(51, SkipNode<int>::alloc_count);
  ASSERT_EQ(51, SkipNode<int>::dealloc_count);
}

#endif
