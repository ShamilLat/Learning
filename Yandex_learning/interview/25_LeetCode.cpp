#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Посчитать количество комнат для проведения встреч

0, 30
5, 10
15, 20
Ответ 2

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

int main() {
  return 0;
}