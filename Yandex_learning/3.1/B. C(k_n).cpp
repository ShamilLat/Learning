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
  cout << fact(n) / (fact(n - k) * fact(k));
  return 0;
}