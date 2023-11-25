#include <iostream>
#include <vector>

using namespace std;

/*
Получаем на вход отсортированный массив.
Удалить из него дубликаты (перенести их в начальные позиции)
и вернуть количество уникальных чисел

Пример
1 1 2
Вывод 2,
Массив поменялся на 1 2 2

0, 0, 1, 1, 1, 2, 2, 3, 3, 4
Вывод 5,
Массив поменялся на 0 1 2 3 4 2 2 3 3 4, или 0 1 2 3 4 _ _ _ _ _
*/


class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int i1 = 0, i2 = 0, last_num = nums[0];
    for (; i2 < nums.size(); i2++) {
      if (last_num != nums[i2]) {
        nums[++i1] = nums[i2];
        last_num = nums[i2];
      }
    }
    return i1 + 1;
  }
};

int main() {
  vector<int> vec = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

  Solution solv;
  cout << solv.removeDuplicates(vec) << endl;

  for (auto& i : vec) {
    cout << i << " ";
  }
  cout << endl;
}