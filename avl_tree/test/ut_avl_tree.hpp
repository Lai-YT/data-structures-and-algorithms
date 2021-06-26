#include "../src/avl_tree.hpp"

#include <gtest/gtest.h>
#include <string>

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
}
