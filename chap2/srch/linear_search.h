#include <vector>

// Exercise at p.22
// return the last index + 1 of thr array if target not found

int LinearSearch(std::vector<int> a, int v) {
  int i = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == v) {
      return i;
    }
  }
  return a.size();
}
