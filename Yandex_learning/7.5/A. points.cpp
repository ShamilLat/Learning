#include <stdint.h>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

double distance(std::pair<int, int>& p1, std::pair<int, int>& p2) {
  return std::sqrt(
      (int64_t)(p1.first - p2.first) * (int64_t)(p1.first - p2.first) +
      (int64_t)(p1.second - p2.second) * (int64_t)(p1.second - p2.second));
}

double findDistance(std::vector<std::pair<int, int>>& points) {
  std::sort(points.begin(), points.end());

  if (points.size() <= 1) {
    return 0x7fffffff;
  } else if (points.size() == 2) {
    return distance(points[0], points[1]);
  }

  auto mid = (points.end() - points.begin()) / 2;
  std::vector<std::pair<int, int>> left(points.begin(), points.begin() + mid);
  std::vector<std::pair<int, int>> right(points.begin() + mid, points.end());

  double min_d = std::min(findDistance(left), findDistance(right));
  double mid_x = (double)(left[left.size() - 1].first + right[0].first) / 2;

  auto it_end = left.end() - 1, it_begin = right.begin();
  std::vector<std::pair<int, int>> y_vec;
  while (it_end >= left.begin() && it_end->first >= mid_x - min_d) {
    y_vec.push_back(*it_end);
    it_end--;
  }
  while (it_begin < right.end() && it_begin->first <= mid_x + min_d) {
    y_vec.push_back(*it_begin);
    it_begin++;
  }

  std::sort(y_vec.begin(), y_vec.end(),
            [](auto& a, auto& b) { return a.second < b.second; });

  double new_min_d = min_d;
  for (auto& i : y_vec) {
    for (int j = 1; j <= 7; j++) {
      new_min_d = std::min(distance(i, *(&i + j)), new_min_d);
    }
  }

  return new_min_d;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> points(n);
  for (int i = 0; i < n; i++) {
    std::cin >> points[i].first >> points[i].second;
  }

  std::cout << std::fixed << std::setprecision(6) << findDistance(points)
            << std::endl;

  return 0;
}