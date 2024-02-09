#include <iostream>
#include <string>

using namespace std;

/*
Reverse each word in srting s
*/

class Solution {
 public:
  string reverseWords(string s) {
    int i1 = 0, i2 = 0;
    for (int i = 0; i <= s.size(); i++) {
      if (i == s.size() || s[i] == ' ') {
        i2 = i - 1;
        while (i1 < i2) {
          swap(s[i1++], s[i2--]);
        }
        i1 = i + 1;
      }
    }
    return s;
  }
};

int main() {
  Solution solv;
  string s = "Let's take LeetCode contest";

  cout << solv.reverseWords(s) << endl;
}