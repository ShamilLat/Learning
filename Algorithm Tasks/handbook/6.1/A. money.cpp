#include <iostream>

void print_coins(int n, int coin) {
  for (int i = 0; i < n; i++) {
    std::cout << " " << coin;
  }
}

void print_set(int cnt10, int cnt5, int cnt1) {
  std::cout << cnt10 + cnt5 + cnt1;
  print_coins(cnt1, 1);
  print_coins(cnt5, 5);
  print_coins(cnt10, 10);
  std::cout << std::endl;
}

int main() {
  int m;
  std::cin >> m;
  int cnt10, cnt5, cnt1;
  cnt10 = m / 10, cnt5 = (m % 10) / 5, cnt1 = m % 5;
  // print_set(cnt10, cnt5, cnt1);
  std::cout << (1 + cnt5 + cnt10) * (cnt10 + 1) << std::endl;

  do {
    int tmp5 = cnt5, tmp1 = cnt1;
    do {
      print_set(cnt10, tmp5, tmp1);
      tmp5--;
      tmp1 += 5;
    } while (tmp5 >= 0);
    cnt10--;
    cnt5 += 2;
  } while (cnt10 >= 0);

  return 0;
}