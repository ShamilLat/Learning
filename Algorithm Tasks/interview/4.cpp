#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

int f(std::string& a, std::string& b) {
  std::unordered_map<char, int> count_symbols;
  for (auto& i : b) {
    if (!count_symbols.contains(i)) {
      count_symbols[i] = 0;
    }
    count_symbols[i]++;
  }

  int alphabet_size = count_symbols.size();
  int con = 0;
  int res_count = 0;

  for (int i = 0; i < b.size(); i++) {
    count_symbols[a[i]]--;
    if (!count_symbols[a[i]]) {
      con++;
    } else if (count_symbols[a[i]] == -1) {
      con--;
    }
  }
  if (con == alphabet_size) {
    res_count++;
  }

  for (int i = 0; i < a.size() - b.size(); i++) {
    count_symbols[a[i]]++;
    if (!count_symbols[a[i]]) {
      con++;
    } else if (count_symbols[a[i]] == 1) {
      con--;
    }

    count_symbols[a[i + b.size()]]--;
    if (!count_symbols[a[i + b.size()]]) {
      con++;
    } else if (count_symbols[a[i + b.size()]] == -1) {
      con--;
    }

    if (con == alphabet_size) {
      res_count++;
    }
  }

  return res_count;
}

int main() {
  std::string a, b;
  std::cin >> a >> b;

  std::cout << f(a, b) << std::endl;

  return 0;
}