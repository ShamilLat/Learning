#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int res = 1;
  while (n) {
    res *= n;
    n--;
  }
  cout << res;
  return 0;
}