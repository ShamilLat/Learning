#include <iostream>
#include <ostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename Type>
std::ostream& operator<<(std::ostream& out, std::unordered_set<Type>& values) {
  for (auto& it : values) {
    out << it << " ";
  }
  return out;
}

template <typename Type>
std::ostream& operator<<(std::ostream& out,
                         std::unordered_map<int, Type>& points) {
  for (auto& it : points) {
    out << it.first << " ( " << it.second << ")\n";
  }
  return out;
}

int main() {
  std::unordered_map<int, std::unordered_set<int>> points_x;
  std::unordered_map<int, std::unordered_set<int>> points_y;
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> points(n);
  int x, y;
  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    points[i] = {x, y};
    if (!points_x.contains(x)) {
      points_x.insert({x, std::unordered_set<int>()});
    }
    points_x[x].insert(y);
    if (!points_y.contains(y)) {
      points_y.insert({y, std::unordered_set<int>()});
    }
    points_y[y].insert(x);
  }

  int cnt = 0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (points[i].first == points[j].first ||
          points[i].second == points[j].second) {
        continue;
      } else {
        if (points_x[points[i].first].contains(points[j].second) &&
            points_x[points[j].first].contains(points[i].second)) {
          cnt++;
        }
      }
    }
  }
  cnt /= 2;
  std::cout << cnt << "\n";

  // std::cout << points_x << std::endl;
  // std::cout << points_y << std::endl;
}