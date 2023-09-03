#include <iostream>
#include <string>

using namespace std;

int R(int n, int m) {
  if (n == 0 && m == 0) {
    return 0;
  }
  return !(((n > 0) ? R(n - 1, m) : 1) && ((m > 0) ? R(n, m - 1) : 1) &&
           ((n > 0 && m > 0) ? R(n - 1, m - 1) : 1));
}

int main() {
  string answer[2] = {"Loose", "Win"};
  int n, m;
  cin >> n >> m;
  cout << answer[R(n, m)] << "\n";
  return 0;
}