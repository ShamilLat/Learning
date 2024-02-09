#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/*
Даны точки на прямой. Есть ли вертикальная прямая, которая делит эти точки
симместрично
*/

bool f(const std::vector<int>& vec) {
  int min = INT_MAX;
  int max = INT_MIN;
  unordered_set<int> points;

  for (int i = 0; i < vec.size(); i++) {
    min = min(vec[i], min);
    max = max(vec[i], max);

    points.insert(vec[i]);
  }

  int dist = max + min;
  for (int i = 0; i < vec.size(); i++) {
    if (!points.contains(dist - vec[i])) {
      return false;
    }
  }

  return true;
}

int main() {
  int n;
  cin >> n;
  vector<int> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> vec[i];
  }

  cout << n << " " << f(vec) << endl;
}