#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

/*
Найти индекс первой неповторяющейся буквы в строке
*/

class Solution {
 public:
  int firstUniqChar(string s) {
    unordered_map<char, int> m;
    for (auto& i : s) {
      m[i]++;
    }
    for (int i = 0; i < s.size(); i++) {
      if (m[s[i]] == 1) {
        return i;
      }
    }
    return -1;
  }
};

int main() {
  Solution solv;
  string s = "aabb";

  cout << solv.firstUniqChar(s) << endl;
}