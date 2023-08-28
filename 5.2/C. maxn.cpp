#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int a = 0, b = 1;
  while (a <= n && b <= n) {
    b += a;
    a = b - a;
  }
  if (!n) {
    b = 0;
  }
  std::cout << b - a << " " << a << "\n";
}