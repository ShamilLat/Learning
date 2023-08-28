#include <iostream>

using namespace std;

void towers(int n, int from, int to) {
  if (n == 1) {
    cout << from << " " << to << "\n";
    return;
  }
  int left = 6 - from - to;
  towers(n - 1, from, left);
  cout << from << " " << to << "\n";
  towers(n - 1, left, to);
}

int main() {
  int n;
  cin >> n;
  int cnt = 1;
  for (int i = 0; i < n; i++) {
    cnt *= 2;
  }
  cout << cnt - 1 << "\n";
  towers(n, 1, 3);
  return 0;
}