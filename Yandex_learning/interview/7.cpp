#include <algorithm>
#include <iostream>
#include <vector>

class Solution {
 public:
  Solution() {}
  Solution(std::vector<int> vec) : vec_(vec) {}

  int find_max_length() {
    int max_length = 0, current_length = 0;
    bool delete_number = false;
    int last_length = 0;
    for (int i = 0; i < vec_.size(); i++) {
      if (vec_[i] == 1) {
        current_length++;
      } else {
        max_length = std::max(max_length, current_length);
        if (delete_number) {
          max_length = std::max(max_length, current_length + last_length);
        }
        if (i > 0 && i < vec_.size() - 1 && vec_[i - 1] == 1 &&
            vec_[i + 1] == 1) {
          last_length = current_length;
          delete_number = true;
        } else {
          delete_number = false;
        }
        current_length = 0;
      }
    }
    return max_length;
  }

 private:
  std::vector<int> vec_;
};

int main() {
  int n;
  std::cin >> n;

  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
  }

  Solution solv(vec);

  std::cout << solv.find_max_length() << std::endl;
  return 0;
}