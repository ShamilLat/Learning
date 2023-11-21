#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
Содержится ли во второй строке первая строка по буквам (порядок важен)
Пример

"abc", "ahbgdc"
true

"axc", "ahbgdc"
false
*/

class Solution {
 public:
  bool isSubsequence(string s, string t) {
    int i1 = 0;
    for (int i2 = 0; i2 < t.size() && i1 < s.size(); i2++) {
      if (s[i1] == t[i2]) {
        i1++;
      }
    }
    return (i1 == s.size());
  }
};

int main() {
  Solution solv;

  string a, b;
  cin >> a >> b;
  cout << solv.isSubsequence(a, b) << endl;
}