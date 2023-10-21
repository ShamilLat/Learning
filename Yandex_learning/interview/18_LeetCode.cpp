#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  bool isValid(string s) {
    stack<char> st;
    for (auto& c : s) {
      if (check_open_close(c)) {
        st.push(c);
      } else {
        if (st.empty()) {
          return false;
        }
        char tmp = st.top();
        st.pop();
        if (!check_brackets(tmp, c)) {
          return false;
        }
      }
    }
    if (!st.empty()) {
      return false;
    }
    return true;
  }

 private:
  unordered_map<char, int> symbols = {{'(', 1}, {'{', 2}, {'[', 3},
                                      {']', 4}, {'}', 5}, {')', 6}};
  bool check_open_close(char c) {
    if (symbols[c] <= 3) {
      return true;
    }
    return false;
  }

  bool check_brackets(char open, char close) {
    if (symbols[open] + symbols[close] == 7) {
      return true;
    }
    return false;
  }
};

int main() {
  string s;
  cin >> s;

  Solution solv;
  cout << solv.isValid(s) << endl;
}