#ifndef ANAGRAM_HPP_
#define ANAGRAM_HPP_

#include <cctype>
#include <cstdint>
#include <string>

/*
 * Non-alphabets are ignored.
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


#endif /* end of include guard: ANAGRAM_HPP_ */
