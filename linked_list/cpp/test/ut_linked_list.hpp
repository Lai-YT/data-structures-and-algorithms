#include "../src/linked_list.hpp"

#include <functional>
#include <gtest/gtest.h>


/**
 * @brief This helper function if designed for LinkedList::Find.
 */
std::function<bool(int)> EqualTo(const int t) {
  return [t](const int x) -> bool {
    return x == t;
  };
}


class LinkedListTest : public ::testing::Test {
protected:
  void SetUp() {
    list_ = LinkedList<int>{};
  }

  LinkedList<int> list_;
};

/**
 * @brief Both head and tail should be null at the beginning.
 */
TEST_F(LinkedListTest, Init) {
  ASSERT_FALSE(list_.head());
  ASSERT_FALSE(list_.tail());
}

/**
 * @brief AppendFront() should have head and tail points to the same
 * node when there's only one node in the list.
 */
TEST_F(LinkedListTest, AppendFrontFirst) {
  list_.AppendFront(10);
  ASSERT_TRUE(list_.head() == list_.tail());
  ASSERT_EQ(10, list_.head()->value);
}

/**
 * @brief Appends 10 data from the front and test whether they are linked
 * properly.
 */
TEST_F(LinkedListTest, AppendFront) {
  for (int i = 0; i < 10; ++i) {
    list_.AppendFront(i);
  }

  /* AppendFront() has elements in reversed order */
  int i = 9;
  for (const Node<int>* cur = list_.head(); cur; cur = cur->next) {
    ASSERT_EQ(i--, cur->value);
  }
  ASSERT_EQ(-1, i);
}

/**
 * @brief AppendBack() should have head and tail points to the same
 * node when there's only one node in the list.
 */
TEST_F(LinkedListTest, AppendBackFirst) {
  list_.AppendBack(10);
  ASSERT_TRUE(list_.head() == list_.tail());
  ASSERT_EQ(10, list_.tail()->value);
}

/**
 * @brief Appends 10 data from the back and test whether they are linked
 * properly.
 */
TEST_F(LinkedListTest, AppendBack) {
  for (int i = 0; i < 10; ++i) {
    list_.AppendBack(i);
  }

  int i = 0;
  for (const Node<int>* cur = list_.head(); cur; cur = cur->next) {
    ASSERT_EQ(i++, cur->value);
  }
  ASSERT_EQ(10, i);
}

/**
 * @brief Inserts the data right after head when head is the only node.
 */
TEST_F(LinkedListTest, InsertAfterHeadOnly) {
  list_.AppendBack(-1);
  list_.InsertAfter(
      list_.Find(EqualTo(-1)),
      -2
  );
  ASSERT_EQ(-1, list_.head()->value);  /* value not changed */
  ASSERT_TRUE(list_.head()->next);  /* did insert something */
  ASSERT_EQ(-2, list_.head()->next->value);  /* is what we inserted */
  ASSERT_FALSE(list_.head()->next->next);
}

/**
 * @brief Inserts the data right after head when there are already 10 nodes
 * in the list.
 */
TEST_F(LinkedListTest, InsertAfterHead) {
  for (int i = 0; i < 10; ++i) {
    list_.AppendBack(i);
  }
  list_.InsertAfter(
      list_.Find(EqualTo(0)),
      -1
  );
  const auto* tar = list_.head();
  ASSERT_EQ(0, tar->value);
  tar = tar->next;
  ASSERT_EQ(-1, tar->value);
  tar = tar->next;
  ASSERT_EQ(1, tar->value);
}

/**
 * @brief The special part of insert after tail is that the tail pointer has to
 * follow up.
 */
TEST_F(LinkedListTest, InsertAfterTail) {
  for (int i = 0; i < 10; ++i) {
    list_.AppendBack(i);
  }
  const auto* origin_tail = list_.tail();
  list_.InsertAfter(
      list_.Find(EqualTo(9)),
      -1
  );
  ASSERT_EQ(9, origin_tail->value);
  /* make sure the tail pointer do follow up */
  EXPECT_TRUE(origin_tail->next == list_.tail());
  EXPECT_EQ(-1, list_.tail()->value);
  EXPECT_FALSE(list_.tail()->next);
}

/**
 * @brief Inserts the data into the middle of the list and checks if they are
 * linked properly.
 */
TEST_F(LinkedListTest, InsertAfterMiddle) {
  for (int i = 0; i < 100; ++i) {
    list_.AppendBack(i);
  }
  list_.InsertAfter(
      list_.Find(EqualTo(67)),
      -2
  );
  auto* tar = list_.Find(EqualTo(67));
  ASSERT_EQ(67, tar->value);
  tar = tar->next;
  ASSERT_EQ(-2, tar->value);
  tar = tar->next;
  ASSERT_EQ(68, tar->value);
}

/**
 * @brief The node to find is in the middle of the list, which is the common case.
 */
TEST_F(LinkedListTest, FindMiddle) {
  const int VALUE_TO_FIND = 37;

  const Node<int>* tar = nullptr;
  for (int i = 0; i < 100; ++i) {
    list_.AppendBack(i);
    if (i == VALUE_TO_FIND) {
      tar = list_.tail();
    }
  }
  Node<int>* res = list_.Find(EqualTo(VALUE_TO_FIND));
  /* did find something and is what we want */
  ASSERT_TRUE(res);
  ASSERT_EQ(tar, res);
}

