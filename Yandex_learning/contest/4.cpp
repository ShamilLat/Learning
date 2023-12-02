#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
  vector<stack<int>> ab = {{}, {}};
  ab[0].push(0);
  ab[1].push(0);

  stack<int> deep;

  int n;
  cin >> n;
  vector<char> lang;
  vector<int> bar(n);
  for (int i = 0; i < n; i++) {
    char l;
    cin >> l;
    lang.push_back(l);
  }

  int num, cur_deep = -1;
  for (int i = 0; i < 2 * (n + 1); i++) {
    cin >> num;
    if (deep.empty() || deep.top() < num) {
      deep.push(num);
      cur_deep++;

      if (num != 0) {
        ab[lang[num - 1] - 'A'].push(cur_deep);
      }
    } else if (num != 0) {
      int pos = lang[num - 1] - 'A';

      int my_deep = ab[pos].top();
      ab[pos].pop();
      bar[num - 1] = my_deep - ab[pos].top() - 1;

      deep.pop();
      cur_deep--;
    }
  }
  for (auto& i : bar) {
    cout << i << " ";
  }
  cout << endl;
}