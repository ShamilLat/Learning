#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> points(n);
  for (int i = 0; i < n; i++) {
    std::cin >> points[i].first >> points[i].second;
  }

  std::sort(points.begin(), points.end());

  for (auto& i : points) {
    std::cout << i.first << " " << i.second << "\n";
  }

  return 0;
}