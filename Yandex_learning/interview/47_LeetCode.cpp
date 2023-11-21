#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

using namespace std;

/*
Упростить путь к файлу

Пример
"/home//foo/"
Output: "/home/foo"
*/

class Solution {
 public:
  string simplifyPath(string path) {
    int i1 = 0, i2 = 1;

    stack<string> st;
    while (i2 <= path.size()) {
      if (path[i2] == '/' || i2 == path.size()) {
        string tmp = path.substr(i1, i2 - i1);
        if (tmp == "/..") {
          if (!st.empty())
            st.pop();
        } else if (tmp.size() && tmp != "/." && tmp != "/") {
          st.push(tmp);
        }
        i1 = i2;
      }
      i2++;
    }
    stringstream ss;
    if (st.size() == 0) {
      ss << '/';
    } else {
      stack<string> new_st;
      while (!st.empty()) {
        new_st.push(st.top());
        st.pop();
      }

      while (!new_st.empty()) {
        ss << new_st.top();
        new_st.pop();
      }
    }

    return ss.str();
  }
};

int main() {
  Solution solv;
  string s;
  cin >> s;
  cout << solv.simplifyPath(s);
}