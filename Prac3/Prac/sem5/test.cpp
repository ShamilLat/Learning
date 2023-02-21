#include <iostream>

int main()
{
  double x1 = 2, x2 = 1, a1, a2, a = 1.0 / 8;
  std::cout << "a = " << a << std::endl;
  for (int i = 2; i < 10; i++) {
    a1 = x1 - a * (8 * x1 + x2);
    a2 = x2 - a * (2 * x2 + x1);
    std::cout << i << " a1 = " << a1 << " a2 = " << a2 << std::endl;
    x1 = a1;
    x2 = a2;
  }
}

