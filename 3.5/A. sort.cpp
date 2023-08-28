#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    int min_num = a[i], poz = i;
    for (int j = i; j < n; j++) {
      if (min_num > a[j]) {
        min_num = a[j];
        poz = j;
      }
    }
    swap(a[i], a[poz]);
  }

  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
  return 0;
}