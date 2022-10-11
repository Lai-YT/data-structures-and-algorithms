#include <gtest/gtest.h>
#include <optional>
#include <string>

#include "../src/skip_list.hpp"
#include "../src/skip_node.hpp"


class SkipListTest : public ::testing::Test {
protected:
  SkipList<int, std::string> list_{};
};


/// The first value of the list should be inserted without any exception thrown.
TEST_F(SkipListTest, InsertFirstNode) {
  ASSERT_NO_THROW(list_.Insert({1, "1"}));
}


/// Inserts 10 numbers, all of them should be inserted without any exceptions thrown.
TEST_F(SkipListTest, InsertNumberOneToTen) {
  ASSERT_NO_THROW({
    for (int i = 1; i <= 10; ++i) {
      list_.Insert({i, std::to_string(i)});
    }
  });
}


/// Though dummy value "0" is used in SkipList<int>, `value` insertion shouldn't be affected.
TEST_F(SkipListTest, InsertNumberNegativeTenToPositiveTen) {
  ASSERT_NO_THROW({
    for (int i = -10; i <= 10; ++i) {
      list_.Insert({i, std::to_string(i)});
    }
  });
}


/// Existing keys should be inserted without any exceptions thrown.
TEST_F(SkipListTest, InsertExistingKey) {
  for (int i = -10; i <= 10; ++i) {
    list_.Insert({i, std::to_string(i)});
  }

  ASSERT_NO_THROW({
    for (int i = -10; i <= 10; ++i) {
      list_.Insert({i, std::to_string(i)});
    }
  });
}


/// Finds from an empty list, should get a null pointer.
TEST_F(SkipListTest, FindEmptyList) {
  std::optional<std::string> node = list_.Find(-100);

  ASSERT_FALSE(node.has_value());
}


/// Finds value from a one value list.
TEST_F(SkipListTest, FindOnlyValueInList) {
  list_.Insert({1, "1"});

  std::optional<std::string> value = list_.Find(1);

  ASSERT_TRUE(value);
  ASSERT_EQ("1", *value);
}


/// Inserts 50 values and finds all of them one by one.
TEST_F(SkipListTest, FindValues) {
  for (int i = 1; i <= 50; ++i) {
    list_.Insert({i, std::to_string(i)});
  }

  const int order[] = {  /* a random generated order */
    47, 42, 39, 12, 24, 23, 17, 7, 40, 33, 1, 3, 15, 2, 30, 34, 26, 44, 5, 36,
    20, 22, 10, 29, 50, 6, 38, 37, 31, 32, 8, 49, 27, 28, 48, 43, 13, 35, 45,
    19, 41, 16, 9, 14, 25, 18, 11, 21, 46, 4,
  };
  for (const int i : order) {
    std::optional<std::string> value = list_.Find(i);

    ASSERT_TRUE(value);
    ASSERT_EQ(std::to_string(i), *value);
  }
}


/// Though dummy value "0" is used in SkipList<int>, `value` find shouldn't be affected.
TEST_F(SkipListTest, FindValuesNegativeTenToPositiveTen) {
  for (int i = -10; i <= 10; ++i) {
    list_.Insert({i, std::to_string(i)});
  }

  const int order[] = {  /* a random generated order */
    -10, 7, -9, -1, 3, 6, 0, 10, 1, -2, -6, 8, -4, 2, -3, 4, -5, 9, -7, -8, 5,
  };
  for (const int i : order) {
    std::optional<std::string> value = list_.Find(i);

    ASSERT_TRUE(value);
    ASSERT_EQ(std::to_string(i), *value);
  }
}


