#include <cstdlib>
#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& out, std::vector<int>& a) {
  for (int i = 0; i < a.size(); i++) {
    out << a[i] << " ";
  }
  return out;
}

void quick_sort(std::vector<int>& a) {
  if (a.size() <= 1) {
    return;
  }
  int random_pos = rand() % a.size();
  int m = a[random_pos];
  std::vector<int> a_small, a_large;
  int m_eq_cnt = 0;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] == m) {
      m_eq_cnt++;
    } else if (a[i] < m) {
      a_small.push_back(a[i]);
    } else {
      a_large.push_back(a[i]);
    }
  }
  quick_sort(a_small);
  quick_sort(a_large);
  for (int i = 0; i < m_eq_cnt; i++) {
    a_small.push_back(m);
  }
  a_small.insert(a_small.end(), a_large.begin(), a_large.end());
  a = a_small;
}

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  quick_sort(a);

  std::cout << a << std::endl;
}
