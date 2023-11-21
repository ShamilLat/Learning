#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Найти число, которое отсуствует в массиве

Пример:
[3, 0, 1]
Ответ 2

[0, 1]
Ответ 2
*/

class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    int xor_num = 0, iter = 0;
    for (auto& i : nums) {
      xor_num ^= i;
      xor_num ^= iter;
      iter++;
    }
    xor_num ^= nums.size();
    return xor_num;
  }
};

int main() {
  Solution solv;
  vector<int> vec = {0, 1};
  cout << solv.missingNumber(vec) << endl;
}