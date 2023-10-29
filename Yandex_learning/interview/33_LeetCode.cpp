#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

/*
Максимальную длинну из одинаковых букв в строке

Пример
abbcccddddeeeeedcba
Ответ 5 (буквы eeeee)
*/

class Solution {
 public:
  int maxPower(string s) {
    int it = 0, ans = 1;
    for (int i = 1; i < s.length(); i++) {
      (s[i] == s[it]) ? ans = max(i - it + 1, ans) : it = i;
    }
    return ans;
  }
};

int main() {
  string s;
  cin >> s;
  Solution solv;

  cout << solv.maxPower(s) << endl;
  return 0;
}