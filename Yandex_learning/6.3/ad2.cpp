#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, k, w;
  std::cin >> n >> k >> w;
  std::vector<std::pair<int, int>> data(k);
  int input_week;
  for (int i = 0; i < k; i++) {
    std::cin >> data[i].first >> input_week;
    data[i].second = std::min(input_week, w);
  }

  std::sort(data.begin(), data.end(), std::greater<std::pair<int, int>>());

  int total_profit = 0, used_weeks = 0, j = 0;
  while (used_weeks < n * w && j < k) {
    int tmp = std::min(data[j].second, n * w - used_weeks);
    used_weeks += tmp;
    total_profit += data[j].first * tmp;
    j++;
  }

  std::cout << total_profit << std::endl;

  return 0;
}