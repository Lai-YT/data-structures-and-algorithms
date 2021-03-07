#ifndef UT_LSEARCH_H_
#define UT_LSEARCH_H_

#include "../srch/linear_search.h"

#include <cstdlib>
#include <vector>

#include "../util/random.h"

TEST(LsearchTest, Found) {
  std::srand(std::time(0));
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    int v_inx = Random(0, 500);
    int v = 1000;
    a[v_inx] = v;
    ASSERT_EQ(v_inx, LinearSearch(a, v));
  }
}

TEST(LsearchTest, NotFound) {
  std::srand(std::time(0));
  for (size_t i = 0; i < 1000; ++i) {
    std::vector<int> a = RandomArray(500, 0, 1000);
    int v = 1000;
    ASSERT_EQ(a.size(), LinearSearch(a, v));
  }
}

#endif /* end of include guard: UT_LSEARCH_H_ */