/// Inserting existing `key` should update the `value` of that `key`.
TEST_F(SkipListTest, InsertExistingKeysToUpdateValues) {
  for (int i = -10; i <= 10; ++i) {
    list_.Insert({i, std::to_string(i)});
  }

  const int order[] = {  /* a random generated order */
    -10, 7, -9, -1, 3, 6, 0, 10, 1, -2, -6, 8, -4, 2, -3, 4, -5, 9, -7, -8, 5,
  };
  for (const int i : order) {
    list_.Insert({i, std::to_string(i + 100) /* new value */});
  }

  for (int i = -10; i <= 10; ++i) {
    std::optional<std::string> value = list_.Find(i);

    ASSERT_TRUE(value);
    ASSERT_EQ(std::to_string(i + 100), *value);
  }
}


/// The last value in the list should be deleted properly.
TEST_F(SkipListTest, DeleteOnlyValueInList) {
  list_.Insert({1, "1"});

  ASSERT_NO_THROW(list_.Delete(1));
  ASSERT_FALSE(list_.Find(1));
}


/// Deletes all 50 values from the list, so we should get nullptrs when we try to find those values.
TEST_F(SkipListTest, DeleteValues) {
  /* insert values */
  for (int i = 1; i <= 50; ++i) {
    list_.Insert({i, std::to_string(i)});
  }

  /* delete all */
  const int order[] = {  /* a random generated order */
    47, 42, 39, 12, 24, 23, 17, 7, 40, 33, 1, 3, 15, 2, 30, 34, 26, 44, 5, 36,
    20, 22, 10, 29, 50, 6, 38, 37, 31, 32, 8, 49, 27, 28, 48, 43, 13, 35, 45,
    19, 41, 16, 9, 14, 25, 18, 11, 21, 46, 4,
  };
  ASSERT_NO_THROW({
    for (const int i : order) {
      list_.Delete(i);
    }
  });

  /* find all */
  for (int i = 1; i <= 50; ++i) {
    ASSERT_FALSE(list_.Find(i));
  }
}


/// Though dummy value "0" is used in SkipList<int>, `value` deletion shouldn't be affected.
TEST_F(SkipListTest, DeleteValuesNegativeTenToPositiveTen) {
  for (int i = -10; i <= 10; ++i) {
    list_.Insert({i, std::to_string(i)});
  }

  const int order[] = {  /* a random generated order */
    -10, 7, -9, -1, 3, 6, 0, 10, 1, -2, -6, 8, -4, 2, -3, 4, -5, 9, -7, -8, 5,
  };
  ASSERT_NO_THROW({
    for (const int i : order) {
      list_.Delete(i);
    }
  });

  for (int i = -10; i <= 10; ++i) {
    ASSERT_FALSE(list_.Find(i));
  }
}


/// Deletion should clean up and re-link nodes properly so the coming insertion isn't broken.
TEST_F(SkipListTest, InsertAndDeleteAlternately) {
  for (int i = 0; i < 10; ++i) {
    for (int i = -10; i <= 10; ++i) {
      list_.Insert({i, std::to_string(i)});
    }
    for (int i = -10; i <= 10; ++i) {
      std::optional<std::string> value = list_.Find(i);
      ASSERT_TRUE(value);
      ASSERT_EQ(std::to_string(i), *value);
    }
    for (int i = -10; i <= 10; ++i) {
      list_.Delete(i);
    }
    for (int i = -10; i <= 10; ++i) {
      ASSERT_FALSE(list_.Find(i));
    }
  }
}

#ifdef MEM_DEBUG

/// The number of allocation and deallocation count should match, otherwise memory leaks.
TEST_F(SkipListTest, DeallocateNodesProperly) {
  /* reset the counters */
  SkipNode<int, std::string>::alloc_count = 0;
  SkipNode<int, std::string>::dealloc_count = 0;

  /* both counts should be 50 + 1 (header) after exiting the block */
  {
    SkipList<int, std::string> list{};
    for (int i = 1; i <= 50; ++i) {
      list.Insert({i, std::to_string(i)});
    }
  }

  ASSERT_EQ(51, (SkipNode<int, std::string>::alloc_count) /* the brackets are necessary to not break the macro */);
  ASSERT_EQ(51, (SkipNode<int, std::string>::dealloc_count));
}

#endif
