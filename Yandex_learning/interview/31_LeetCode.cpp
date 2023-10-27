#include <iostream>
#include <queue>
#include <typeinfo>
#include <unordered_set>
#include <vector>

using namespace std;

/*
Найти "острова" из единиц в матрице

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
*/

class Solution {
 private:
  void check(int i, vector<vector<char>>& vec) {
    int new_n = i / vec[0].size();
    int new_m = i % vec[0].size();
    vec[new_n][new_m] = '0';
    if (new_n > 0 && vec[new_n - 1][new_m] == '1') {
      check(i - vec[0].size(), vec);
    }
    if (new_n < vec.size() - 1 && vec[new_n + 1][new_m] == '1') {
      check(i + vec[0].size(), vec);
    }
    if (new_m > 0 && vec[new_n][new_m - 1] == '1') {
      check(i - 1, vec);
    }
    if (new_m < vec[0].size() - 1 && vec[new_n][new_m + 1] == '1') {
      check(i + 1, vec);
    }
  }

 public:
  int numIslands(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    int res = 0;

    for (int i = 0; i < n * m; i++) {
      if (grid[i / m][i % m] == '1') {
        check(i, grid);
        res++;
      }
    }
    return res;
  }
};

int main() {
  int m, n;
  cin >> n >> m;

  vector<vector<char>> vec(n, vector<char>(m));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> vec[i][j];
    }
  }

  Solution solv;

  cout << solv.numIslands(vec) << endl;

  return 0;
}

/*
4 5
1 1 1 1 0
1 1 0 1 0
1 1 0 0 0
0 0 0 0 0

4 5
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

*/