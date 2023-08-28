#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <vector>

int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> points(n);
  for (int i = 0; i < n; i++) {
    std::cin >> points[i];
  }

  std::sort(points.begin(), points.end());

  std::vector<int> d;
  int cnt = 0;
  for (int i = 1; i < n; i++) {
    if (points[i] - points[i - 1]) {
      d.push_back(points[i] - points[i - 1]);
      cnt++;
    }
  }

  std::sort(d.begin(), d.end());

  int sum = 0;
  for (int i = 0; i < cnt - k + 1; i++) {
    sum += d[i];
  }
  std::cout << sum << std::endl;

  return 0;
}