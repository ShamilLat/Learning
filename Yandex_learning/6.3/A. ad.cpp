#include <algorithm>
#include <iostream>

int main() {
  int n;
  std::cin >> n;
  int p[n], c[n];
  for (int i = 0; i < n; i++) {
    std::cin >> c[i];
  }
  for (int i = 0; i < n; i++) {
    std::cin >> p[i];
  }
  std::sort(c, c + n);
  std::sort(p, p + n);

  int res = 0;
  for (int i = 0; i < n; i++) {
    res += c[i] * p[i];
  }
  std::cout << res << std::endl;
}