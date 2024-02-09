#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Напишите функцию, которая принимает массив 0 и 1, а возвращает
длину максимального подмассива из единиц после удаления ровно
одной цифры.
*/

class Solution {
 public:
  Solution() {}

  int longestSubarray(vector<int>& nums) {
    int i1 = 0, i2 = 0, cnt = 0;
    int max_length = 0;
    for (; i2 < nums.size(); i2++) {
      if (nums[i2] == 0) {
        cnt++;
      }
      if (cnt > 1) {
        if (nums[i1] == 0) {
          cnt--;
        }
        i1++;
      }
      max_length = max(max_length, i2 - i1);
    }
    return max_length;
  }
};

int main() {
  int n;
  cin >> n;

  vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  Solution solv;

  cout << solv.longestSubarray(vec) << endl;
  return 0;
}