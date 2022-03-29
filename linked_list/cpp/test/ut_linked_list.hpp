#include "../src/linked_list.hpp"

#include <gtest/gtest.h>


class LinkedListTest : public ::testing::Test {
protected:
  void SetUp() {
    list_ = LinkedList<int>{};
  }

  LinkedList<int> list_;
};


TEST_F(LinkedListTest, Init) {
  ASSERT_FALSE(list_.head());
  ASSERT_FALSE(list_.tail());
}


TEST_F(LinkedListTest, AppendFrontFirst) {
  list_.AppendFront(10);
  ASSERT_TRUE(list_.head() == list_.tail());
  ASSERT_EQ(10, list_.head()->value);
}


TEST_F(LinkedListTest, AppendFront) {

}


TEST_F(LinkedListTest, AppendBackFirst) {

}


TEST_F(LinkedListTest, AppendBack) {

}


TEST_F(LinkedListTest, Find) {

}


TEST_F(LinkedListTest, Remove) {

}


TEST_F(LinkedListTest, RemoveNotExists) {

}


TEST_F(LinkedListTest, IsEmpty) {
  ASSERT_TRUE(list_.IsEmpty());
}
