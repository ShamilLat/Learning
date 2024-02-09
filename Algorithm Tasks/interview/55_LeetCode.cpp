#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/*
Найти максимальную площадь прямоугольника в матрице.
Прямоугольник строится из единиц
*/

ostream& operator<<(ostream& out, vector<int>& vec) {
  for (auto& i : vec) {
    out << i << " ";
  }
  return out;
}

class Solution {
 public:
  int largestRectangleArea(vector<int>& histo) {
    stack<int> st;
    int maxA = 0;
    int n = histo.size();
    for (int i = 0; i <= n; i++) {
      while (!st.empty() && (i == n || histo[st.top()] >= histo[i])) {
        int height = histo[st.top()];
        st.pop();
        int width = ((st.empty()) ? i : i - st.top() - 1);
        maxA = max(maxA, width * height);
      }
      st.push(i);
    }
    return maxA;
  }

  int maximalRectangle(vector<vector<char>>& matrix) {
    int maxArea = 0;
    int n = matrix.size(), m = matrix[0].size();
    vector<int> height(m, 0);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        matrix[i][j] == '1' ? height[j]++ : height[j] = 0;
      }
      //   cout << height << endl;
      maxArea = max(maxArea, largestRectangleArea(height));
    }
    return maxArea;
  }
};

int main() {
  vector<vector<char>> vec = {{'1', '0', '1', '0', '0'},
                              {'1', '0', '1', '0', '1'},
                              {'1', '1', '1', '1', '1'},
                              {'1', '0', '0', '1', '0'}};
  Solution solv;
  cout << solv.maximalRectangle(vec) << endl;
}