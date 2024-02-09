#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Tree {
 public:
  unordered_map<long long, Tree*> nodes;
  long long cnt = 0;
};

long long func_cnt(long long num) {
  if (num == 1)
    return 0;

  return num * (num - 1) / 2;
}

long long SumCntDFS(Tree* node) {
  if (node == nullptr)
    return 0;

  long long sum = func_cnt(node->cnt);
  for (auto& pair : node->nodes) {
    sum += SumCntDFS(pair.second);
  }
  return sum;
}

int main() {
  int n;
  cin >> n;

  unordered_map<int, Tree*> prefs;
  Tree* cur_tree = nullptr;
  for (int i = 0; i < n; i++) {
    int k, num;
    cin >> k;
    cur_tree = nullptr;
    for (int j = 0; j < k; j++) {
      cin >> num;
      if (cur_tree == nullptr) {
        if (!prefs.contains(num)) {
          prefs[num] = new Tree;
        }
        cur_tree = prefs[num];
        cur_tree->cnt++;
      } else {
        if (!cur_tree->nodes.contains(num)) {
          cur_tree->nodes[num] = new Tree;
        }
        cur_tree = cur_tree->nodes[num];
        cur_tree->cnt++;
      }
    }
  }

  long long sum = 0;
  for (auto& i : prefs) {
    sum += SumCntDFS(i.second);
  }

  cout << sum << endl;

  return 0;
}
