#include <algorithm>
#include <iostream>
#include <vector>

bool f(const std::string& a, const std::string& b) {
  std::vector<std::vector<int>> table(a.size() + 1,
                                      std::vector<int>(b.size() + 1));

  for (int j = 0; j <= b.size(); j++) {
    table[0][j] = j;
  }
  for (int i = 0; i <= a.size(); i++) {
    table[i][0] = i;
  }

  for (int i = 1; i <= a.size(); i++) {
    for (int j = 1; j <= b.size(); j++) {
      int insertion = table[i][j - 1] + 1;
      int deletion = table[i - 1][j] + 1;
      int match = table[i - 1][j - 1];
      int mismatch = table[i - 1][j - 1] + 1;
      if (a[i - 1] == b[j - 1]) {
        table[i][j] = std::min(std::min(insertion, deletion), match);
      } else {
        table[i][j] = std::min(std::min(insertion, deletion), mismatch);
      }
    }
  }

  return (table[a.size()][b.size()] == 1);
}

int main() {
  std::string a, b;
  std::cin >> a >> b;

  std::cout << (f(a, b) ? "Yes" : "No") << std::endl;

  return 0;
}
