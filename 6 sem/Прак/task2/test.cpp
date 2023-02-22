#include <sys/time.h>
#include <time.h>
#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

double get_random_number() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> random_num(0, 100);

  return random_num(gen);
}

double get_norm(const std::vector<double>& x) {
  double res = 0.0;
  for (const auto& i : x) {
    res += i * i;
  }
  return std::sqrt(res);
}

/* static inline double timer() {
  struct timeval tm;

  gettimeofday(&tm, NULL);
  return ((double)tm.tv_sec + (double)tm.tv_usec * 1.e-6);
} */

auto get_time() {
  return std::chrono::high_resolution_clock::now();
}

/* std::time_t get_current_date_time() {
  const auto date_time = std::chrono::system_clock::now();
  const auto date_time_t = std::chrono::system_clock::to_time_t(date_time);
  return date_time_t;
} */

int main() {
  double speed[8];

  double a, t1, b;
  char t;
  std::cin >> t >> a >> t >> t1 >> t;
  speed[0] = 1;

  for (int i = 0; i < 5; i++) {
    std::cin >> t >> a >> t >> b >> t;
    speed[i + 1] = t1 / b;
  }

  int st = 1;
  for (int i = 0; i < 6; i++) {
    std::cout << "(" << st << "," << speed[i] << ")\n";
    st *= 2;
  }
  std::cout << "\n\n";

  st = 1;
  for (int i = 0; i < 6; i++) {
    std::cout << "(" << st << "," << speed[i] / st << ")\n";
    st *= 2;
  }
}

/*
int main() {
  int n = 5;

  std::vector<std::vector<int>> a;
  for (int i = 0; i < n; i++) {
    std::vector<int> b;
    for (int j = 0; j < n; j++) {
      b.push_back(i * n + j);
    }
    a.push_back(b);
    b.clear();
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << a[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << std::endl;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      std::swap(a[i][j], a[j][i]);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << a[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  for (auto& it : a[0]) {
    it -= 1;
    std::cout << it << " ";
  }
  std::cout << std::endl;
}

int main() {
  double* a = (double*)calloc(5, sizeof(*a));
  for (int i = 0; i < 5; i++) {
    a[i] = i * 3;
  }
  for (int i = 0; i < 5; i++) {
    std::cout << a[i] << " ";
  }
  std::cout << "\n" << sizeof(a);

}

int main() {
  std::cout << get_random_number() << "\n";

  auto t1 = get_time();

  int k = 0;
  for (int i = 0; i < 1000000000; i++) {
    k++;
  }

  auto t2 = get_time();

  std::chrono::duration<float> d = t2 - t1;
  std::cout << d.count() << "\n";
} */