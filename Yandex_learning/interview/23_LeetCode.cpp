#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
Количество воды между блоками после дождя
*/

class Solution {
 public:
  int trap(vector<int>& height) {
    stack<pair<int, int>> st;
    int res = 0;
    for (int i = 0; i < height.size(); i++) {
      if (height[i] == 0) {
        continue;
      }
      int prev_max = 0;
      while (!st.empty() && st.top().first <= height[i]) {
        res += (i - st.top().second - 1) * (st.top().first - prev_max);
        prev_max = max(prev_max, st.top().first);
        st.pop();
      }
      if (!st.empty()) {
        res += (i - st.top().second - 1) * (height[i] - prev_max);
      }
      st.push({height[i], i});
    }
    return res;
  }
};

int main() {
  vector<int> vec;
  int num;
  while (cin >> num) {
    vec.push_back(num);
  }

  Solution solv;
  cout << solv.trap(vec) << endl;
}