#include <iostream>
#include <vector>

template <typename Type>
Type f(std::vector<Type>& vec) {  // Второй максимум
  Type max_1 = vec[0], max_2 = vec[1];
  if (max_1 < max_2) {
    std::swap(max_1, max_2);
  }
  for (int i = 2; i < vec.size(); i++) {
    if (vec[i] >= max_1) {
      max_2 = max_1;
      max_1 = vec[i];
    } else if (vec[i] > max_2) {
      max_2 = vec[i];
    }
  }

  return max_2;
}

template <typename Type>
Type f2(std::vector<Type>& vec) {  // Второй абсолютный максимум
  Type max_1 = vec[0], max_2 = vec[1];
  if (max_1 < max_2) {
    std::swap(max_1, max_2);
  }
  for (int i = 2; i < vec.size(); i++) {
    if (vec[i] > max_1) {
      max_2 = max_1;
      max_1 = vec[i];
    } else if (vec[i] > max_2 && vec[i] != max_1) {
      max_2 = vec[i];
    }
  }
  return max_2;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    std::cin >> vec[i];
  }
  std::cout << f(vec) << std::endl;
  std::cout << f2(vec) << std::endl;
}