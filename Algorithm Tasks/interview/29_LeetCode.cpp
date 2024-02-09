#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/*
Найти наибольшую длинну подстроки без повторяющихся букв
*/

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    int i = 0, j = 0;
    int max_cnt = 0;

    unordered_set<char> letters;
    while (i < s.size()) {
      if (!letters.contains(s[i])) {
        letters.insert(s[i]);
        max_cnt = max(max_cnt, (int)letters.size());
        i++;
      } else {
        do {
          letters.erase(s[j]);
        } while (s[j++] != s[i]);
      }
    }

    return max_cnt;
  }
};

int main() {
  string s;
  cin >> s;
  Solution solv;
  cout << solv.lengthOfLongestSubstring(s) << endl;
  return 0;
}