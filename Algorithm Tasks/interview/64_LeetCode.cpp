#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Дан массив.
Есть ли в нем такой подмассив, что сумма чисел подмассива кратна числу k
*/

class Solution {
 public:
  bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> sums;
    int sum = 0;
    sums.insert({0, -1});
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
      if (sums.contains(sum % k) && i - sums[sum % k] >= 2) {
        return true;
      } else {
        sums.insert({sum % k, i});
      }
    }
    return false;
  }
};

int main() {
  vector<int> vec = {7, 1, 3, 5, 11};

  Solution solv;
  cout << solv.checkSubarraySum(vec, 6) << endl;
}