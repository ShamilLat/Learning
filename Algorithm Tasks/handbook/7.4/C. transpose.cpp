#include <algorithm>
#include <iostream>
#include <vector>

int binary_search(int n, std::vector<int>& a, int q) {
  int maxIndex = n - 1, minIndex = 0, midIndex;
  while (maxIndex >= minIndex) {
    midIndex = (maxIndex + minIndex) / 2;
    if (q < a[midIndex]) {
      maxIndex = midIndex - 1;
    } else if (q > a[midIndex]) {
      minIndex = midIndex + 1;
    }
  }
  if (q > a[midIndex]) {
    midIndex++;
  }
  return midIndex;
}

int count_inversions(std::vector<int>& numbers) {
  if (numbers.size() <= 1) {
    return 0;
  }
  int mid = (numbers.end() - numbers.begin()) / 2;
  std::vector<int> left_vector(numbers.begin(), numbers.begin() + mid);
  std::vector<int> right_vector(numbers.begin() + mid, numbers.end());

  int left_cnt = count_inversions(left_vector);
  int right_cnt = count_inversions(right_vector);

  std::sort(right_vector.begin(), right_vector.end());

  int inv = 0;
  for (auto& i : left_vector) {
    inv += binary_search(right_vector.size(), right_vector, i);
  }

  return left_cnt + inv + right_cnt;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> num(n);
  for (int i = 0; i < n; i++) {
    std::cin >> num[i];
  }
  std::cout << count_inversions(num) << std::endl;
  return 0;
}