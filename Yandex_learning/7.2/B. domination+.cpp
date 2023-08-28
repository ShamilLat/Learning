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
  int dominations_count = 0;
  for (auto& i : cnt) {
    if (i.second > n / 4) {
      dominations_count++;
    }
  }
  std::cout << ((dominations_count >= 3) ? 1 : 0) << std::endl;
  return 0;
}