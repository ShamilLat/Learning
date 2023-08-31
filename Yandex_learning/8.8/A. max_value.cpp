#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

int main() {
  std::vector<int> numbers;
  std::vector<char> ops;

  std::map<char, std::function<int(int&, int&)>> f;
  f['-'] = [](int& a, int& b) { return a - b; };
  f['+'] = [](int& a, int& b) { return a + b; };
  f['*'] = [](int& a, int& b) { return a * b; };

  int num;
  char op;
  while (std::cin >> num) {
    numbers.push_back(num);
    if (std::cin >> op) {
      ops.push_back(op);
    }
  }

  int n = numbers.size();
  std::vector<std::vector<int>> mins(n, std::vector<int>(n, 0x7fffffff));
  std::vector<std::vector<int>> maxs(n, std::vector<int>(n, 0x80000000));

  for (int i = 0; i < n; i++) {
    mins[i][i] = numbers[i];
    maxs[i][i] = numbers[i];
  }
  for (int s = 1; s < n; s++) {
    for (int l = 0; l < n - s; l++) {
      int r = l + s;
      for (int m = l; m < r; m++) {
        int a = f[ops[m]](mins[l][m], mins[m + 1][r]);
        int b = f[ops[m]](mins[l][m], maxs[m + 1][r]);
        int c = f[ops[m]](maxs[l][m], mins[m + 1][r]);
        int d = f[ops[m]](maxs[l][m], maxs[m + 1][r]);
        mins[l][r] =
            std::min(std::min(std::min(a, b), std::min(c, d)), mins[l][r]);
        maxs[l][r] =
            std::max(std::max(std::max(a, b), std::max(c, d)), maxs[l][r]);
      }
    }
  }

  std::cout << maxs[0][n - 1] << std::endl;

  return 0;
}