#ifndef TEST_UT_ANAGRAM_HPP_
#define TEST_UT_ANAGRAM_HPP_

#include "../src/anagram.hpp"

#include <cstdint>  /* uint64_t */
#include <gtest/gtest.h>
#include <set>
#include <string>
#include <vector>


TEST(AnagramTest, HashWord) {
  std::string stop_low{"stop"};
  std::string stop_up{"STOP"};
  std::string stop_punch{"sT*O/p "};

  uint64_t hash_code = 67 * 71 * 47 * 53;
  ASSERT_EQ(hash_code, HashWord(stop_low));
  ASSERT_EQ(hash_code, HashWord(stop_up));
  ASSERT_EQ(hash_code, HashWord(stop_punch));
}


TEST(AnagramTest, IsAnagramNormalWord) {
  ASSERT_TRUE(IsAnagram("stop", "post"));
  ASSERT_TRUE(IsAnagram("tachymetric", "mccarthyite"));

  ASSERT_FALSE(IsAnagram("post", "top"));
  ASSERT_FALSE(IsAnagram("pott", "top"));
  ASSERT_FALSE(IsAnagram("topss", "postt"));
}


TEST(AnagramTest, IsAnagramNonAlpha) {
  ASSERT_TRUE(IsAnagram("sTo*p", "p ost-"));
  ASSERT_TRUE(IsAnagram("ta!ch25yme]Tric+", "mcca\\ rt(HYite"));

  ASSERT_FALSE(IsAnagram("Post%", "t@Op"));
  ASSERT_FALSE(IsAnagram("po$tt", "To_p"));
  ASSERT_FALSE(IsAnagram("toP**Ss", "po[stt"));
}


TEST(AnagramTest, GetAnagramPairsTwo) {
  std::vector<std::string> words{
    "proudest", "stop", "pots", "tops", "sprouted",
  };
  std::set<std::set<std::string>> anagram_pairs{
    {"stop", "pots", "tops"}, {"proudest", "sprouted"},
  };

  ASSERT_EQ(anagram_pairs, GetAnagramPairs(words));
}


TEST(AnagramTest, GetAnagramPairsThree) {
  std::vector<std::string> words{
    "proudest", "stop", "pots", "tops",
    "Semolina", "is no meal.", "sprouted",
  };
  std::set<std::set<std::string>> anagram_pairs{
    {"stop", "pots", "tops"}, {"proudest", "sprouted"},
    {"Semolina", "is no meal."},
  };

  ASSERT_EQ(anagram_pairs, GetAnagramPairs(words));
}


#endif /* end of include guard: TEST_UT_ANAGRAM_HPP_ */
