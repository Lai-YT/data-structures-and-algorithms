#include <vector>

// pseudocode at p.41
void insertSort(std::vector<int>& a) {
  for (size_t j = 1; j < a.size(); ++j) {
    int key = a[j];
    int i = j - 1;
    while (i >= 0 && a[i] > key) {
      a[i + 1] = a[i];
      i = i - 1;
    }
    a[i + 1] = key;
  }
}
