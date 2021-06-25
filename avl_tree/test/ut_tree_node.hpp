#include "../src/tree_node.hpp"

#include <gtest/gtest.h>
#include <string>


TEST(TreeNodeTest, ConstructNode) {
  TreeNode<std::string> tree_node("April", 4);
  ASSERT_EQ(tree_node.data, "April");
  ASSERT_EQ(tree_node.key, 4);
  ASSERT_EQ(tree_node.height, 0);
  ASSERT_TRUE(tree_node.left == nullptr);
  ASSERT_TRUE(tree_node.right == nullptr);
}

TEST(TreeNodeTest, SetNode) {
  TreeNode<std::string> root_node("April", 4),
                             right_node("May", 5),
                             left_node("March", 3);
  root_node.left = &left_node;
  root_node.right = &right_node;

  ASSERT_EQ(root_node.left->data, "March");
  ASSERT_EQ(root_node.left->key, 3);
  ASSERT_EQ(root_node.left->height, 0);

  ASSERT_EQ(root_node.right->data, "May");
  ASSERT_EQ(root_node.right->key, 5);
  ASSERT_EQ(root_node.right->height, 0);
}
