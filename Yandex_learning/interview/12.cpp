#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>
#include <unordered_map>
#include <vector>

template <typename Type>
std::ostream& operator<<(std::ostream& out, std::vector<Type>& vec) {
  for (int i = 0; i < vec.size(); i++) {
    out << vec[i] << " ";
  }
  return out;
}

std::vector<int> f(const std::vector<int>& a, const std::vector<int>& b) {
  std::vector<int> res(a.size());
  std::unordered_map<int, int> count_numbers_a;
  std::unordered_map<int, int> count_numbers_b;
  int cnt = 0;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == b[i]) {
      cnt++;
    } else {
      if (!count_numbers_a.contains(a[i])) {
        count_numbers_a[a[i]] = 0;
      }
      count_numbers_a[a[i]]++;

      if (!count_numbers_b.contains(b[i])) {
        count_numbers_b[b[i]] = 0;
      }
      count_numbers_b[b[i]]++;

      if (count_numbers_a.contains(b[i]) && count_numbers_a[b[i]] - 1 >= 0) {
        cnt++;
        count_numbers_a[b[i]]--;
        count_numbers_b[b[i]]--;
      }

      if (count_numbers_b.contains(a[i]) && count_numbers_b[a[i]] - 1 >= 0) {
        cnt++;
        count_numbers_b[a[i]]--;
        count_numbers_a[a[i]]--;
      }
    }
    res[i] = cnt;
  }

  return res;
}

std::vector<int> stress_f(const std::vector<int>& a,
                          const std::vector<int>& b) {
  std::vector<int> res(a.size());
  std::vector<std::pair<int, bool>> local_a(a.size());
  std::vector<int> local_b(b);

  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j <= i; j++) {
      local_a[j] = {a[j], true};
    }
    int cnt = 0;
    for (int j = 0; j <= i; j++) {
      for (int k = 0; k <= i; k++) {
        if (local_b[j] == local_a[k].first && local_a[k].second) {
          cnt++;
          local_a[k].second = false;
          break;
        }
      }
    }
    res[i] = cnt;
  }

  return res;
}

int main() {
  for (int n = 5; n <= 50; n += 5) {
    for (int i = 0; i < 10; i++) {
      std::vector<int> a(n), b(n);
      for (int j = 0; j < n; j++) {
        a[j] = rand() % n;
      }
      for (int j = 0; j < n; j++) {
        b[j] = rand() % n;
      }
      auto res = f(a, b);
      auto res2 = stress_f(a, b);

      bool check = true;
      for (int j = 0; j < n; j++) {
        if (res[j] != res2[j]) {
          check = false;
        }
      }
      if (check) {
        std::cout << "Test OK\n";
        // std::cout << a << std::endl;
        // std::cout << b << std::endl << std::endl;
      } else {
        std::cout << "Test not OK:" << std::endl;

        std::cout << a << std::endl;
        std::cout << b << std::endl;
        std::cout << res << std::endl;
        std::cout << res2 << std::endl << std::endl;
      }
    }
  }
}