#include <iostream>
#include <sstream>
#include <string>

int main() {
  int n;
  std::string a, b;
  std::cin >> n;
  std::cin >> a >> b;
  std::stringstream ss;

  for (int i = 0; i < n; i++) {
    ss << a[i] << b[i];
  }
  std::cout << ss.str() << std::endl;

  return 0;
}