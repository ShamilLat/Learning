#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> a, vector<int> b) {
  vector<int> res;
  int i1 = 0, i2 = 0;
  while (i1 < a.size() && i2 < b.size()) {
    res.push_back((a[i1] < b[i2]) ? a[i1++] : b[i2++]);
  }
  while (i1 < a.size()) {
    res.push_back(a[i1++]);
  }
  while (i2 < b.size()) {
    res.push_back(b[i2++]);
  }

  return res;
}

int main() {
  int n;
  cin >> n;
  int first_m;
  cin >> first_m;
  vector<int> first_a(first_m);
  for (int i = 0; i < first_m; i++) {
    cin >> first_a[i];
  }
  sort(first_a.begin(), first_a.end());

  for (int i = 1; i < n; i++) {
    int m;
    cin >> m;
    vector<int> a(m);
    for (int j = 0; j < m; j++) {
      cin >> a[j];
    }
    sort(a.begin(), a.end());
    first_a = merge(first_a, a);
  }

  for (auto& it : first_a) {
    cout << it << " ";
  }
  cout << "\n";

  return 0;
}