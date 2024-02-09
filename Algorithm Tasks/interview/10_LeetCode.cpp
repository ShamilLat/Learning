#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Объединить слова по анаграмам.
Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
*/

template <typename Type>
ostream& operator<<(ostream& out, vector<Type>& vec) {
  for (auto& i : vec) {
    out << i << " ";
  }
  out << "\n";
  return out;
}

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> mp;

    for (auto& x : strs) {
      string word = x;
      sort(word.begin(), word.end());
      mp[word].push_back(x);
    }

    vector<vector<string>> res;
    for (auto& x : mp) {
      res.push_back(x.second);
    }
    return res;
  }
};

int main() {
  string s;
  vector<string> vec;
  while (cin >> s) {
    vec.push_back(s);
  }

  Solution solv;

  auto res = solv.groupAnagrams(vec);

  cout << res;

  return 0;
}