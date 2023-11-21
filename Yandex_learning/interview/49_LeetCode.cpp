#include <iostream>
#include <vector>

using namespace std;

/*
Отсортировать массив по квадратам чисел

[-4, -1, 0, 2, 10]
Ответ [0, 1, 4, 16, 100]

*/

class Solution {
 public:
  vector<int> sortedSquares(vector<int>& nums) {
    vector<int> res(nums.size());
    int left = 0, right = nums.size() - 1;
    for (int i = nums.size() - 1; i >= 0; i--) {
      if (abs(nums[left]) > abs(nums[right])) {
        res[i] = nums[left] * nums[left];
        left++;
      } else {
        res[i] = nums[right] * nums[right];
        right--;
      }
    }
    return res;
  }
};

int main() {
  Solution solv;
  vector<int> vec;
  int num;
  while (cin >> num) {
    vec.push_back(num);
  }

  auto res = solv.sortedSquares(vec);
  for (auto& i : res) {
    cout << i << " ";
  }
  cout << "\n";
}