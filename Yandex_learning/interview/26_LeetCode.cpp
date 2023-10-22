#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Найти анаграммы второй строки в первой

Пример
Input: s = "cbaebabacd", p = "abc"
Output: [0,6]

Input: s = "abab", p = "ab"
Output: [0,1,2]
*/

class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> ans;
    unordered_map<char, int> m;
    for (auto x : p)
      m[x]++;
    int count = m.size();
    int i = 0, j = 0, k = p.size();

    while (j < s.size()) {
      if (m.contains(s[j])) {
        m[s[j]]--;
        if (m[s[j]] == 0)
          count--;
      }
      if (j - i + 1 < k) {
        j++;
      } else if (j - i + 1 == k) {
        if (count == 0)
          ans.push_back(i);

        if (m.contains(s[i])) {
          m[s[i]]++;
          if (m[s[i]] == 1)
            count++;
        }
        i++;
        j++;
      }
    }
    return ans;
  }
};

int main() {
  string a, b;
  cin >> a >> b;
  Solution solv;
  auto res = solv.findAnagrams(a, b);
  for (auto& i : res) {
    cout << i << " ";
  }
  cout << "\n";
}