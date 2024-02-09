#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

std::string f1(std::string s1, std::string s2) {
  size_t max_s = std::max(s1.size(), s2.size());
  std::string res;
  res.resize(max_s);
  int i1 = s1.size() - 1, i2 = s2.size() - 1, i3 = res.size() - 1;
  int ten = 0;
  while (i1 >= 0 && i2 >= 0) {
    res[i3] = (s1[i1] - '0' + s2[i2] - '0' + ten) % 10 + '0';
    ten = (s1[i1] - '0' + s2[i2] - '0' + ten) / 10;
    i1--;
    i2--;
    i3--;
  }
  while (i1 >= 0) {
    res[i3] = (s1[i1] - '0' + ten) % 10 + '0';
    ten = (s1[i1] - '0' + ten) / 10;
    i1--;
    i3--;
  }
  while (i2 >= 0) {
    // res[i3] = s2[i2];
    res[i3] = (s2[i2] - '0' + ten) % 10 + '0';
    ten = (s2[i2] - '0' + ten) / 10;
    i2--;
    i3--;
  }

  if (ten) {
    return "1" + res;
  }
  return res;
}

int main() {
  std::string s1, s2;
  std::cin >> s1 >> s2;

  std::cout << f1(s1, s2) << std::endl;

  for (int i = 0; i < 1000; i++) {
    int a = rand() % 1000, b = rand() % 1000;
    std::stringstream ss1, ss2;
    ss1 << a;
    ss2 << b;
    std::cout << "Test check:\n" << a << " " << b << "\n";
    std::cout << "Result is: " << a + b << "\n";
    std::cout << "F answ is: " << f1(ss1.str(), ss2.str()) << "\n\n";
  }
}