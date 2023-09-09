#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

void f(std::string& s) {
  char c, last_c;
  int cnt = 1;
  last_c = s[0];
  int input_pos = 0;
  for (int i = 1; i < s.size(); i++) {
    if (last_c != s[i]) {
      s[input_pos++] = last_c;
      if (cnt > 1) {
        std::string num = std::to_string(cnt);
        s.replace(input_pos, num.size(), num);
        input_pos += num.size();
      }
      cnt = 1;
    } else {
      cnt++;
    }
    last_c = s[i];
  }

  s[input_pos++] = last_c;
  if (cnt > 1) {
    s.replace(input_pos, std::to_string(cnt).size(), std::to_string(cnt));
    input_pos += std::to_string(cnt).size();
  }

  s.resize(input_pos);
}

int main() {
  std::string s;
  std::cin >> s;
  f(s);
  std::cout << s << std::endl;
  return 0;
}