#include <iostream>
#include <string>
#include <unordered_map>

/*
Длинну наибольшей подпоследовательности, в которой только два типа букв

eceba
Ответ 3

ccaabbb
Ответ 5
*/

using namespace std;

class Solution {
 public:
  int lengthOfLongestSubstringTwoDistinct(string s) {
    unordered_map<char, int> letters;
    int i1 = 0, i2 = 0;
    int max_l = 0;
    for (i2 = 0; i2 < s.size(); i2++) {
      letters[s[i2]]++;
      while (letters.size() > 2 && i1 < i2) {
        letters[s[i1]]--;
        if (letters[s[i1]] == 0) {
          letters.erase(s[i1]);
        }
        i1++;
      }
      max_l = max(max_l, i2 - i1 + 1);
    }
    return max_l;
  }
};

int main() {
  Solution solv;
  string s;
  cin >> s;
  cout << solv.lengthOfLongestSubstringTwoDistinct(s) << endl;
}