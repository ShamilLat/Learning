#include <iostream>
#include <vector>

using namespace std;

/*
Посчитать наименьшее количество квадратов чисел, необходимых
для посчёта заданного n

n = 13
Ответ 2 (4 + 9)

n = 12
Ответ 3 (4 + 4 + 4)
*/

class Solution {
 public:
  int numSquares(int n) {
    vector<int> cnt(n + 1, INT_MAX);
    int num = 1;
    cnt[0] = 0;
    while (num * num <= n) {
      for (int i = num * num; i <= n; i++) {
        cnt[i] = min(cnt[i], cnt[i - num * num] + 1);
      }
      num++;
    }
    return cnt[n];
  }
};

int main() {
  Solution solv;
  cout << solv.numSquares(13) << endl;
}