/**
 * @brief The node to find is exactly the head.
 */
TEST_F(LinkedListTest, FindHead) {
  for (int i = 0; i < 100; ++i) {
    list_.AppendBack(i);
  }
  Node<int>* res = list_.Find(EqualTo(list_.head()->value));
  ASSERT_TRUE(res);
  ASSERT_EQ(list_.head(), res);
}

/**
 * @brief The node to find is exactly the tail.
 */
TEST_F(LinkedListTest, FindTail) {
  for (int i = 0; i < 100; ++i) {
    list_.AppendBack(i);
  }
  Node<int>* res = list_.Find(EqualTo(list_.tail()->value));
  ASSERT_TRUE(res);
  ASSERT_EQ(list_.tail(), res);
}

/**
 * @brief The node in the middle of the list is removed, which is the common case.
 */
TEST_F(LinkedListTest, Remove) {
  const int VALUE_TO_REMOVE = 67;

  for (int i = 0; i < 100; ++i) {
    list_.AppendBack(i);
  }

  auto* tar = list_.Find(EqualTo(VALUE_TO_REMOVE));
  ASSERT_TRUE(tar);
  list_.Remove(tar);

  int i = 0;
  for (const Node<int>* cur = list_.head(); cur; cur = cur->next) {
    if (i == VALUE_TO_REMOVE) {
      /* skip */
      ++i;
    }
    ASSERT_EQ(i++, cur->value);
  }
  ASSERT_EQ(100, i);
}

/**
 * @brief The head node of the list may also be removed, the head pointer should
 * follow up.
 */
TEST_F(LinkedListTest, RemoveHead) {
  for (int i = 0; i < 10; ++i) {
    list_.AppendBack(i);
  }
  list_.Remove(list_.Find(EqualTo(0 /* this is the head */)));
  ASSERT_TRUE(list_.head());
  ASSERT_EQ(1, list_.head()->value);
  ASSERT_EQ(2, list_.head()->next->value);
}

/**
 * @brief The head node of the list may also be removed, the head pointer should
 * follow up.
 */
TEST_F(LinkedListTest, RemoveTail) {
  for (int i = 0; i < 10; ++i) {
    list_.AppendBack(i);
  }
  list_.Remove(list_.Find(EqualTo(9 /* this is the tail */)));

  ASSERT_TRUE(list_.tail());
  ASSERT_EQ(8, list_.tail()->value);
  ASSERT_FALSE(list_.tail()->next);

  int i = 0;
  for (const Node<int>* cur = list_.head(); cur; cur = cur->next) {
    ASSERT_EQ(i++, cur->value);
  }
  ASSERT_EQ(9, i);
}

/**
 * @brief The last node of the list may also be removed, the head and tail
 * pointers should be safely set back to null.
 */
TEST_F(LinkedListTest, RemoveLastOne) {
  list_.AppendFront(1);
  list_.Remove(list_.Find(EqualTo(1)));
  ASSERT_TRUE(list_.IsEmpty());
}

/**
 * @brief The node to remove isn't in the list, every thing should be kept unchanged.
 */
TEST_F(LinkedListTest, RemoveNotExists) {
  for (int i = 0; i < 10; ++i) {
    list_.AppendBack(i);
  }
  auto tar = Node<int>{50};
  /* "invalid pointer" will occur immediately if this
    stack-allocated pointer is deleted */
  list_.Remove(&tar);

  /* tar not modified */
  ASSERT_EQ(50, tar.value);
  ASSERT_FALSE(tar.next);

  /* list not modified */
  int i = 0;
  for (const Node<int>* cur = list_.head(); cur; cur = cur->next) {
    ASSERT_EQ(i++, cur->value);
  }
  ASSERT_EQ(10, i);
}

/**
 * @brief The list can be called "empty" only if there's no node in the list.
 */
TEST_F(LinkedListTest, IsEmpty) {
  ASSERT_TRUE(list_.IsEmpty());

  list_.AppendFront(0);
  ASSERT_FALSE(list_.IsEmpty());

  list_.Remove(list_.Find(EqualTo(0)));
  ASSERT_TRUE(list_.IsEmpty());
}

/**
 * @brief An empty list shouldn't be broken after the reversal.
 */
TEST_F(LinkedListTest, ReverseEmpty) {
  list_.Reverse();
  ASSERT_TRUE(list_.IsEmpty());
}

/**
 * @brief A list with only 1 node should stay the same after the reversal.
 */
TEST_F(LinkedListTest, ReverseOnlyOne) {
  list_.AppendFront(1);
  ASSERT_TRUE(list_.head());
  ASSERT_TRUE(list_.tail());
  ASSERT_TRUE(list_.head() == list_.tail());
  ASSERT_EQ(1, list_.head()->value);
  ASSERT_FALSE(list_.head()->next);
}

/**
 * @brief Normally reverse a list with 100 nodes.
 */
TEST_F(LinkedListTest, Reverse) {
  for (int i = 0; i < 100; ++i) {
    list_.AppendBack(i);
  }

  list_.Reverse();

  int i = 99;
  for (const Node<int>* cur = list_.head(); cur; cur = cur->next) {
    ASSERT_EQ(i--, cur->value);
  }
  ASSERT_EQ(-1, i);
  ASSERT_FALSE(list_.tail()->next);  /* all links should be reversed */
}
