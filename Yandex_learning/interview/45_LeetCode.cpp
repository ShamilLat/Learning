#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Решить польскую инверсную запись
*/

class Solution {
 public:
  int evalRPN(vector<string>& tokens) {
    int it = tokens.size() - 1;
    return count(tokens, it);
  }

  bool is_op(string& s) { return s == "+" || s == "-" || s == "/" || s == "*"; }
  int count(vector<string>& tokens, int& it) {
    int cnt = 0;
    if (is_op(tokens[it])) {
      cnt = funcs[tokens[it]](count(tokens, --it), count(tokens, --it));
    } else {
      return (stoi)(tokens[it]);
    }
    return cnt;
  }

  unordered_map<string, function<int(int, int)>> funcs = {
      {"+", [](int a, int b) { return b + a; }},
      {"-", [](int a, int b) { return b - a; }},
      {"*", [](int a, int b) { return b * a; }},
      {"/", [](int a, int b) { return b / a; }}};
};

int main() {
  Solution solv;
  vector<string> vec = {"2", "1", "+", "3", "*"};

  cout << solv.evalRPN(vec) << endl;
}