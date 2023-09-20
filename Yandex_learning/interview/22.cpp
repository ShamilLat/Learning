#include <iostream>
#include <ostream>
#include <unordered_map>
#include <unordered_set>

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
  int x, y;
  for (int i = 0; i < n; i++) {
    std::cin >> x >> y;
    if (!points_x.contains(x)) {
      points_x.insert({x, std::unordered_set<int>()});
    }
    points_x[x].insert(y);
    if (!points_y.contains(y)) {
      points_y.insert({y, std::unordered_set<int>()});
    }
    points_y[y].insert(x);
  }

  std::cout << points_x << std::endl;
  std::cout << points_y << std::endl;
}