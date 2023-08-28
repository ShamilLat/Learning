#include <iostream>
#include <string>

using namespace std;

int main() {
  string answer[2] = {"Loose", "Win"};
  int n1, m1;
  cin >> n1 >> m1;
  int table[n1 + 1][m1 + 1];
  table[0][0] = 0;

  for (int n = 0; n <= n1; n++) {
    for (int m = 0; m <= m1; m++) {
      if (n == 0 && m == 0) {
        continue;
      }
      int num = 1;
      if (n > 0) {
        num &= table[n - 1][m];
        if (m > 1) {
          num &= table[n - 1][m - 2];
        }
      }
      if (m > 0) {
        num &= table[n][m - 1];
        if (n > 1) {
          num &= table[n - 2][m - 1];
        }
      }
      if (n > 1) {
        num &= table[n - 2][m];
      }
      if (m > 1) {
        num &= table[n][m - 2];
      }
      table[n][m] = !num;
    }
  }
  cout << answer[table[n1][m1]] << "\n";

  return 0;
}