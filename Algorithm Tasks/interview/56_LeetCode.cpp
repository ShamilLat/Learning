#include <iostream>
#include <vector>

using namespace std;

/*
Найти позицию числа в массиве, отсортированном "по кругу".
Пример: 4 5 6 7 0 1 2
Ищем 3
Ответ -1

Ищем 5
Ответ 1
*/

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int low = 0, high = nums.size() - 1;

    while (low <= high) {
      int mid = (low + high) / 2;

      if (nums[mid] == target) {
        return mid;
      }

      if (nums[low] <= nums[mid]) {
        if (nums[low] <= target && target < nums[mid]) {
          high = mid - 1;
        } else {
          low = mid + 1;
        }
      } else {
        if (nums[mid] < target && target <= nums[high]) {
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      }
    }

    return -1;
  }
};

int main(int argc, char* argv[]) {
  vector<int> vec = {3, 1};
  Solution solv;

  cout << solv.search(vec, atoi(argv[1])) << endl;
}