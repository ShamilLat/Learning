#include <iostream>

using namespace std;

int min(int a, int b) {
  return ((a > b) ? b : a);
}

int towers(int n) {
  if (n <= 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  if (n == 2) {
    return 3;
  }
  if (n == 3) {
    return 5;
  }
  return min(2 * towers(n - 3) + 7, 2 * towers(n - 4) + 15);
}

int main() {
  int n;
  cin >> n;
  cout << towers(n) << "\n";
  return 0;
}