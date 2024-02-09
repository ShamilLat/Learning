#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int l[n], r[n];
  int min_r = 100;
  for (int i = 0; i < n; i++) {
    cin >> l[i] >> r[i];
  }
  bool check = 1;
  while (check) {
    check = 0;
    int min_r = 100, taken_int = -1;

    for (int k = 0; k < n; k++) {
      if (r[k] > 0 && min_r > r[k]) {
        min_r = r[k];
        taken_int = k;
      }
    }
    for (int i = 0; i < n; i++) {
      if (l[i] && l[i] <= min_r && i != taken_int) {
        l[i] = 0;
        r[i] = 0;
        check = 1;
      } else if (i == taken_int) {
        l[i] = 0;
        r[i] = -1;
        check = 1;
      }
    }
  }

  int count = 0;
  for (int i = 0; i < n; i++) {
    if (r[i] == -1) {
      count++;
    }
  }

  cout << count;
  return 0;
}