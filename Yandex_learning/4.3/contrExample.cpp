#include <iostream>
#include <ostream>
#include <vector>

int MaxPairwiseProduct(std::vector<int>& A, int n) {
  int cnt = 0;
  int m1 = A[0];
  int m2 = A[1];
  if (++cnt && m2 > m1) {
    std::swap(m1, m2);
  }

  for (int i = 2; i < n; i++) {
    if (++cnt && A[i] > m1) {
      // m2 = m1;
      // m1 = A[i];
    } else if (++cnt && A[i] > m2) {
      // m2 = A[i];
    }
  }

  // std::cout << "count of cmp:" << cnt << std::endl;
  return cnt;
}

std::ostream& operator<<(std::ostream& out, std::vector<int>& a) {
  for (auto i : a) {
    out << i << " ";
  }
  return out;
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  a[0] = n;
  for (int i = 1; i < n; i++) {
    // std::cout << i << " ";
    a[i] = i;
  }
  int cnt = MaxPairwiseProduct(a, n);

  if (2 * cnt > 3 * n) {
    std::cout << "Yes\n";
    std::cout << a << std::endl;
  } else {
    std::cout << "No\n";
  }
  return 0;
}