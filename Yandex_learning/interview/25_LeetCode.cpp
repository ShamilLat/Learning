#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

/*
Посчитать количество комнат для проведения встреч

0, 30
5, 10
15, 20
Ответ 2


Идея в том, что смотрим на границы интервалов и считаем,
сколько в данный момент занято переговорок
*/

class Solution {
 public:
  int minMeetingRooms(vector<vector<int>>& A) {
    vector<int> starts, ends;
    for (auto& v : A) {
      starts.push_back(v[0]);
      ends.push_back(v[1]);
    }
    sort(begin(starts), end(starts));
    sort(begin(ends), end(ends));
    int N = A.size(), ans = 0, cnt = 0;
    for (int i = 0, j = 0; i < N;) {
      if (starts[i] < ends[j]) {
        ++cnt;
        ++i;
        ans = max(ans, cnt);
      } else if (starts[i] > ends[j]) {
        --cnt;
        ++j;
      } else {
        ++i;
        ++j;
      }
    }
    return ans;
  }
};

class Solution2 {
 public:
  int minMeetingRooms(vector<vector<int>>& A) {
    vector<pair<int, int>> nums;
    for (auto& vec_i : A) {
      nums.push_back({vec_i[0], 1});
      nums.push_back({vec_i[1], -1});
    }
    sort(nums.begin(), nums.end(),
         [](pair<int, int>& el1, pair<int, int>& el2) {
           return (el1.first != el2.first ? el1.first < el2.first
                                          : el1.second < el2.second);
         });

    int res = 0, cnt = 0;
    for (auto& i : nums) {
      cnt += i.second;
      res = max(res, cnt);
    }
    return res;
  }
};

int main() {
  for (int test = 0; test < 100; test++) {
    vector<vector<int>> vec;
    for (int i = 0; i < 10; i++) {
      int num1 = rand() % 30;
      vec.push_back({num1, num1 + rand() % 30});
    }

    Solution solv;
    Solution2 solv2;

    int ans1 = solv.minMeetingRooms(vec), ans2 = solv2.minMeetingRooms(vec);
    if (ans1 != ans2) {
      cout << "Test ERROR\n";
      for (auto& vec_i : vec) {
        cout << vec_i[0] << " " << vec_i[1] << "\n";
      }
      cout << "ans1 = " << ans1 << ", ans2 = " << ans2 << "\n";
    } else {
      cout << "Test OK\n";
    }
  }

  return 0;
}