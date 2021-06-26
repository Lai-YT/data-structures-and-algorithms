#include "../src/avl_tree.hpp"

#include <gtest/gtest.h>
#include <string>
#include <iostream>

//         6
//   3            9
// 1   4       8     12
//  2   5     7    10
//                  11
class AVLTreeTest : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_EQ(0, TreeNode<std::string>::count);
    month_tree_.Insert("June", 6);
    month_tree_.Insert("March", 3);
    month_tree_.Insert("September", 9);
    month_tree_.Insert("January", 1);
    month_tree_.Insert("December", 12);
    month_tree_.Insert("October", 10);
    month_tree_.Insert("April", 4);
    month_tree_.Insert("August", 8);
    month_tree_.Insert("February", 2);
    month_tree_.Insert("November", 11);
    month_tree_.Insert("May", 5);
    month_tree_.Insert("July", 7);
  }

  AVLTree<std::string> month_tree_;
};


TEST_F(AVLTreeTest, Insert) {
  month_tree_.Insert("updated_Oct", 10);

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
  ASSERT_EQ("updated_Oct",   months.at(9));
  ASSERT_EQ("November",  months.at(10));
  ASSERT_EQ("December",  months.at(11));
}

TEST_F(AVLTreeTest, Search) {
  ASSERT_EQ("January",   month_tree_.Search(1)->data);
  ASSERT_EQ("February",  month_tree_.Search(2)->data);
  ASSERT_EQ("March",     month_tree_.Search(3)->data);
  ASSERT_EQ("April",     month_tree_.Search(4)->data);
  ASSERT_EQ("May",       month_tree_.Search(5)->data);
  ASSERT_EQ("June",      month_tree_.Search(6)->data);
  ASSERT_EQ("July",      month_tree_.Search(7)->data);
  ASSERT_EQ("August",    month_tree_.Search(8)->data);
  ASSERT_EQ("September", month_tree_.Search(9)->data);
  ASSERT_EQ("October",   month_tree_.Search(10)->data);
  ASSERT_EQ("November",  month_tree_.Search(11)->data);
  ASSERT_EQ("December",  month_tree_.Search(12)->data);

  ASSERT_EQ("June", month_tree_.Search(3)->parent->data);
  ASSERT_EQ("June", month_tree_.Search(9)->parent->data);
  ASSERT_EQ("March", month_tree_.Search(1)->parent->data);
}

TEST_F(AVLTreeTest, Height) {
  ASSERT_EQ(0, month_tree_.Search(2)->height);
  ASSERT_EQ(0, month_tree_.Search(5)->height);
  ASSERT_EQ(0, month_tree_.Search(7)->height);
  ASSERT_EQ(0, month_tree_.Search(11)->height);
  ASSERT_EQ(1, month_tree_.Search(1)->height);
  ASSERT_EQ(1, month_tree_.Search(4)->height);
  ASSERT_EQ(1, month_tree_.Search(8)->height);
  ASSERT_EQ(1, month_tree_.Search(10)->height);
  ASSERT_EQ(2, month_tree_.Search(12)->height);
  ASSERT_EQ(2, month_tree_.Search(3)->height);
  ASSERT_EQ(3, month_tree_.Search(9)->height);
  ASSERT_EQ(4, month_tree_.Search(6)->height);
}

TEST_F(AVLTreeTest, LeftRotate) {
  AVLTree<int> tree;
  for (int i = 0; i < 10; ++i) {
    tree.Insert(i, i);
  }
  const std::vector<int> tree_order = tree.Traverse();
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
  }
}

TEST_F(AVLTreeTest, RightRotate) {
  AVLTree<int> tree;
  for (int i = 9; i >= 0; --i) {
    tree.Insert(i, i);
  }
  const std::vector<int> tree_order = tree.Traverse();
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
    std::cout << tree.Search(i)->height << '\n';
  }
}

TEST_F(AVLTreeTest, LeftRightRotate) {
  AVLTree<int> tree;
  tree.Insert(10, 10);
  tree.Insert(8, 8);
  tree.Insert(9, 9);
  const std::vector<int> tree_order = tree.Traverse();
  ASSERT_EQ(8, tree_order.at(0));
  ASSERT_EQ(9, tree_order.at(1));
  ASSERT_EQ(10, tree_order.at(2));
}

TEST_F(AVLTreeTest, RightLeftRotate) {
  AVLTree<int> tree;
  tree.Insert(10, 10);
  tree.Insert(12, 12);
  tree.Insert(11, 11);
  const std::vector<int> tree_order = tree.Traverse();
  ASSERT_EQ(10, tree_order.at(0));
  ASSERT_EQ(11, tree_order.at(1));
  ASSERT_EQ(12, tree_order.at(2));
}
