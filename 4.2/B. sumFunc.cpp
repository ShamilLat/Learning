#include <iostream>

void sum(int* bigger, int* smaller, int big_size, int small_size) {
  std::cout << big_size << std::endl;
  for (int i = 0; i <= small_size; i++) {
    bigger[i + (big_size - small_size)] += smaller[i];
  }
  for (int i = 0; i <= big_size; i++) {
    std::cout << bigger[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  int n, m;
  std::cin >> n;
  int a[n + 1];
  for (int i = 0; i <= n; i++) {
    std::cin >> a[i];
  }
  std::cin >> m;
  int b[m + 1];
  for (int i = 0; i <= m; i++) {
    std::cin >> b[i];
  }
  if (n > m) {
    sum(a, b, n, m);
  } else {
    sum(b, a, m, n);
  }
  return 0;
}