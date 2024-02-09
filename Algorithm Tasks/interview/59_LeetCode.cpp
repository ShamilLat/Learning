#include <iostream>
#include <vector>

using namespace std;

/*
Найти минимальный элемент в rotated-сортированном массиве.

Пример 4 5 6 7 0 1 2
Ответ 0

11 13 15 17
Ответ 11

2 1
Ответ 1

3 4 5 1 2
Ответ 1
*/

class Solution {
 public:
  int findMin(vector<int>& nums) {
    int first_num = nums[0];
    int left = 0, right = nums.size() - 1;
    while (left < right) {
      int m = (left + right) / 2;
      if (nums[m] >= first_num) {
        left = m + 1;
      } else {
        right = m;
      }
    }
    return ((nums[left] > first_num) ? first_num : nums[left]);
  }
};

int main() {
  vector<int> vec = {2, 1};
  Solution solv;

  cout << solv.findMin(vec) << endl;
}