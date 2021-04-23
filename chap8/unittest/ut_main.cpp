#include <gtest/gtest.h>

#include "ut_bucket_sort.hpp"
#include "ut_counting_sort.hpp"
#include "ut_radix_sort.hpp"

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
