#include "../src/node.hpp"

#include <gtest/gtest.h>


TEST(NodeTest, Value) {
  Node node{25};

  ASSERT_EQ(25, node.value);
  ASSERT_FALSE(node.next);
}


TEST(NodeTest, Next) {
  Node node{25};
  node.next = new Node(20);

  ASSERT_TRUE(node.next);
  ASSERT_EQ(20, node.next->value);
  
  delete node.next;
  node.next = nullptr;
}
