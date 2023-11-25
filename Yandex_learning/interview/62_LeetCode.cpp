#include <iostream>
#include <vector>

using namespace std;

/*
Дан массив из чисел.
Вернуть массив, у которого на i-ой позиции будет умножение всех
чисел массива, но без i-го

Пример
1 2 3 4
Вывод
24 12 8 6
*/

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> left(nums.size(), 1);
    for (int i = 1; i < nums.size(); i++) {
      left[i] = nums[i - 1] * left[i - 1];
    }

    int num = 1;
    vector<int> res(nums.size(), 1);
    for (int i = nums.size() - 1; i >= 0; i--) {
      res[i] = num * left[i];
      num *= nums[i];
    }

    return res;
  }
};

int main() {
  vector<int> vec = {1, 2, 3, 4};

  Solution solv;
  auto res = solv.productExceptSelf(vec);

  for (auto& i : res) {
    cout << i << " ";
  }

  cout << endl;
}

/*
1 2 3 4

1  1  2 6
24 12 4 1

1  1  2 6
24 12 4 1
*/