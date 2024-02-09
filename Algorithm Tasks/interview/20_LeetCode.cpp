#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Задача про сидение.
Найти такое место, которое будет максимально отдалено от соседа.
Вывести это макимальное расстояние
*/

class Solution {
 public:
  int maxDistToClosest(vector<int>& seats) {
    int cnt = 0;
    bool start_one = false;
    int result = 0;
    for (auto& i : seats) {
      if (i) {
        if (!start_one) {
          result = max(result, cnt);
        } else {
          result = max(result, (cnt + 1) / 2);
        }
        cnt = 0;
        start_one = true;
      } else {
        cnt++;
      }
    }

    result = max(result, cnt);
    return result;
  }
};

int main() {
  vector<int> vec;
  int num;
  while (cin >> num) {
    vec.push_back(num);
  }

  Solution solv;
  cout << solv.maxDistToClosest(vec) << endl;
}
