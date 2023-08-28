#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, k;
  std::cin >> n >> k;
  int current_num;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
    if (i == k - 1) {
      current_num = a[i];
    }
  }

  std::sort(a.begin(), a.end());

  int current_pos = 0, check = 1, wins = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == current_num) {
      current_pos = i;
      break;
    }
  }
  while (check && a.size() > 1) {
    // std::cout << "in while: pos = " << current_pos << ", num = " <<
    // current_num
    //           << std::endl;
    std::vector<int> new_a;
    if (current_pos % 2) {  // позиция нечетная
      if (a.size() % 2) {   // размер нечетный
        for (int i = 1; i < a.size(); i += 2) {
          new_a.push_back(a[i]);
        }
        new_a.push_back(a[a.size() - 1]);
      } else {  // размер четный
        for (int i = 1; i < a.size(); i += 2) {
          new_a.push_back(a[i]);
        }
      }
    } else {               // позиция четная
      if (a.size() % 2) {  // размер нечетный
        for (int i = 0; i < a.size(); i += 2) {
          new_a.push_back(a[i]);
        }
      } else {  // размер четный
        for (int i = 2; i < a.size(); i += 2) {
          new_a.push_back(a[i]);
        }
        new_a.push_back(a[a.size() - 1]);
      }
    }
    a = new_a;
    check = 0;
    for (int i = 0; i < a.size(); i++) {
      if (a[i] == current_num) {
        wins++;
        current_pos = i;
        check = 1;
        break;
      }
    }
    // for (int i = 0; i < a.size(); i++) {
    //   std::cout << a[i] << " ";
    // }
    // std::cout << std::endl;
  }

  std::cout << wins << std::endl;

  return 0;
}