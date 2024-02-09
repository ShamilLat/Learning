#include <iostream>
#include <vector>

using namespace std;

/*
Задача про монотонности
*/

class Solution {
 public:
  int longestArray(vector<int>& numbers) {
    if (numbers.size() == 0) {
      return 0;
    }

    if (numbers.size() == 1) {
      return 1;
    }

    bool mode = (numbers[0] <= numbers[1]);

    int max_length = 0, left_pos = 0;
    for (int i = 1; i <= numbers.size(); i++) {
      if (i == numbers.size() ||
         (mode && numbers[i - 1] > numbers[i]) ||
         (!mode && numbers[i - 1] < numbers[i])) {
        mode = !mode;
        max_length = max(max_length, i - left_pos);
        left_pos = i - 1;
      }
    }

    return max_length;
  }
};

int main() {
  Solution solv;

  vector<int> vec;
  int num;
  while (cin >> num) {
    if (num == 0) {
      break;
    }
    vec.push_back(num);
  }

  cout << solv.longestArray(vec) << endl;
}