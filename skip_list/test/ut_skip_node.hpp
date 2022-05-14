#include <gtest/gtest.h>
#include <string>

#include "../src/skip_node.hpp"


/// The `value` and `level` of a node should be set properly by constructor.
TEST(SkipNodeTest, CallConstructor) {
  SkipNode<std::string> node{"MyNode", 15};

  ASSERT_EQ("MyNode", node.value());
  ASSERT_EQ(15, node.level());
}


/// Should be successfully set as the `next` node.
TEST(SkipNodeTest, SetNextSameLevel) {
  SkipNode<std::string> left{"left", 0};
  SkipNode<std::string> right{"right", 0};

  left.set_next(&right);

  ASSERT_EQ(left.next(), &right);
}


/// A LevelRelationException should be thrown when the node isn't at the same level.
TEST(SkipNodeTest, SetNextWrongLevel) {
  SkipNode<std::string> left{"left", 0};
  SkipNode<std::string> right{"right", 1};

  ASSERT_THROW({
    try {
      left.set_next(&right);
    } catch (const LevelRelationException& e) {
      EXPECT_STREQ("`next` node with level 1, should be 0", e.what());
      throw;
    }
  }, LevelRelationException);
}


/// Should be successfully set as the `down` node.
TEST(SkipNodeTest, SetDownOneLevelBelow) {
  SkipNode<std::string> top{"top", 10};
  SkipNode<std::string> down{"down", 9};

  top.set_down(&down);

  ASSERT_EQ(top.down(), &down);
}


/// A LevelRelationException should be thrown when the node isn't one level below.
TEST(SkipNodeTest, SetDownWrongLevel) {
  SkipNode<std::string> top{"top", 10};
  SkipNode<std::string> down{"down", 8};

  ASSERT_THROW({
    try {
      top.set_down(&down);
    } catch (const LevelRelationException& e) {
      EXPECT_STREQ("`down` node with level 8, should be 9", e.what());
      throw;
    }
  }, LevelRelationException);
}
