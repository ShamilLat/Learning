#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

void rec(std::vector<Value>& res, int add_pr = 0) {}

int main() {
  std::string s;
  std::cin >> s;

  std::stringstream ss(s);

  char c;
  while (ss >> c) {
    std::cout << c << " ";
  }
  std::cout << "\n";

  //   std::vector<int> res;
}
