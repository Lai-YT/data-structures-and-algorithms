#ifndef UT_ANAGRAM_HPP_
#define UT_ANAGRAM_HPP_

#include "../anagram.hpp"

#include <cstdint>
#include <gtest/gtest.h>
#include <string>


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


#endif /* end of include guard: UT_ANAGRAM_HPP_ */
