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
  std::string stop_anag{"post"};
  
  uint64_t hash_code = 67 * 71 * 47 * 53;
  ASSERT_EQ(hash_code, HashWord(stop_low));
  ASSERT_EQ(hash_code, HashWord(stop_up));
  ASSERT_EQ(hash_code, HashWord(stop_punch));
  ASSERT_TRUE(HashWord(stop_low) == HashWord(stop_anag));
}


#endif /* end of include guard: UT_ANAGRAM_HPP_ */
