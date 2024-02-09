#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  std::string s;
  std::cin >> s;

  std::unordered_map<char, int> count_symbols;

  for (auto& i : s) {
    count_symbols[i] = 0;
  }

  int it_left = 0, it_right = 0;
  int cnt = 0, total_symbols = count_symbols.size();
  int min_size = s.size(), min_left = 0, min_right = s.size() - 1;

  count_symbols[s[0]]++;
  cnt = 1;
  bool check = 1;

  while (check && it_right < s.size()) {
    check = 0;
    while (cnt != total_symbols && it_right < s.size() - 1) {
      check = 1;
      cnt += (count_symbols[s[++it_right]]++ ? 0 : 1);
    }
    while (cnt == total_symbols && it_left <= it_right) {
      if (min_size > it_right - it_left) {
        min_size = it_right - it_left;
        min_right = it_right;
        min_left = it_left;
      }
      check = 1;
      cnt -= (--count_symbols[s[it_left++]] ? 0 : 1);
    }
  }

  std::cout << min_left << " " << min_right << std::endl;

  return 0;
}