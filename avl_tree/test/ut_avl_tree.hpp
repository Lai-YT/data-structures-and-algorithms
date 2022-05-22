#include "../src/avl_tree.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <string>

#include "../src/tree_node.hpp"


class AVLTreeTest : public ::testing::Test {
protected:
  void SetUp() override {
#ifdef MEM_DEBUG
    ASSERT_EQ(0, (TreeNode<int, std::string>::leak_count));
#endif
    month_tree_.Insert({6,  "June"});
    month_tree_.Insert({3,  "March"});
    month_tree_.Insert({9,  "September"});
    month_tree_.Insert({1,  "January"});
    month_tree_.Insert({12, "December"});
    month_tree_.Insert({10, "October"});
    month_tree_.Insert({4,  "April"});
    month_tree_.Insert({8,  "August"});
    month_tree_.Insert({2,  "February"});
    month_tree_.Insert({11, "November"});
    month_tree_.Insert({5,  "May"});
    month_tree_.Insert({7,  "July"});
  }

  AVLTree<int, std::string> month_tree_;
  AVLTree<int, int> tree_;
};


/**
 * Inserts a `key`-`value` with the `key` already exist, the old value
 * should be updated by `value`.
 */
TEST_F(AVLTreeTest, UpdateImplicitlyByInsert) {
  month_tree_.Insert({10, "<October>"});

  const std::vector<std::string> months = month_tree_.Traverse();
  ASSERT_EQ(12, months.size());
  ASSERT_EQ("January",   months.at(0));
  ASSERT_EQ("February",  months.at(1));
  ASSERT_EQ("March",     months.at(2));
  ASSERT_EQ("April",     months.at(3));
  ASSERT_EQ("May",       months.at(4));
  ASSERT_EQ("June",      months.at(5));
  ASSERT_EQ("July",      months.at(6));
  ASSERT_EQ("August",    months.at(7));
  ASSERT_EQ("September", months.at(8));
  ASSERT_EQ("<October>", months.at(9));
  ASSERT_EQ("November",  months.at(10));
  ASSERT_EQ("December",  months.at(11));
}


TEST_F(AVLTreeTest, Search) {
  ASSERT_EQ("January",   month_tree_.Search(1)->value());
  ASSERT_EQ("February",  month_tree_.Search(2)->value());
  ASSERT_EQ("March",     month_tree_.Search(3)->value());
  ASSERT_EQ("April",     month_tree_.Search(4)->value());
  ASSERT_EQ("May",       month_tree_.Search(5)->value());
  ASSERT_EQ("June",      month_tree_.Search(6)->value());
  ASSERT_EQ("July",      month_tree_.Search(7)->value());
  ASSERT_EQ("August",    month_tree_.Search(8)->value());
  ASSERT_EQ("September", month_tree_.Search(9)->value());
  ASSERT_EQ("October",   month_tree_.Search(10)->value());
  ASSERT_EQ("November",  month_tree_.Search(11)->value());
  ASSERT_EQ("December",  month_tree_.Search(12)->value());
  /* not found */
  ASSERT_TRUE(month_tree_.Search(0) == nullptr);
  ASSERT_TRUE(month_tree_.Search(13) == nullptr);
}


/**
 * Inserts 0 ~ 9, since this is the ascending order, new node is always the
 * right-most node; left rotations should be performed correclty.
 */
TEST_F(AVLTreeTest, LeftRotate) {
  for (int i = 0; i < 10; ++i) {
    tree_.Insert({i, i});
  }

  const std::vector<int> tree_order = tree_.Traverse();
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
  }
}


/**
 * Inserts 9 ~ 0, since this is the descending order, new node is always the
 * left-most node; right rotations should be performed correclty.
 */
TEST_F(AVLTreeTest, RightRotate) {
  for (int i = 9; i >= 0; --i) {
    tree_.Insert({i, i});
  }

  const std::vector<int> tree_order = tree_.Traverse();
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
  }
}


/**
 *    10     Produces a left-right heavy condition;
 *    /      the order of the nodes should still be correct.
 *   8
 *    \
 *     9
 */
TEST_F(AVLTreeTest, LeftRightRotate) {
  tree_.Insert({10, 10});
  tree_.Insert({8, 8});
  tree_.Insert({9, 9});

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(3, tree_order.size());
  ASSERT_EQ(8, tree_order.at(0));
  ASSERT_EQ(9, tree_order.at(1));
  ASSERT_EQ(10, tree_order.at(2));
}


