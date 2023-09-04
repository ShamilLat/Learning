#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::stringstream ss;
  char c, last_c;
  int cnt = 1;
  std::cin >> c;
  last_c = c;
  while (std::cin >> c) {
    if (last_c != c) {
      ss << last_c;
      if (cnt > 1) {
        ss << cnt;
      }
      cnt = 1;
    } else {
      cnt++;
    }
    last_c = c;
  }

  ss << last_c;
  if (cnt > 1) {
    ss << cnt;
  }

  std::cout << ss.str() << std::endl;
  return 0;
}