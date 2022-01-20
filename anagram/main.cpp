#include <fstream>
#include <set>
#include <string>
#include <vector>

#include "src/anagram.hpp"


void ReadWords(std::istream& is, std::vector<std::string>& words);

void WriteAnagramPairs(std::ostream& os,
                       const std::set<std::set<std::string>>& pairs);

void WriteAnagramPair(std::ostream& os,
                      const std::set<std::string>& pair);


/*
 * Reads words from a file and writes the anagram pairs into another file.
 */
int main(int argc, char const *argv[]) {
  std::vector<std::string> words{};
  std::ifstream text_file{"american-english.txt"};
  ReadWords(text_file, words);
  text_file.close();

  std::set<std::set<std::string>> anagram_pairs = GetAnagramPairs(words);

  std::ofstream pair_file{"anagram-pairs.txt"};
  WriteAnagramPairs(pair_file, anagram_pairs);
  pair_file.close();

  return 0;
}


void ReadWords(std::istream& is, std::vector<std::string>& words) {
  words.reserve(10000);  /* we know there're lots of words */
  std::string word{};
  while (is >> word) {
    words.push_back(word);
  }
}


void WriteAnagramPairs(std::ostream& os,
                       const std::set<std::set<std::string>>& pairs) {
  for (const auto& pair : pairs) {
    WriteAnagramPair(os, pair);
  }
}


void WriteAnagramPair(std::ostream& os, const std::set<std::string>& pair) {
  os << "{\n";
  for (const auto& word : pair) {
    os << '\t' << word << '\n';
  }
  os << "}\n";
}
