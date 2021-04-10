#include "../spec/merge_inversions.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "../spec/brute_force_inversions.hpp"
#include "../util/random.hpp"

// randomly generate 1000 arrays, each with length 500,
// use BruteForceInversions to test if merge-inversions counts correctly

TEST(MergInverTest, i500) {
  std::srand(std::time(0));
  for (size_t i = 0; i < 1; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    int expect_invers = 0, act_invers = 0;
    expect_invers = BruteForceInversions(a);
    act_invers = CountInversions(a, 0, a.size() - 1);
    ASSERT_EQ(expect_invers, act_invers);
  }
}
