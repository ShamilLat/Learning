#include <algorithm>
#include <iostream>
#include <vector>

int check_lines(std::vector<int>& a, int k) {
  int min_point = a[0], new_point = min_point + k;
  int cnt = 1;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] > new_point) {
      cnt++;
      min_point = a[i];
      new_point = min_point + k;
    }
  }
  return cnt;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::sort(a.begin(), a.end());

  int size = 0;
  int min_size = 0, max_size = a[n - 1] - a[0], mid_size;
  while (max_size >= min_size) {
    mid_size = (max_size + min_size) / 2;
    int current_count = check_lines(a, mid_size);
    if (k >= current_count) {
      max_size = mid_size - 1;
      size = mid_size;
    } else if (k < current_count) {
      min_size = mid_size + 1;
    }
  }

  std::cout << std::max(size, mid_size) << std::endl;

  return 0;
}