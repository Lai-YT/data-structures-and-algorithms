#ifndef MEM_DEBUG
  #define MEM_DEBUG
#endif

#include <gtest/gtest.h>

#include "ut_tree_node.hpp"
#include "ut_avl_tree.hpp"


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
