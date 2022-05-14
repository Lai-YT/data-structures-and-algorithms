#include <gtest/gtest.h>
#include <string>

#include "../src/skip_node.hpp"


/**
 * @brief The `value` and `level` of a node should be set properly by constructor,
 * and all its forward nodes should be null.
 */
TEST(SkipNodeTest, CallConstructor) {
  SkipNode<std::string> node{"MyNode", 15};

  ASSERT_EQ("MyNode", node.value());
  ASSERT_EQ(15, node.level());
  for (int i = 1; i <= node.level(); ++i) {
    ASSERT_TRUE(node.forward(i) == nullptr);
  }
}


/// Forward nodes should be properly set and get when they don't exceed the forward level that the node can have.
TEST(SkipNodeTest, SetForwardInLimit) {
  SkipNode<std::string> node{"MyNode", 5};
  SkipNode<std::string> forwards[] = {
    SkipNode<std::string>{"1", 1}, SkipNode<std::string>{"2", 2}, SkipNode<std::string>{"3", 3},
    SkipNode<std::string>{"4", 4}, SkipNode<std::string>{"5", 5}
  };

  for (int i = 1; i <= node.level(); ++i) {
    node.set_forward(&forwards[i - 1], i);
  }

  for (int i = 1; i <= node.level(); ++i) {
    ASSERT_EQ(std::to_string(i), node.forward(i)->value());
  }
}


/// Exception should be thrown when a low level node is set as a high level forward node.
TEST(SkipNodeTest, SetForwardTooLowLevel) {
  SkipNode<std::string> node{"MyNode", 5};
  SkipNode<std::string> forward{"3", 3};

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
  SkipNode<std::string> node{"MyNode", 5};
  SkipNode<std::string> forward{"6", 6};

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
  SkipNode<std::string> node{"MyNode", 5};

  ASSERT_THROW({
    try {
      node.forward(6);
    } catch (const LevelRelationException& e) {
      EXPECT_STREQ("level 6 exceeds the limit, which is 5", e.what());
      throw;
    }
  }, LevelRelationException);
}
