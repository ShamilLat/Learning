#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/*
Подается бинарный массив из 0 и 1 и число k.
Вывести максимальное количество единиц подряд, если мы можем
заменить k нулей

Given a binary array nums and an integer k,
return the maximum number of consecutive 1's in the array
if you can flip at most k 0's.
*/

class Solution {
 public:
  int longestOnes(vector<int>& nums, int k) {
    queue<int> poses;
    int i1 = 0;
    int ans = 0;
    for (int i2 = 0; i2 < nums.size(); i2++) {
      if (nums[i2] == 0) {
        poses.push(i1);
        i1 = i2 + 1;
      }
      if (poses.size() > k) {
        poses.pop();
      }

      !poses.empty() ? ans = max(ans, i2 - poses.front() + 1)
                     : ans = max(ans, i2 - i1 + 1);
    }

    return ans;
  }
};

class Solution2 {
 public:
  int longestOnes(vector<int>& nums, int k) {
    int i = 0, j, cnt = 0;
    for (j = 0; j < nums.size(); j++) {
      if (nums[j] == 0)
        cnt++;
      if (cnt > k) {
        if (nums[i] == 0)
          cnt--;
        i++;
      }
    }
    return j - i;
  }
};

int main() {
  vector<int> vec;

  //   vec = {1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1};
  //   vec = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
  //   vec = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
  vec = {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0};

  Solution solv;
  Solution2 solv2;

  cout << solv.longestOnes(vec, 1) << endl;
  cout << solv2.longestOnes(vec, 1) << endl;
}