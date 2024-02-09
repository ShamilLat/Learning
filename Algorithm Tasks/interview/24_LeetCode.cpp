#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Найти пару индексов чисел, сумма которых равна target
*/

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> numbers;
    for (int i = 0; i < nums.size(); i++) {
      if (numbers.contains(target - nums[i])) {
        return vector<int>{numbers[target - nums[i]], i};
      } else {
        numbers.insert({nums[i], i});
      }
    }
    return vector<int>();
  }
};

int main() {
  vector<int> vec;
  int target;
  cin >> target;
  int num;
  while (cin >> num) {
    vec.push_back(num);
  }

  Solution solv;
  auto res = solv.twoSum(vec, target);

  cout << res[0] << " " << res[1] << endl;
  return 0;
}