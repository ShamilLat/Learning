#include <stdint.h>
#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& out, std::vector<int>& vec) {
  for (auto& i : vec) {
    out << i << " ";
  }
  return out;
}

int main() {
  std::vector<int64_t> numbers;
  int num = 0;
  char op;
  std::cin >> num;
  numbers.push_back(num);
  while (std::cin >> op) {
    std::cin >> num;
    if (op == '+') {
      numbers.push_back(num);
    } else if (op == '-') {
      numbers.push_back(-num);
    } else if (op == '*') {
      int64_t tmp = numbers.back();
      numbers.pop_back();
      numbers.push_back(tmp * (int64_t)num);
    }
  }

  int64_t sum = 0;
  for (auto& i : numbers) {
    sum += i;
  }
  std::cout << sum << std::endl;

  return 0;
}