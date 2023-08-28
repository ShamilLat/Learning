#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
  int n, weight;
  std::cin >> n >> weight;
  int c[n], w[n];
  long double price[n];
  for (int i = 0; i < n; i++) {
    std::cin >> c[i] >> w[i];
    price[i] = (long double)c[i] / (long double)w[i];
  }
  for (int i = 0; i < n; i++) {
    for (int j = 1; j < n; j++) {
      if (price[j - 1] > price[j]) {
        std::swap(price[j - 1], price[j]);
        std::swap(c[j - 1], c[j]);
        std::swap(w[j - 1], w[j]);
      }
    }
  }

  int take_w = 0, i = n - 1;
  long double take_price = 0;
  while (take_w < weight && i >= 0) {
    int min_w = std::min(w[i], weight - take_w);
    take_w += min_w;
    take_price += price[i] * (long double)min_w;
    i--;
  }

  std::cout << std::fixed << std::setprecision(4) << take_price << std::endl;

  return 0;
}