#include <iostream>

int main() {
  int a, b;
  std::cin >> a >> b;
  int cpy_a = a, cpy_b = b, d = 0;
  while (a && b) {
    if (a > b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  d = a + b;
  std::cout << (int64_t)cpy_a * (int64_t)cpy_b / d << std::endl;

  return 0;
}