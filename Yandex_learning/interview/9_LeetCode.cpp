#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/*
Передвинуть все нули в массиве в конец массива
*/

class Solution {
 public:
  void moveZeroes(vector<int>& nums) {
    int first_null_pos = -1;

    auto vec_size = nums.size();
    for (int i = 0; i < vec_size; i++) {
      if (!nums[i] && first_null_pos == -1) {
        first_null_pos = i;
      } else if (nums[i] && first_null_pos != -1) {
        swap(nums[first_null_pos], nums[i]);
        first_null_pos++;
      }
    }
  }
};

int main() {
  vector<int> vec;
  int num;
  while (cin >> num) {
    vec.push_back(num);
  }

  Solution solv;
  solv.moveZeroes(vec);

  for (auto& it : vec) {
    cout << it << " ";
  }
  cout << "\n";
}