#include <gtest/gtest.h>

// sort
#include "ut_isort.hpp"
#include "ut_misort.hpp"
#include "ut_msort.hpp"
#include "ut_ssort.hpp"

// search
#include "ut_lsearch.hpp"

// special
#include "ut_minversions.hpp"

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
