#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  Solution() {}

  int longestSubarray(vector<int>& nums) {
    int max_length = 0, current_length = 0, last_length = 0;
    bool delete_number = false, have_null = false;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i]) {
        current_length++;
      } else {
        have_null = true;
        max_length = max(max_length, current_length);
        if (delete_number) {
          max_length = max(max_length, current_length + last_length);
        }
        if (i && i < nums.size() - 1 && nums[i - 1] && nums[i + 1]) {
          last_length = current_length;
          delete_number = true;
        } else {
          last_length = 0;
          delete_number = false;
        }
        current_length = 0;
      }
    }
    max_length = max(max_length, current_length + last_length - !have_null);
    return max_length;
  }
};

int main() {
  int n;
  std::cin >> n;

  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
  }

  Solution solv;

  std::cout << solv.longestSubarray(vec) << std::endl;
  return 0;
}