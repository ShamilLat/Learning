#include <iostream>

int main() {
  int64_t a = 0, b = 1;
  int n;
  std::cin >> n;
  for (int i = 1; i < n; i++) {
    b = a + b;
    a = b - a;
  }
  if (n >= 1) {
    std::cout << b << "\n";
  }
  if (n == 0) {
    std::cout << a << "\n";
  }
  return 0;
}