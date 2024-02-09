#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
Написать функцию, которая делает
RLE сжатие строки, например "abbccc"→ "ab2c3"
*/

class Solution {
 public:
  int compress(vector<char>& chars) {
    char c, last_c;
    int cnt = 1;
    last_c = chars[0];
    int input_pos = 0;
    for (int i = 1; i < chars.size(); i++) {
      if (last_c != chars[i]) {
        chars[input_pos++] = last_c;
        if (cnt > 1) {
          string num = to_string(cnt);
          for (int j = 0; j < num.size(); j++) {
            chars[j + input_pos] = num[j];
          }
          input_pos += num.size();
        }
        cnt = 1;
      } else {
        cnt++;
      }
      last_c = chars[i];
    }

    chars[input_pos++] = last_c;
    if (cnt > 1) {
      string num = to_string(cnt);
      for (int j = 0; j < num.size(); j++) {
        chars[j + input_pos] = num[j];
      }
      input_pos += num.size();
    }

    chars.resize(input_pos);
    return input_pos;
  }
};

int main() {
  Solution solv;

  vector<char> s;
  char c;
  while (cin >> c) {
    s.push_back(c);
  }

  int res = solv.compress(s);

  return 0;
}