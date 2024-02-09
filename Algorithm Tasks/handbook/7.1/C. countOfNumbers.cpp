#include <algorithm>
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
  int num;
  for (int i = 0; i < m; i++) {
    if (i) {
      std::cout << " ";
    }
    std::cin >> num;
    int min_poz = -1, max_poz = -1;
    int minIndex = 0, maxIndex = n - 1, midIndex;
    while (maxIndex >= minIndex) {
      midIndex = (maxIndex + minIndex) / 2;
      if (num == a[midIndex]) {
        // std::cout << "current pos = " << midIndex << std::endl;
        maxIndex = midIndex - 1;
        min_poz = midIndex;
      } else if (num < a[midIndex]) {
        maxIndex = midIndex - 1;
      } else if (num > a[midIndex]) {
        minIndex = midIndex + 1;
      }
    }
    if (min_poz != -1) {
      minIndex = 0, maxIndex = n - 1;
      while (maxIndex >= minIndex) {
        midIndex = (maxIndex + minIndex) / 2;
        if (num == a[midIndex]) {
          minIndex = midIndex + 1;
          max_poz = midIndex;
        } else if (num < a[midIndex]) {
          maxIndex = midIndex - 1;
        } else if (num > a[midIndex]) {
          minIndex = midIndex + 1;
        }
      }
    } else {
      std::cout << 0;
      continue;
    }

    std::cout << max_poz - min_poz + 1;
  }
  std::cout << std::endl;
  return 0;
}