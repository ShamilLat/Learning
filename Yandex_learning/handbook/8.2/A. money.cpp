#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int money;
  std::cin >> money;
  std::vector<int> money_table(money + 1, 0x7fffffff);
  money_table[0] = 0;

  std::vector<int> coins = {1, 3, 4};
  for (int i = 1; i <= money; i++) {
    for (auto& coin : coins) {
      if (coin <= money) {
        money_table[i] = std::min(money_table[i], money_table[i - coin] + 1);
      }
    }
  }
  std::cout << money_table[money] << std::endl;
  return 0;
}