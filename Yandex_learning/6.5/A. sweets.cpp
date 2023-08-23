#include <cmath>
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  std::cout << ((int)std::sqrt(1 + 8 * (int64_t)n) - 1) / 2 << std::endl;

  return 0;
}
