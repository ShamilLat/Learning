#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

/*
Найти количество букв из 1й строки, встречающихся во второй строке

Примеры:
jewels = "aA", stones = "aAAbbbb"
Ответ 3 (т.к. ищем буквы 'a' и 'A')

jewels = "z", stones = "ZZ"
Ответ 0
*/

class Solution {
 public:
  int numJewelsInStones(string jewels, string stones) {
    unordered_set<char> l;
    for (auto& i : jewels) {
      l.insert(i);
    }
    int res = 0;
    for (auto& i : stones) {
      if (l.contains(i)) {
        res++;
      }
    }
    return res;
  }
};

int main() {
  Solution solv;
  string a, b;
  cin >> a >> b;
  cout << solv.numJewelsInStones(a, b) << endl;
}