#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  int q;

  for (int i = 0; i < m; i++) {
    std::cin >> q;
    int maxIndex = n - 1, minIndex = 0, midIndex;
    int result = -1;
    while (maxIndex >= minIndex) {
      midIndex = (maxIndex + minIndex) / 2;
      if (q == a[midIndex]) {
        result = midIndex;
        break;
      } else if (q < a[midIndex]) {
        maxIndex = midIndex - 1;
      } else if (q > a[midIndex]) {
        minIndex = midIndex + 1;
      }
    }
    std::cout << result << std::endl;
  }

  return 0;
}