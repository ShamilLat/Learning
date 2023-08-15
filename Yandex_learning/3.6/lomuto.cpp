#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, vector<int> a) {
  for (int i = 0; i < a.size(); i++) {
    out << a[i] << " ";
  }
  return out;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  int m = a[0];
  int i = 0;
  for (int j = 1; j < n; j++) {
    if (a[j] <= m) {
      i++;
      if (i != j) {
        swap(a[i], a[j]);
      }
    }
  }
  swap(a[0], a[i]);

  cout << a << "\n";
  return 0;
}