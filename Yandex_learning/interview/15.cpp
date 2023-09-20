#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

void print_p(const int& first, const int& second) {
  if (first != second) {
    std::cout << first << "-" << second << std::endl;
  } else {
    std::cout << first << std::endl;
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
  }

  std::sort(vec.begin(), vec.end());

  int first = vec[0], second = vec[0];
  for (int i = 1; i < vec.size(); i++) {
    if (vec[i] != second + 1) {
      print_p(first, second);
      first = vec[i];
    }
    second = vec[i];
  }
  print_p(first, second);

  return 0;
}