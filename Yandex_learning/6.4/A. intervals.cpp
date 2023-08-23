#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> segments(n);
  for (int i = 0; i < n; i++) {
    std::cin >> segments[i].first >> segments[i].second;
  }

  std::sort(segments.begin(), segments.end(),
            [](auto& left, auto& right) { return left.second < right.second; });

  int current_min = segments[0].second;
  std::vector<int> points = {current_min};
  for (int i = 1; i < n; i++) {
    if (segments[i].first > current_min) {
      current_min = segments[i].second;
      points.push_back(current_min);
    }
  }

  std::cout << points.size() << std::endl;
  int check = 0;
  for (auto& i : points) {
    if (check) {
      std::cout << " ";
    }
    std::cout << i;
    check = 1;
  }
  std::cout << std::endl;

  return 0;
}