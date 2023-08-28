#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, l;
  std::cin >> n >> l;
  std::vector<int> points(n);
  for (int i = 0; i < n; i++) {
    std::cin >> points[i];
  }

  std::sort(points.begin(), points.end());

  int cnt = 1, current_max = points[0] + l;
  for (int i = 1; i < n; i++) {
    if (points[i] > current_max) {
      current_max = points[i] + l;
      cnt++;
    }
  }
  std::cout << cnt << std::endl;

  return 0;
}