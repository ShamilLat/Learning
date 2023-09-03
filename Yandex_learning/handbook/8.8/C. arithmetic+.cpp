#include <stdint.h>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

template <typename Type>
std::ostream& operator<<(std::ostream& out, std::vector<Type>& vec) {
  for (auto& i : vec) {
    out << i << " ";
  }
  return out;
}

struct Value {
  Value() {}
  Value(int a_) : number(a_) { type = true; }
  Value(char a_) : op(a_) { type = false; }

  friend std::ostream& operator<<(std::ostream& out, Value& value) {
    if (value.type) {
      out << value.number;
    } else {
      out << value.op;
    }
    return out;
  }

  int number;
  char op;
  bool type = 0;
};

std::map<char, int> pr = {{'+', 0}, {'-', 0}, {'*', 1}};
int current_pr = 0;
std::map<char, std::function<int64_t(int64_t&, int64_t&)>> f;

void check_op(char op,
              std::vector<Value>& res,
              std::stack<std::pair<char, int>>& ops) {
  if (op == '+' || op == '-' || op == '*') {
    while (!ops.empty() && ops.top().second >= pr[op] + current_pr) {
      res.emplace_back(Value(ops.top().first));
      ops.pop();
    }
    ops.push({op, pr[op] + current_pr});
  } else if (op == '(') {
    current_pr += 2;
  } else if (op == ')') {
    current_pr -= 2;
    std::cin >> op;
    if (!std::cin.eof()) {
      check_op(op, res, ops);
    }
  }
}

int64_t rec(std::vector<Value>& res) {
  if (!res.back().type) {
    char tmp_op = res.back().op;
    res.pop_back();
    int64_t v1 = rec(res);
    int64_t v2 = rec(res);
    return f[tmp_op](v2, v1);
  } else {
    int64_t tmp = res.back().number;
    res.pop_back();
    return tmp;
  }
  return 0;
}

int main() {
  f['-'] = [](int64_t& a, int64_t& b) { return a - b; };
  f['+'] = [](int64_t& a, int64_t& b) { return a + b; };
  f['*'] = [](int64_t& a, int64_t& b) { return a * b; };

  char c;
  int num;

  std::stack<std::pair<char, int>> ops;
  std::vector<Value> res;

  while (!std::cin.eof()) {
    std::cin >> num;
    if (std::cin.eof()) {
      break;
    } else if (!std::cin.fail()) {
      // std::cout << "num = " << num << std::endl;
      res.emplace_back(Value(num));
    }
    std::cin.clear();
    std::cin >> c;
    if (std::cin.eof()) {
      break;
    }
    // std::cout << "op  = " << c << std::endl;
    check_op(c, res, ops);
  }

  while (!ops.empty()) {
    res.emplace_back(Value(ops.top().first));
    ops.pop();
  }

  std::cout << res << std::endl;

  std::cout << rec(res) << std::endl;

  return 0;
}
