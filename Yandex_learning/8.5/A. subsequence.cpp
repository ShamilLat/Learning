#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::cin >> m;
  std::vector<int> b(m);
  for (int i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1));

  for (int i = 0; i <= n; i++) {
    table[i][0] = 0;
  }
  for (int i = 0; i <= m; i++) {
    table[0][i] = 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      table[i][j] = std::max(table[i][j - 1], table[i - 1][j]);
      if (a[i - 1] == b[j - 1]) {
        table[i][j] = std::max(table[i][j], table[i - 1][j - 1] + 1);
      }
    }
  }

  std::cout << table[n][m] << std::endl;

  return 0;
}