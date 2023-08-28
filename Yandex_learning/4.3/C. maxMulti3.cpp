#include <cstdlib>
#include <iostream>
#include <vector>

std::vector<int> generate_test(int n) {
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = rand() % 400000 - 200000;
    // a[i] = rand() % 10 - 5;
  }
  return a;
}

int64_t check_mul(std::vector<int>& a) {
  int64_t max = (int64_t)a[0] * (int64_t)a[1] * (int64_t)a[2];
  for (int i = 0; i < a.size(); i++) {
    for (int j = i + 1; j < a.size(); j++) {
      for (int k = j + 1; k < a.size(); k++) {
        if ((int64_t)a[i] * (int64_t)a[j] * (int64_t)a[k] > max) {
          max = (int64_t)a[i] * (int64_t)a[j] * (int64_t)a[k];
        }
      }
    }
  }
  return max;
}

int64_t max_m(std::vector<int>& a) {
  int max1 = a[0], max2 = a[1], max3 = a[2], min1, min2;
  if (max1 < max2) {
    std::swap(max1, max2);
  }
  if (max2 < max3) {
    std::swap(max2, max3);
  }
  if (max1 < max2) {
    std::swap(max1, max2);
  }
  min1 = max3;
  min2 = max2;

  int check_min = 0;

  for (int i = 3; i < a.size(); i++) {
    if (max1 <= a[i]) {
      max3 = max2;
      max2 = max1;
      max1 = a[i];
      check_min++;
    } else if (max2 <= a[i]) {
      max3 = max2;
      max2 = a[i];
      check_min++;
    } else if (max3 <= a[i]) {
      max3 = a[i];
      check_min++;
    }
    if (min1 >= a[i]) {
      min2 = min1;
      min1 = a[i];
      check_min++;
    } else if (min2 >= a[i]) {
      min2 = a[i];
      check_min++;
    }
  }

  // std::cout << max1 << " " << max2 << " " << max3 << " " << min2 << " " <<
  // min1 << std::endl;
  if (check_min == 0) {
    // std::cout << "A\n";
    return (int64_t)max1 * (int64_t)max2 * (int64_t)max3;
  } else if (check_min == 1) {
    // std::cout << "C\n";
    return std::max((int64_t)max1 * (int64_t)max2 * (int64_t)max3,
                    (int64_t)min1 * (int64_t)min2 * (int64_t)max1);
  }  // std::cout << "B\n";
  return std::max((int64_t)max1 * (int64_t)max2 * (int64_t)max3,
                  (int64_t)max1 * (int64_t)min2 * (int64_t)min1);
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

  // auto ans = check_mul(vec);
  // std::cout << vec << "\n";
  // if (ans == max_m(vec)) {
  //   std::cout << "True\n";
  //   std::cout << ans << std::endl;
  // } else {
  //   std::cout << "False\n";
  //   std::cout << "answer is " << ans << "\nfunc answer is " << max_m(vec)
  //             << std::endl;
  // }
  std::cout << max_m(vec) << std::endl;

  return 0;
}
