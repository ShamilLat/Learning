#include <iostream>
#include <vector>

using namespace std;

/*
Найти в массиве два числа, сумма которых равна target
*/

class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    while (numbers[left] + numbers[right] != target) {
      (numbers[left] + numbers[right] > target) ? --right : ++left;
    }

    return {left + 1, right + 1};
  }
};

int main() {
  vector<int> vec = {-1, 0};

  Solution solv;
  auto res = solv.twoSum(vec, -1);

  cout << res[0] << " " << res[1] << endl;
}