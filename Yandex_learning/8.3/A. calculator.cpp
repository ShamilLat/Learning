#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int main() {
  int num;
  std::cin >> num;

  std::vector<int> num_table(num + 1, 0x7fffffff);
  num_table[1] = 0;
  for (int i = 2; i <= num; i++) {
    num_table[i] = std::min(num_table[i], num_table[i - 1] + 1);
    if (i % 2 == 0) {
      num_table[i] = std::min(num_table[i], num_table[i / 2] + 1);
    }
    if (i % 3 == 0) {
      num_table[i] = std::min(num_table[i], num_table[i / 3] + 1);
    }
  }

  std::cout << num_table[num] << std::endl;
  std::stack<int> op_list;
  while (num > 1) {
    // op_list.push_front(num);
    op_list.push(num);
    if (num_table[num] == 1 + num_table[num - 1]) {
      num--;
    } else if (num % 2 == 0 && num_table[num] == 1 + num_table[num / 2]) {
      num /= 2;
    } else if (num % 3 == 0 && num_table[num] == 1 + num_table[num / 3]) {
      num /= 3;
    }
  }
  op_list.push(1);

  bool check = 0;
  while (op_list.size()) {
    if (check) {
      std::cout << " ";
    }
    std::cout << op_list.top();
    op_list.pop();
    check = 1;
  }
  std::cout << std::endl;

  return 0;
}