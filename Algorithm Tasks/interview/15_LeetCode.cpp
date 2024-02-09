#include <iostream>
#include <string>
#include <unordered_map>

/*
Given two strings s1 and s2, return true if s2 contains a permutation of s1, or
false otherwise.

In other words, return true if one of s1's permutations is the substring of s2.

Example 1:

Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").
*/

using namespace std;

class Solution {
 public:
  bool checkInclusion(string s1, string s2) {
    if (s1.length() > s2.length()) {
      return false;
    }
    unordered_map<char, int> letters;
    for (auto& i : s1) {
      letters[i]++;
    }

    unordered_map<char, int> cnt_letters;
    int cnt = 0;
    int it_left = 0, it_right = 0;
    for (; it_right < s1.length(); it_right++) {
      if (letters.contains(s2[it_right])) {
        cnt_letters[s2[it_right]]++;
        if (cnt_letters[s2[it_right]] == letters[s2[it_right]]) {
          cnt++;
        } else if (cnt_letters[s2[it_right]] == letters[s2[it_right]] + 1) {
          cnt--;
        }
        if (cnt == letters.size()) {
          return true;
        }
      }
    }

    while (it_right < s2.length()) {
      if (letters.contains(s2[it_left])) {
        cnt_letters[s2[it_left]]--;
        if (cnt_letters[s2[it_left]] == letters[s2[it_left]]) {
          cnt++;
        } else if (cnt_letters[s2[it_left]] == letters[s2[it_left]] - 1) {
          cnt--;
        }
      }

      if (letters.contains(s2[it_right])) {
        cnt_letters[s2[it_right]]++;
        if (cnt_letters[s2[it_right]] == letters[s2[it_right]]) {
          cnt++;
        } else if (cnt_letters[s2[it_right]] == letters[s2[it_right]] + 1) {
          cnt--;
        }
      }

      if (cnt == letters.size()) {
        return true;
      }

      it_left++;
      it_right++;
    }
    return false;
  }
};

int main() {
  string s1, s2;
  cin >> s1 >> s2;

  Solution solv;
  cout << solv.checkInclusion(s1, s2) << endl;
  return 0;
}