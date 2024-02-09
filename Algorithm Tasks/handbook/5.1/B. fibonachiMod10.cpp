#include <iostream>

int main() {
  int64_t a = 0, b = 1;
  int64_t n;
  std::cin >> n;

  for (int64_t i = 1; i < n; i++) {
    b = (a + b) % 10;
    a = (b + 10 - a) % 10;
  }
  if (n) {
    std::cout << b << "\n";
  } else {
    std::cout << a << "\n";
  }
  return 0;
}