#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> s(n);
  int sum = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> s[i];
    sum += s[i];
  }

  if (sum % 3 != 0) {
    std::cout << 0 << std::endl;
    return 0;
  }
  int v = sum / 3;

  std::vector<std::vector<std::vector<bool>>> table(
      n + 1,
      std::vector<std::vector<bool>>(v + 1, std::vector<bool>(v + 1, false)));

  table[0][0][0] = true;

  for (int i = 1; i <= n; i++) {
    for (int s1 = 0; s1 <= v; s1++) {
      for (int s2 = 0; s2 <= v; s2++) {
        table[i][s1][s2] = table[i - 1][s1][s2];
        if (s[i - 1] <= s1) {
          table[i][s1][s2] =
              table[i][s1][s2] || table[i - 1][s1 - s[i - 1]][s2];
        }
        if (s[i - 1] <= s2) {
          table[i][s1][s2] =
              table[i][s1][s2] || table[i - 1][s1][s2 - s[i - 1]];
        }
      }
    }
  }
  std::cout << table[n][v][v] << std::endl;

  return 0;
}