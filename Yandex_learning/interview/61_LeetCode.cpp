#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Разбить строку на подстроки, в которых не повторяются буквы

Пример
"ababcbacadefegdehijhklij"
Разбиваем на
"ababcbaca", "defegde", "hijhklij"
Ответ: {9, 7, 8} (длинны этих подстрок)
*/

class Solution {
 public:
  vector<int> partitionLabels(string s) {
    unordered_map<char, int> letters_info;
    stack<pair<int, int>> intervals;
    for (int i = 0; i < s.size(); i++) {
      char letter = s[i];
      if (!letters_info.contains(letter)) {
        letters_info[letter] = i;
        intervals.push({i, i});
      } else {
        int num = 0;
        while (!intervals.empty() &&
               intervals.top().second >= letters_info[letter]) {
          num = min(intervals.top().first, letters_info[letter]);
          intervals.pop();
        }
        intervals.push({num, i});
      }
    }

    vector<int> res(intervals.size());
    for (int i = intervals.size() - 1; i >= 0; i--) {
      res[i] = intervals.top().second - intervals.top().first + 1;
      intervals.pop();
    }

    return res;
  }
};

class Solution2 {
 public:
  vector<int> partitionLabels(string s) {
    unordered_map<char, int> mp;
    // filling impact of character's
    for (int i = 0; i < s.size(); i++) {
      mp[s[i]] = i;
    }
    // making of result
    vector<int> res;
    int prev = -1;
    int maxi = 0;

    for (int i = 0; i < s.size(); i++) {
      maxi = max(maxi, mp[s[i]]);
      if (maxi == i) {
        // partition time
        res.push_back(maxi - prev);
        prev = maxi;
      }
    }
    return res;
  }
};

int main() {
  string s = "abcdefg";

  Solution solv;
  auto res = solv.partitionLabels(s);

  for (auto& i : res) {
    cout << i << " ";
  }
  cout << endl;
}