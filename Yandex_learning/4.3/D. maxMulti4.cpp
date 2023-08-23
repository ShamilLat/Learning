#include <compare>
#include <cstdlib>
#include <iostream>
#include <vector>

std::vector<int> generate_test(int n) {
  std::vector<int> a(n);
  int check;
  std::cin >> check;
  for (int i = 0; i < n; i++) {
    // a[i] = rand() % 40000 - 20000;
    a[i] = rand() % check - check / 2;
  }
  return a;
}

int64_t check_mul(std::vector<int>& a) {
  int64_t max = (int64_t)a[0] * (int64_t)a[1] * (int64_t)a[2] * (int64_t)a[3];
  for (int i = 0; i < a.size(); i++) {
    for (int j = i + 1; j < a.size(); j++) {
      for (int k = j + 1; k < a.size(); k++) {
        for (int m = k + 1; m < a.size(); m++) {
          if ((int64_t)a[i] * (int64_t)a[j] * (int64_t)a[k] * (int64_t)a[m] >
              max) {
            max = (int64_t)a[i] * (int64_t)a[j] * (int64_t)a[k] * (int64_t)a[m];
          }
        }
      }
    }
  }
  return max;
}

std::ostream& operator<<(std::ostream& out, std::vector<int>& a) {
  for (auto i : a) {
    out << i << " ";
  }
  return out;
}

int main() {
  int n;
  std::cin >> n;

  // auto vec = generate_test(n);
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
  }

  std::qsort(&vec[0], vec.size(), sizeof(int),
             [](const void* x, const void* y) {
               const int arg1 = *static_cast<const int*>(x);
               const int arg2 = *static_cast<const int*>(y);
               const auto cmp = (arg1 <=> arg2);
               if (cmp < 0)
                 return -1;
               if (cmp > 0)
                 return 1;
               return 0;
             });

  int min_mul1 = vec[0] * vec[1], min_mul2 = vec[2] * vec[3],
      max_mul1 = vec[n - 1] * vec[n - 2], max_mul2 = vec[n - 3] * vec[n - 4];

  int64_t res = std::max(std::max((int64_t)max_mul1 * (int64_t)max_mul2,
                                  (int64_t)max_mul1 * (int64_t)min_mul1),
                         (int64_t)min_mul1 * (int64_t)min_mul2);

  // auto ans = check_mul(vec);
  // std::cout << vec << "\n";
  // if (ans == res) {
  //   std::cout << "True\n";
  //   std::cout << ans << std::endl;
  // } else {
  //   std::cout << "False\n";
  //   std::cout << "answer is " << ans << "\nfunc answer is " << res <<
  //   std::endl; std::cout << max_mul1 << " " << max_mul2 << " " << min_mul2 <<
  //   " "
  //             << min_mul1 << std::endl;
  // }

  std::cout << res << std::endl;

  return 0;
}
