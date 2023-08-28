#include <iostream>

int main() {
  int r, c;
  std::cin >> r >> c;
  std::cout << r * c - (r / 3 + ((r % 3 > 0) ? 1 : 0)) *
                           (c / 3 + ((c % 3 > 0) ? 1 : 0))
            << std::endl;
}