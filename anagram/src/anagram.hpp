#ifndef ANAGRAM_HPP_
#define ANAGRAM_HPP_

#include <cctype>  /* isalpha, tolower */
#include <cstdint> /* uint8_t, uint64_t */
#include <memory>  /* move */
#include <string>
#include <set>
#include <unordered_map>
#include <vector>


/*
 * Uses prime factorization as the key. Non-alphabets are ignored.
 * Note that I did not handle the overflow problem.
 */
uint64_t HashWord(const std::string& word) {
  /* map alphabet to prime by index, e.g., b -> CHAR_TO_PRIME[1] */
  static const uint8_t CHAR_TO_PRIME[26] = {
      2  /* a */, 3  /* b */, 5  /* c */, 7  /* d */, 11 /* e */, 13 /* f */,
      17 /* g */, 19 /* h */, 23 /* i */, 29 /* j */, 31 /* k */, 37 /* l */,
      41 /* m */, 43 /* n */, 47 /* o */, 53 /* p */, 59 /* q */, 61 /* r */,
      67 /* s */, 71 /* t */, 73 /* u */, 79 /* v */, 83 /* w */, 89 /* x */,
      97 /* y */, 101/* z */,
  };
  uint64_t hash_code = 1;
  for (const char c : word) {
    if (!isalpha(c)) {
      continue;
    }
    /* Lower and upper cases are treated as the same. */
    hash_code *= CHAR_TO_PRIME[tolower(c) % 97 /* a */];
  }
  return hash_code;
}


/*
 * Returns true if the 2 words are anagrams.
 */
bool IsAnagram(const std::string& a, const std::string& b) {
  return HashWord(a) == HashWord(b);
}


/*
 * The order of the pairs are unspecified.
 */
std::set<std::set<std::string>>
    GetAnagramPairs(const std::vector<std::string>& words) {
  /* customize hash function with HashWord */
  static auto word_hash =
    [](const std::string& word) -> uint64_t {
      return HashWord(word);
    };
  /* Two words with the same hash code are treated as the same,
    not a collision. */
  static auto word_equal =
    [](const std::string& a, const std::string& b) -> bool {
      return HashWord(a) == HashWord(b);
    };

  std::unordered_map<std::string, std::set<std::string>,
                     decltype(word_hash), decltype(word_equal)>
    factor_and_anagrams{26, word_hash, word_equal};
  /* group each anagram pair */
  for (const std::string& word : words) {
    const auto factor_iter = factor_and_anagrams.find(word);
    if (factor_iter != factor_and_anagrams.cend()) {
      /* already contains, add in */
      factor_iter->second.insert(word);
    } else {
      factor_and_anagrams.emplace(word, std::set<std::string>{word});
    }
  }
  /* collect all anagram pairs together */
  std::set<std::set<std::string>> anagram_pairs{};
  for (const auto& fact_and_ana : factor_and_anagrams) {
    anagram_pairs.insert(std::move(fact_and_ana.second));
  }

  return anagram_pairs;
}


#endif /* end of include guard: ANAGRAM_HPP_ */
