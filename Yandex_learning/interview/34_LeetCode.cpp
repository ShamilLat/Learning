#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
Найти все пересечения интервалов в двух списках

Input:
firstList = [[0,2],[5,10],[13,23],[24,25]]
secondList = [[1,5],[8,12],[15,24],[25,26]]

Output:
[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
*/

class Solution {
 public:
  vector<vector<int>> intervalIntersection(vector<vector<int>>& firstList,
                                           vector<vector<int>>& secondList) {
    vector<vector<int>> res;
    for (int i = 0, j = 0; i < firstList.size() && j < secondList.size();) {
      int left = max(firstList[i][0], secondList[j][0]),
          right = min(firstList[i][1], secondList[j][1]);

      if (left <= right) {
        res.push_back(vector<int>{left, right});
      }

      firstList[i][1] < secondList[j][1] ? i++ : j++;
    }

    return res;
  }
};

int main() {
  vector<vector<int>> a, b;
  a = {{0, 2}, {5, 10}, {13, 23}, {24, 25}},
  b = {{1, 5}, {8, 12}, {15, 24}, {25, 26}};

  //   a = {{8, 15}};
  //   b = {{2, 6}, {8, 10}, {12, 20}};

  Solution solv;
  auto res = solv.intervalIntersection(a, b);
  for (auto& i : res) {
    cout << i[0] << " " << i[1] << endl;
  }
}