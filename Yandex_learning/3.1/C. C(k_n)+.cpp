#include <iostream>

using namespace std;

int fact(int n) {
  int res = 1;
  while (n > 1) {
    res *= n;
    n--;
  }
  return res;
}

int main() {
  int n, k;
  cin >> n >> k;
  cout << fact(n + k - 1) / (fact(n - 1) * fact(k));
  return 0;
}