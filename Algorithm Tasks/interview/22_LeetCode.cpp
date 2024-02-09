#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Объединить интервалы

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Объединили 1:3 и 2:6

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Объединили 1:4 и 4:5
*/

class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> result;

    sort(
        intervals.begin(), intervals.end(),
        [](vector<int>& vec1, vector<int>& vec2) { return vec1[0] < vec2[0]; });

    int left = intervals[0][0], right = intervals[0][1];
    for (int i = 1; i < intervals.size(); i++) {
      if (right >= intervals[i][0]) {
        right = max(intervals[i][1], right);
      } else {
        result.push_back(vector<int>{left, right});
        left = intervals[i][0];
        right = intervals[i][1];
      }
    }

    result.push_back(vector<int>{left, right});

    return result;
  }
};

int main() {
  vector<vector<int>> vec;

  int n1, n2;
  while (cin >> n1 >> n2) {
    vec.push_back(vector<int>{n1, n2});
  }

  Solution solv;
  auto res = solv.merge(vec);

  for (auto& vec_i : res) {
    for (auto& i : vec_i) {
      cout << i << " ";
    }
    cout << endl;
  }
}