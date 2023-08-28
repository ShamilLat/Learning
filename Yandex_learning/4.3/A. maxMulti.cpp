#include <iostream>

int main() {
  int max1, max2;
  int n;
  std::cin >> n;
  std::cin >> max1 >> max2;
  if (max1 < max2) {
    std::swap(max1, max2);
  }
  int num;
  for (int i = 2; i < n; i++) {
    std::cin >> num;
    if (num >= max1) {
      max2 = max1;
      max1 = num;
    } else if (num >= max2) {
      max2 = num;
    }
  }
  int64_t result = (int64_t)max1 * (int64_t)max2;
  std::cout << result << "\n";
}