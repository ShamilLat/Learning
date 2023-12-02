#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  int n, m, q;
  cin >> n >> m >> q;

  vector<string> names;
  vector<long long> sums;
  unordered_map<string, unordered_map<long long, vector<int>>> nums;
  unordered_set<int> rows;

  string tmp;
  for (int i = 0; i < m; i++) {
    cin >> tmp;
    names.push_back(tmp);
    nums[tmp] = {};
  }

  for (int i = 0; i < n; i++) {
    long long sum = 0, num;
    for (int j = 0; j < m; j++) {
      cin >> num;
      sum += num;
      if (!nums[names[j]].contains(num)) {
        nums[names[j]][num] = {};
      }
      nums[names[j]][num].push_back(i);
    }
    sums.push_back(sum);
  }

  char op;
  int num;
  for (int i = 0; i < q; i++) {
    cin >> tmp >> op >> num;
    for (auto& tmp_map : nums[tmp]) {
      if ((op == '>' && tmp_map.first <= num) ||
          (op == '<' && tmp_map.first >= num)) {
        rows.insert(tmp_map.second.begin(), tmp_map.second.end());
      }
    }
  }

  long long res_sum = 0;
  for (int i = 0; i < n; i++) {
    if (!rows.contains(i)) {
      res_sum += sums[i];
    }
  }

  cout << res_sum << endl;
}