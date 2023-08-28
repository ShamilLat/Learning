#include <iostream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& out, vector<int>& a) {
  for (int i = 0; i < a.size(); i++) {
    out << a[i] << " ";
  }
  return out;
}

void quick_sort(vector<int>& a) {
  if (a.size() <= 1) {
    return;
  }
  if (a.size() == 2) {
    if (a[0] > a[1]) {
      swap(a[0], a[1]);
    }
    return;
  }
  int min = a[0], max = a[0];
  for (auto i : a) {
    if (i < min) {
      min = i;
    } else if (i > max) {
      max = i;
    }
  }
  int m = (min + max) / 2;
  vector<int> a_small, a_large;
  for (int i = 0; i < a.size(); i++) {
    if (a[i] <= m) {
      a_small.push_back(a[i]);
    } else if (a[i] > m) {
      a_large.push_back(a[i]);
    }
  }

  quick_sort(a_small);
  quick_sort(a_large);
  a_small.insert(a_small.end(), a_large.begin(), a_large.end());
  a = a_small;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  quick_sort(a);
  cout << a << endl;

  return 0;
}