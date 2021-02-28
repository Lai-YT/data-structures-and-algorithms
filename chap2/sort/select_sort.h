#include <algorithm>
#include <vector>

// Exercise at p.50
void SelectSort(std::vector<int>& a) {
  int n = a.size();
  for (size_t j = 0; j < n - 1; ++j) {
    int min = j;
    for (size_t i = j + 1; i < n; ++i) {
      if (a[i] < a[min]) {
        min = i;
      }
    }
    std::swap(a[j], a[min]);
  }
}

// best case: n-squared
// worst case: n-squared