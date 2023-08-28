#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
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

vector<int> MergeSort(vector<int>& a) {
  if (a.size() == 1) {
    return a;
  }
  int mid = (a.end() - a.begin()) / 2;
  vector<int> first_a(a.begin(), a.begin() + mid);
  vector<int> second_a(a.begin() + mid, a.end());
  vector<int> sort_first = MergeSort(first_a);
  vector<int> sort_second = MergeSort(second_a);
  return merge(sort_first, sort_second);
}

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
  cout << MergeSort(a) << "\n";
  return 0;
}
