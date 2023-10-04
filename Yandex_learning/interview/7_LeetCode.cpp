#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Проверить, можно ли одну строку переделать в другую путем
замены/добавения/удаления одного символа
*/

class Solution {
 public:
  bool isOneEdit(string s1, string s2) {
    vector<vector<int>> table(s1.size() + 1, vector<int>(s2.size() + 1, 0));
    for (int i = 0; i <= s1.size(); i++) {
      table[i][0] = i;
    }
    for (int i = 0; i <= s2.size(); i++) {
      table[0][i] = i;
    }
    for (int i = 1; i <= s1.size(); i++) {
      for (int j = 1; j <= s2.size(); j++) {
        int plus = table[i][j - 1] + 1;
        int minus = table[i - 1][j] + 1;
        int eq = table[i - 1][j - 1] + !(s1[i - 1] == s2[j - 1]);
        table[i][j] = min(min(plus, minus), eq);
      }
    }
    return (table[s1.size()][s2.size()] == 1);
  }
};

int main() {
  Solution solv;

  string s1, s2;
  cin >> s1 >> s2;

  cout << solv.isOneEdit(s1, s2) << "\n";
}