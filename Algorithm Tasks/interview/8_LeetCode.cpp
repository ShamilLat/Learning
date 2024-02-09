#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Возвращает количество подмассивов в массиве, сумма элементов
которых равна заданному k
*/

class Solution {
 public:
  int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> sums;
    int sum = 0, cnt = 0;
    sums[0] = 1;
    for (int i = 0; i < nums.size(); i++) {
      sum += nums[i];
      if (sums.contains(sum - k)) {
        cnt += sums[sum - k];
      }
      if (!sums.contains(sum)) {
        sums[sum] = 0;
      }
      sums[sum]++;
    }
    return cnt;
  }
};

int main() {
  Solution solv;
  int k, n;
  vector<int> vec;

  cin >> k;
  while (cin >> n) {
    vec.push_back(n);
  }

  std::cout << solv.subarraySum(vec, k) << "\n";
}