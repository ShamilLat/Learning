#include <algorithm>
#include <iostream>
#include <vector>

struct NumbersData {
  NumbersData() {}
  NumbersData(int n) {
    after.resize(n, 0);
    before.resize(n, 0);
    after_bigger.resize(n, 0);
    before_smaller.resize(n, 0);
  }

  std::vector<int> after;
  std::vector<int> before;
  std::vector<int> after_bigger;
  std::vector<int> before_smaller;
};

std::tuple<std::vector<int>, int> merge(std::vector<int>& a,
                                        std::vector<int>& b,
                                        NumbersData& data) {
  std::vector<int> res;
  int inversions = 0;
  int i1 = 0, i2 = 0;
  while (i1 < a.size() && i2 < b.size()) {
    if (a[i1] < b[i2]) {
      data.after_bigger[a[i1]] += b.size() - i2;
      data.after[a[i1]] += i2;
      res.push_back(a[i1++]);
    } else {
      data.before[b[i2]] += a.size() - i1;
      data.before_smaller[b[i2]] += i1;
      res.push_back(b[i2++]);
      inversions += (a.size() - i1);
    }
  }
  while (i1 < a.size()) {
    data.after[a[i1]] += b.size();
    res.push_back(a[i1++]);
  }
  while (i2 < b.size()) {
    data.before_smaller[b[i2]] += a.size();
    res.push_back(b[i2++]);
  }

  return {res, inversions};
}

int count_inversions(std::vector<int>& numbers, NumbersData& data) {
  if (numbers.size() <= 1) {
    return 0;
  }
  int mid = (numbers.end() - numbers.begin()) / 2;
  std::vector<int> left_vector(numbers.begin(), numbers.begin() + mid);
  std::vector<int> right_vector(numbers.begin() + mid, numbers.end());
  int left_cnt = count_inversions(left_vector, data);
  int right_cnt = count_inversions(right_vector, data);

  auto [new_numbers, cnt] = merge(left_vector, right_vector, data);
  numbers = new_numbers;

  return left_cnt + cnt + right_cnt;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> numbers(n);

  int input = 0;
  for (int i = 0; i < n; i++) {
    std::cin >> input;
    numbers[i] = input - 1;
  }

  NumbersData data(n);
  int total_inversions = count_inversions(numbers, data);
  int min_count = total_inversions;

  for (int i = n - 1; i >= 0; i--) {
    total_inversions = total_inversions + data.before[i] - data.after[i] +
                       data.before_smaller[i] - data.after_bigger[i];
    min_count = std::min(min_count, total_inversions);
  }

  std::cout << min_count << "\n";

  return 0;
}