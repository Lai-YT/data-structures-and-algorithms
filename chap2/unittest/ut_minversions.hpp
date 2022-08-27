#include "../spec/merge_inversions.hpp"

#include <cstdlib>
#include <vector>

#include "../spec/brute_force_inversions.hpp"
#include "../util/random.hpp"

// randomly generate 1000 arrays, each with length 500,
// use BruteForceInversions to test if merge-inversions counts correctly

TEST(MergInverTest, i500) {
  std::srand(std::time(0));
  const int TEST_ARRAY_SIZE = 500;
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> array = RandomArray(TEST_ARRAY_SIZE, 0, TEST_ARRAY_SIZE * 2);
    const int expect_invers = BruteForceInversions(array);

    const int actual_invers = inv::CountInversions(array);

    ASSERT_EQ(expect_invers, actual_invers);
  }
}
