#include <iostream>
#include <string>

using namespace std;

/*
Сложить два числа записанные в виде строки
*/

class Solution {
 public:
  string addStrings(string num1, string num2) {
    if (num2.size() > num1.size()) {
      return addStrings(num2, num1);
    }
    int i1 = num1.size() - 1, i2 = num2.size() - 1;
    int k = 0;
    while (i2 >= 0) {
      int value = num1[i1] + num2[i2] - '0' - '0' + k;
      k = value / 10;
      num1[i1] = '0' + value % 10;
      i1--;
      i2--;
    }
    while (k && i1 >= 0) {
      int value = num1[i1] + k - '0';
      k = value / 10;
      num1[i1] = '0' + value % 10;
      i1--;
    }

    if (k) {
      num1 = "1" + num1;
    }

    return num1;
  }
};

int main() {
  string s1 = "0", s2 = "0";
  Solution solv;
  cout << solv.addStrings(s1, s2) << endl;
}