#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

bool f(const std::vector<int>& vec) {
  int min = 0x7fffffff;
  int max = 0x80000000;
  std::unordered_set<int> p;

  for (int i = 0; i < vec.size(); i++) {
    min = std::min(vec[i], min);
    max = std::max(vec[i], max);

    p.insert(vec[i]);
  }

  int dist = max + min;
  for (int i = 0; i < vec.size(); i++) {
    if (!p.contains(dist - vec[i])) {
      return false;
    }
  }

  return true;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
  }

  std::cout << n << " " << f(vec) << std::endl;
}