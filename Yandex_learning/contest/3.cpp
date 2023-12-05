#include <limits.h>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  int n, m, q;
  cin >> n >> m >> q;

  vector<string> names;
  unordered_map<string, int> name_to_ind;
  vector<pair<int, int>> min_max(m, {INT_MIN, INT_MAX});
  unordered_map<int, long long> sums;
  unordered_map<int, vector<long long>> matrix;

  string tmp;
  for (int i = 0; i < m; i++) {
    cin >> tmp;
    name_to_ind[tmp] = i;
    names.push_back(tmp);
  }

  for (int i = 0; i < n; i++) {
    long long sum = 0, num;
    matrix[i] = {};
    for (int j = 0; j < m; j++) {
      cin >> num;
      matrix[i].push_back(num);
      sum += num;
    }
    sums[i] = sum;
  }

  char op;
  int num;
  for (int i = 0; i < q; i++) {
    cin >> tmp >> op >> num;
    if (op == '>') {
      min_max[name_to_ind[tmp]].first =
          max(min_max[name_to_ind[tmp]].first, num);
    } else {
      min_max[name_to_ind[tmp]].second =
          min(min_max[name_to_ind[tmp]].second, num);
    }
  }

  stack<int> to_delete;
  for (auto& name : names) {
    int index = name_to_ind[name];
    for (auto& i : matrix) {
      if (i.second[index] <= min_max[index].first ||
          i.second[index] >= min_max[index].second) {
        to_delete.push(i.first);
      }
    }
    while (!to_delete.empty()) {
      matrix.erase(to_delete.top());
      sums.erase(to_delete.top());
      to_delete.pop();
    }
  }

  long long res_sum = 0;
  for (auto& i : sums) {
    res_sum += i.second;
  }

  cout << res_sum << endl;
}
