#include <iostream>
#include <tuple>
#include <vector>

std::tuple<std::vector<int>, int> merge(std::vector<int>& a,
                                        std::vector<int>& b) {
  std::vector<int> res;
  int inversions = 0;
  int i1 = 0, i2 = 0;
  while (i1 < a.size() && i2 < b.size()) {
    if (a[i1] < b[i2]) {
      res.push_back(a[i1++]);
    } else {
      res.push_back(b[i2++]);
      inversions += (a.size() - i1);
    }
  }
  while (i1 < a.size()) {
    res.push_back(a[i1++]);
  }
  while (i2 < b.size()) {
    res.push_back(b[i2++]);
  }

  return {res, inversions};
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

  auto [new_numbers, cnt] = merge(left_vector, right_vector);
  numbers = new_numbers;

  return left_cnt + cnt + right_cnt;
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