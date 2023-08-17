#include <iostream>

int main() {
  int a, b;
  std::cin >> a >> b;
  while (a && b) {
    if (a > b) {
      a %= b;
    } else {
      b %= a;
    }
  }
  std::cout << a + b << std::endl;
  return 0;
}