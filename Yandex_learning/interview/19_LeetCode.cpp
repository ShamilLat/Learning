#include <iostream>
#include <vector>

using namespace std;

/*
Найти максимальную подпоследовательность единиц, если можно
один ноль заменить на единицу
*/

class Solution {
 public:
  int findMaxConsecutiveOnes(vector<int>& nums) {
    int l = 0, r = 0, zeros = 0, max = 0;
    while (r < nums.size()) {
      if (nums[r] == 0)
        zeros++;
      while (zeros == 2) {
        if (nums[l++] == 0)
          zeros--;
      }
      max = std::max(max, r - l + 1);
      r++;
    }
    return max;
  }
};

int main() {
  return 0;
}