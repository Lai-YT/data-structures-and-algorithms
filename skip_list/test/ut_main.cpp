#ifndef MEM_DEBUG
  #define MEM_DEBUG
#endif

#include "ut_skip_node.hpp"
#include "ut_skip_list.hpp"

#include <gtest/gtest.h>


int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
