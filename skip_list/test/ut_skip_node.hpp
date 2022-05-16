#include <gtest/gtest.h>
#include <string>

#include "../src/skip_node.hpp"


/**
 * @brief The `key`-`value` pair and `level` of a node should be set properly by
 * constructor, and all its forward nodes should be null.
 */
TEST(SkipNodeTest, CallConstructor) {
  SkipNode<std::string, int> node{{"MyNode", 1}, 5};

  ASSERT_EQ("MyNode", node.key());
  ASSERT_EQ(1, node.value());
  ASSERT_EQ(5, node.level());
  for (int i = 1; i <= node.level(); ++i) {
    ASSERT_TRUE(node.forward(i) == nullptr);
  }
}


/// The forward nodes can be null.
TEST(SkipNodeTest, SetForwardNull) {
  SkipNode<std::string, int> node{{"MyNode", 1}, 5};

  ASSERT_NO_THROW(node.set_forward(nullptr, 1));
  ASSERT_TRUE(node.forward(1) == nullptr);
}


/// Forward nodes should be properly set and get when they don't exceed the forward level that the node can have.
TEST(SkipNodeTest, SetForwardInLimit) {
  SkipNode<std::string, int> node{{"MyNode", 1}, 5};
  SkipNode<std::string, int> forwards[] = {
    SkipNode<std::string, int>{{"a", 1}, 1}, SkipNode<std::string, int>{{"b", 2}, 2},
    SkipNode<std::string, int>{{"c", 3}, 3}, SkipNode<std::string, int>{{"d", 4}, 4},
    SkipNode<std::string, int>{{"e", 5}, 5},
  };

  for (int i = 1; i <= node.level(); ++i) {
    node.set_forward(&forwards[i - 1], i);
  }

  for (int i = 1; i <= node.level(); ++i) {
    ASSERT_EQ(i, node.forward(i)->value());
  }
}


/// Exception should be thrown when a low level node is set as a high level forward node.
TEST(SkipNodeTest, SetForwardTooLowLevel) {
  SkipNode<std::string, int> node{{"MyNode", 1}, 5};
  SkipNode<std::string, int> forward{{"a", 1}, 3};

  ASSERT_THROW({
    try {
      node.set_forward(&forward, 5);
    } catch (const LevelRelationException& e) {
      EXPECT_STREQ("a level 5 forward node should have its level greater than 5, but only 3", e.what());
      throw;
    }
  }, LevelRelationException);
}


/// Exception should be thrown when a level n forward node is set to a level m node, where n > m.
TEST(SkipNodeTest, SetForwardExceedLimit) {
  SkipNode<std::string, int> node{{"MyNode", 1}, 5};
  SkipNode<std::string, int> forward{{"a", 1}, 6};

  ASSERT_THROW({
    try {
      node.set_forward(&forward, 6);
    } catch (const LevelRelationException& e) {
      EXPECT_STREQ("level 6 exceeds the limit, which is 5", e.what());
      throw;
    }
  }, LevelRelationException);
}


/// Exception should be thrown when getting a high level forward node from a low level node.
TEST(SkipNodeTest, GetForwardExceedLimit) {
  SkipNode<std::string, int> node{{"MyNode", 1}, 5};

  ASSERT_THROW({
    try {
      node.forward(6);
    } catch (const LevelRelationException& e) {
      EXPECT_STREQ("level 6 exceeds the limit, which is 5", e.what());
      throw;
    }
  }, LevelRelationException);
}