/**
 *    10     Produces a right-left heavy condition;
 *     \     the order of the nodes should still be correct.
 *     12
 *    /
 *   9
 */
TEST_F(AVLTreeTest, RightLeftRotate) {
  tree_.Insert({10, 10});
  tree_.Insert({12, 12});
  tree_.Insert({11, 11});

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(3, tree_order.size());
  ASSERT_EQ(10, tree_order.at(0));
  ASSERT_EQ(11, tree_order.at(1));
  ASSERT_EQ(12, tree_order.at(2));
}


/**
 * If N elements are inserted, the height of the tree should be smaller than
 * 1.5lg(N) (strictly 1.44 with some constants).
 * NOTE: this is not unser worst case.
 */
TEST_F(AVLTreeTest, BalanceProperly) {
  const int N = 100001;
  /* simply divide into 2 parts, one ascending, another descending */
  for (int i = 0; i < N / 2; ++i) {
    tree_.Insert({i, i});
  }
  for (int i = N - 1; i >= N / 2; --i) {
    tree_.Insert({i, i});
  }

  const std::vector<int> tree_order = tree_.Traverse();
  for (int i = 0; i < N; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
  }
  ASSERT_TRUE(tree_.height() < 1.5 * log2(N));
}


/**
 * Deletes 4 months from the month tree.
 * NOTE: target selection has not special meanings.
 */
TEST_F(AVLTreeTest, Delete_1) {
  month_tree_.Delete(1);
  month_tree_.Delete(4);
  month_tree_.Delete(7);
  month_tree_.Delete(11);

  ASSERT_EQ(nullptr,     month_tree_.Search(1));
  ASSERT_EQ("February",  month_tree_.Search(2)->value());
  ASSERT_EQ("March",     month_tree_.Search(3)->value());
  ASSERT_EQ(nullptr,     month_tree_.Search(4));
  ASSERT_EQ("May",       month_tree_.Search(5)->value());
  ASSERT_EQ("June",      month_tree_.Search(6)->value());
  ASSERT_EQ(nullptr,     month_tree_.Search(7));
  ASSERT_EQ("August",    month_tree_.Search(8)->value());
  ASSERT_EQ("September", month_tree_.Search(9)->value());
  ASSERT_EQ("October",   month_tree_.Search(10)->value());
  ASSERT_EQ(nullptr,     month_tree_.Search(11));
  ASSERT_EQ("December",  month_tree_.Search(12)->value());
}


/**
 * Deletes 2 nodes from 5 nodes.
 * NOTE: target selection has not special meanings.
 */
TEST_F(AVLTreeTest, Delete_2) {
  tree_.Insert({5, 5});
  tree_.Insert({3, 3});
  tree_.Insert({6, 6});
  tree_.Insert({2, 2});
  tree_.Insert({4, 4});

  tree_.Delete(5);
  tree_.Delete(2);

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(3, tree_order.size());
  ASSERT_EQ(3, tree_order.at(0));
  ASSERT_EQ(4, tree_order.at(1));
  ASSERT_EQ(6, tree_order.at(2));
}


/** Inserts 1000 nodes and deletes all nultiple of 7. */
TEST_F(AVLTreeTest, Delete_3) {
  for (int i = 0; i < 1000; ++i) {
    tree_.Insert({i, i});
  }

  for (int i = 7; i < 1000; i += 7) {
    tree_.Delete(i);
  }

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(858, tree_order.size());
  /* should be in ascending order */
  for (int prev = 0, cur = 1; cur < tree_order.size(); ++prev, ++cur) {
    ASSERT_TRUE(tree_order.at(prev) < tree_order.at(cur));
  }
}


/** Inserts 1000 nodes and deletes all of them from the tree. */
TEST_F(AVLTreeTest, DeleteAll) {
  for (int i = 0; i < 1000; ++i) {
    tree_.Insert({i, i});
  }

  for (int i = 0; i < 1000; ++i) {
    tree_.Delete(i);
  }

  ASSERT_EQ(-1 /* null root */, tree_.height());
  ASSERT_TRUE(tree_.Traverse().empty());
}
