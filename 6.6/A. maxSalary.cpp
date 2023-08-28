#include <algorithm>
#include <iostream>
#include <vector>

bool isBetter(int a, int b) {
  int a_size = 1, b_size = 1;
  while (a / a_size) {
    a_size *= 10;
  }
  while (b / b_size) {
    b_size *= 10;
  }
  return (a * b_size + b) > (b * a_size + a);
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> numbers(n);
  for (int i = 0; i < n; i++) {
    std::cin >> numbers[i];
  }

  std::sort(numbers.begin(), numbers.end(), isBetter);

  for (int i = 0; i < n; i++) {
    std::cout << numbers[i];
  }
  std::cout << std::endl;

  return 0;
}