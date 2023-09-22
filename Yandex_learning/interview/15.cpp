#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;

    if (nums.size() == 0) {
      return res;
    }
    int first = nums[0], second = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] != second + 1) {
        if (first != second) {
          res.push_back(to_string(first) + "->" + to_string(second));
        } else {
          res.push_back(to_string(first));
        }
        first = nums[i];
      }
      second = nums[i];
    }
    if (first != second) {
      res.push_back(to_string(first) + "->" + to_string(second));
    } else {
      res.push_back(to_string(first));
    }

    return res;
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

  auto res_vec = solv.summaryRanges(vec);
  for (auto& it : res_vec) {
    std::cout << it << "\n";
  }

  return 0;
}