#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Найти самый длинный палиндром в строке
*/

class Solution {
 public:
  string longestPalindrome(string s) {
    int max_length = 1;
    string res = s.substr(0, 1);
    for (int i = 0; i < s.length(); i++) {
      for (int j = i + max_length; j < s.length(); j++) {
        if (isPalinfrome(s, i, j) && j - i + 1 > max_length) {
          max_length = j - i + 1;
          res = s.substr(i, j - i + 1);
        }
      }
    }
    return res;
  }

  bool isPalinfrome(string& s, int i, int j) {
    while (i < j) {
      if (s[i] != s[j])
        return false;
      i++;
      j--;
    }
    return true;
  }
};

int main() {
  string s;
  cin >> s;

  Solution solv;
  cout << solv.longestPalindrome(s) << endl;

  return 0;
}
