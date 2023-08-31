#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

// bool MemoizedKnapsack(std::vector<int>& golds,
//                       std::map<std::pair<int, int>, bool>& pack,
//                       int w,
//                       int i) {
//   if (!pack.contains({w, i})) {
//     if (i == 0 && w == 0) {
//       pack[{w, i}] = true;
//     } else if (i == 0 && w > 0) {
//       pack[{w, i}] = false;
//     } else if (i > 0 && golds[i - 1] > w) {
//       pack[{w, i}] = MemoizedKnapsack(golds, pack, w, i - 1);
//     } else {
//       pack[{w, i}] = MemoizedKnapsack(golds, pack, w, i - 1) ||
//                      MemoizedKnapsack(golds, pack, w - golds[i - 1], i - 1);
//     }
//   }
//   return pack[{w, i}];
// }

int main() {
  int w, n;
  std::cin >> w >> n;
  std::vector<int> golds(n);
  for (int i = 0; i < n; i++) {
    std::cin >> golds[i];
  }

  std::vector<std::vector<bool>> table(w + 1, std::vector<bool>(n + 1, false));

  table[0][0] = true;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= w; j++) {
      if (golds[i - 1] > j) {
        table[j][i] = table[j][i - 1];
      } else {
        table[j][i] = table[j][i - 1] || table[j - golds[i - 1]][i - 1];
      }
    }
  }

  int max_w = 0;
  for (int i = 0; i <= w; i++) {
    if (table[i][n]) {
      max_w = i;
    }
  }

  std::cout << max_w << std::endl;

  return 0;
}