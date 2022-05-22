#include "../src/tree_node.hpp"

#include <gtest/gtest.h>
#include <string>


/** A tree node should have `key`, `value`, `height` and its `left`, `right` child. */
TEST(TreeNodeTest, ConstructNode) {
  TreeNode<int, std::string> tree_node{{4, "April"}};

  ASSERT_EQ(4, tree_node.key());
  ASSERT_EQ("April", tree_node.value());
  ASSERT_EQ(0, tree_node.height());
  ASSERT_TRUE(tree_node.left() == nullptr);
  ASSERT_TRUE(tree_node.right() == nullptr);
}


TEST(TreeNodeTest, SetChildren) {
  TreeNode<int, std::string> root_node{{4, "April"}};
  TreeNode<int, std::string> right_node{{5, "May"}};
  TreeNode<int, std::string> left_node{{3, "March"}};

  root_node.set_left(&left_node);
  root_node.set_right(&right_node);

  /* child on the both sides are set properly */
  ASSERT_EQ("March", root_node.left()->value());
  ASSERT_EQ(3, root_node.left()->key());

  ASSERT_EQ("May", root_node.right()->value());
  ASSERT_EQ(5, root_node.right()->key());
}
