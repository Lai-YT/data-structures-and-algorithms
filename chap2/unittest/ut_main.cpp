#include <gtest/gtest.h>

// sort
#include "ut_isort.h"
#include "ut_misort.h"
#include "ut_msort.h"
#include "ut_ssort.h"

// test
#include "ut_lsearch.h"

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
