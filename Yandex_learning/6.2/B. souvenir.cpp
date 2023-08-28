#include <iostream>

int main() {
  int n, s;
  std::cin >> n >> s;
  int p[n];
  for (int i = 0; i < n; i++) {
    std::cin >> p[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n; j++) {
      if (p[j - 1] > p[j]) {
        std::swap(p[j - 1], p[j]);
      }
    }
  }
  //   for (int i = 0; i < n; i++) {
  //     std::cout << p[i] << " ";
  //   }
  //   std::cout << std::endl;

  int check = 0;
  int cnt = 0, i = 0;
  while (check <= s) {
    if (p[i] + check <= s) {
      check += p[i];
      cnt++;
      i++;
    } else {
      break;
    }
  }
  std::cout << cnt << std::endl;
}