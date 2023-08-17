#include <iostream>

int main() {
  int64_t a = 0, b = 1;
  int64_t n, m;
  std::cin >> n >> m;

  if (n <= 1) {
    std::cout << n << "\n";
    return 0;
  }

  int64_t period = 0;

  while (period < n - 1) {
    b = (a + b) % m;
    a = (b + m - a) % m;
    period++;
    std::cout << a << " " << b << "\n";
    if (a == 0 && b == 1) {
      break;
    }
  }

  std::cout << "period = " << period << "\n";

  for (int i = 1; i < n % period; i++) {
    // std::cout << "A\n";
    b = (a + b) % m;
    a = (b + m - a) % m;
  }

  std::cout << b << "\n";

  return 0;
}