#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

/*
parentheses:
n = 1
()

n = 2
(()), ()()

n = 3
((())), (()()), (())(), ()(()), ()()()
*/

template <typename Type>
ostream& operator<<(ostream& out, vector<Type> vec) {
  for (auto& i : vec) {
    out << i << " ";
  }
  return out;
}

class Solution {
 public:
  void rec(string str, int open, int close) {
    if (open == 0 && close == 0) {
      res.push_back(str);
      return;
    } else if (open == close) {
      str.push_back('(');
      rec(str, open - 1, close);
    } else if (open == 0) {
      str.push_back(')');
      rec(str, open, close - 1);
    } else {
      str.push_back('(');
      rec(str, open - 1, close);

      str.pop_back();
      str.push_back(')');
      rec(str, open, close - 1);
    }
  }

  vector<string> generateParenthesis(int n) {
    rec("", n, n);
    return res;
  }

  vector<string> res;
};

int main() {
  int n;
  cin >> n;

  Solution solv;
  auto vec = solv.generateParenthesis(n);
  cout << vec << endl;

  return 0;
}
