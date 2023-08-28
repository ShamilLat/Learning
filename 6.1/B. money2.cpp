#include <iostream>

void print_coins(int n, int coin, int& check) {
  for (int i = 0; i < n; i++) {
    if (check) {
      check = 0;
      std::cout << coin;
    } else {
      std::cout << " " << coin;
    }
  }
}

int main() {
  int a[] = {1, 5, 10, 20, 50};
  int cnt[5] = {0};
  int n, sum = 0;
  std::cin >> n;
  for (int i = 4; i >= 0; i--) {
    cnt[i] = n / a[i];
    sum += cnt[i];
    n %= a[i];
  }

  std::cout << sum << std::endl;
  int check = 1;
  for (int i = 4; i >= 0; i--) {
    if (cnt[i] > 0) {
      print_coins(cnt[i], a[i], check);
    }
  }
  std::cout << std::endl;

  return 0;
}