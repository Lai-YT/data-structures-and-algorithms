#include "../src/node.hpp"

#include <gtest/gtest.h>


TEST(NodeTest, Value) {
  Node<int> node{25};

  ASSERT_EQ(25, node.value);
  ASSERT_FALSE(node.next);
}


TEST(NodeTest, Next) {
  Node<int> node{25};
  Node<int> next_node{20};
  node.next = &next_node;

  ASSERT_TRUE(node.next);
  ASSERT_EQ(20, node.next->value);
}
