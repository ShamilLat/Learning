#include <algorithm>
#include <iostream>
#include <vector>

double distance() {}

double FindDistance(std::vector<int>& points) {
  if (points.size() <= 1) {
    return 0;
  } else if (points.size() == 2) {
    return 1;
  }
  auto mid = (points.end() - points.begin()) / 2;
  std::vector<int> left(points.begin(), points.begin() + mid);
  std::vector<int> right(points.begin() + mid, points.end());

  FindDistance(left);
  FindDistance(right);
}

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