#include <iostream>
#include <unordered_map>

int main() {
  int n;
  std::cin >> n;
  std::unordered_map<int, int> cnt;
  int num;
  for (int i = 0; i < n; i++) {
    std::cin >> num;
    if (!cnt.contains(num)) {
      cnt[num] = 1;
    } else {
      cnt[num]++;
    }
  }
  for (auto& i : cnt) {
    if (i.second > n / 2) {
      std::cout << 1 << std::endl;
      return 0;
    }
  }
  std::cout << 0 << std::endl;
  return 0;
}