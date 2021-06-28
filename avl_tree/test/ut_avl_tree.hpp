#include "../src/avl_tree.hpp"

#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include <iostream>


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
  AVLTree<int> tree_;
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

  ASSERT_TRUE(month_tree_.Search(13) == nullptr);
}

TEST_F(AVLTreeTest, LeftRotate) {
  for (int i = 0; i < 10; ++i) {
    tree_.Insert(i, i);
  }
  const std::vector<int> tree_order = tree_.Traverse();
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
  }
}

TEST_F(AVLTreeTest, RightRotate) {
  for (int i = 9; i >= 0; --i) {
    tree_.Insert(i, i);
  }
  const std::vector<int> tree_order = tree_.Traverse();
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
  }
}

TEST_F(AVLTreeTest, LeftRightRotate) {
  tree_.Insert(10, 10);
  tree_.Insert(8, 8);
  tree_.Insert(9, 9);

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(3, tree_order.size());

  ASSERT_EQ(8, tree_order.at(0));
  ASSERT_EQ(9, tree_order.at(1));
  ASSERT_EQ(10, tree_order.at(2));
}

TEST_F(AVLTreeTest, RightLeftRotate) {
  tree_.Insert(10, 10);
  tree_.Insert(12, 12);
  tree_.Insert(11, 11);

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(3, tree_order.size());

  ASSERT_EQ(10, tree_order.at(0));
  ASSERT_EQ(11, tree_order.at(1));
  ASSERT_EQ(12, tree_order.at(2));
}

TEST_F(AVLTreeTest, Height) {
  for (int i = 0; i < 100000; ++i) {
    tree_.Insert(i, i);
  }
  const std::vector<int> tree_order = tree_.Traverse();
  for (int i = 0; i < 100000; ++i) {
    ASSERT_EQ(i, tree_order.at(i));
  }
  // Should be 1.44, but to neglect other coefficients.
  ASSERT_TRUE(tree_.Height() < 1.5 * log2(100000));
}

TEST_F(AVLTreeTest, Delete_1) {
  month_tree_.Delete(1);
  month_tree_.Delete(4);
  month_tree_.Delete(7);
  month_tree_.Delete(11);

  ASSERT_EQ(nullptr,     month_tree_.Search(1));
  ASSERT_EQ("February",  month_tree_.Search(2)->data);
  ASSERT_EQ("March",     month_tree_.Search(3)->data);
  ASSERT_EQ(nullptr,     month_tree_.Search(4));
  ASSERT_EQ("May",       month_tree_.Search(5)->data);
  ASSERT_EQ("June",      month_tree_.Search(6)->data);
  ASSERT_EQ(nullptr,     month_tree_.Search(7));
  ASSERT_EQ("August",    month_tree_.Search(8)->data);
  ASSERT_EQ("September", month_tree_.Search(9)->data);
  ASSERT_EQ("October",   month_tree_.Search(10)->data);
  ASSERT_EQ(nullptr,     month_tree_.Search(11));
  ASSERT_EQ("December",  month_tree_.Search(12)->data);
}

TEST_F(AVLTreeTest, Delete_2) {
  tree_.Insert(5, 5);
  tree_.Insert(3, 3);
  tree_.Insert(6, 6);
  tree_.Insert(2, 2);
  tree_.Insert(4, 4);

  tree_.Delete(5);

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(4, tree_order.size());

  ASSERT_EQ(2, tree_order.at(0));
  ASSERT_EQ(3, tree_order.at(1));
  ASSERT_EQ(4, tree_order.at(2));
  ASSERT_EQ(6, tree_order.at(3));
}

TEST_F(AVLTreeTest, Delete_3) {
  tree_.Insert(5, 5);
  tree_.Insert(3, 3);
  tree_.Insert(6, 6);
  tree_.Insert(2, 2);

  tree_.Delete(5);

  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(3, tree_order.size());

  ASSERT_EQ(2, tree_order.at(0));
  ASSERT_EQ(3, tree_order.at(1));
  ASSERT_EQ(6, tree_order.at(2));
}

TEST_F(AVLTreeTest, Delete_4) {
  for (int i = 0; i < 1000; ++i) {
    tree_.Insert(i, i);
  }
  const std::vector<int> tree_order_before_delete = tree_.Traverse();
  for (int prev = 0, cur = 1; cur < tree_order_before_delete.size(); ++prev, ++cur) {
    ASSERT_TRUE(tree_order_before_delete.at(prev) < tree_order_before_delete.at(cur));
  }
  for (int i = 7; i < 1000; i += 7) {
    tree_.Delete(i);
  }
  const std::vector<int> tree_order = tree_.Traverse();
  ASSERT_EQ(858, tree_order.size());

  bool fail_flag = false;
  for (int prev = 0, cur = 1; cur < tree_order.size(); ++prev, ++cur) {
    if (tree_order.at(prev) > tree_order.at(cur)) {
      fail_flag = true;
      std::cout << "at(" << prev << ") = " << tree_order.at(prev) << ", "
                << "at(" << cur  << ") = " << tree_order.at(cur)  << '\n';
    }
  }
  ASSERT_FALSE(fail_flag);
  // int count = 0;
  // for (auto i : tree_order) {
  //   std::cout << i;
  //   if (++count % 10) {
  //     std::cout << ' ';
  //   } else {
  //     std::cout << '\n';
  //   }
  // }
  // std::cout << '\n';
}
