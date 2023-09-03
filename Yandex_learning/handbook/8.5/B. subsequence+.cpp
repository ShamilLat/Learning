#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, m, l;
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
  std::cin >> l;
  std::vector<int> c(l);
  for (int i = 0; i < l; i++) {
    std::cin >> c[i];
  }

  std::vector<std::vector<std::vector<int>>> table(
      n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(l + 1)));

  for (int i = 0; i <= n; i++) {
    table[i][0][0] = 0;
  }
  for (int i = 0; i <= m; i++) {
    table[0][i][0] = 0;
  }
  for (int i = 0; i <= l; i++) {
    table[0][0][i] = 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      for (int k = 1; k <= l; k++) {
        table[i][j][k] =
            std::max(std::max(table[i][j - 1][k], table[i - 1][j][k]),
                     table[i][j][k - 1]);
        if (a[i - 1] == b[j - 1] && a[i - 1] == c[k - 1]) {
          table[i][j][k] =
              std::max(table[i][j][k], table[i - 1][j - 1][k - 1] + 1);
        }
      }
    }
  }

  std::cout << table[n][m][l] << std::endl;

  return 0;
}