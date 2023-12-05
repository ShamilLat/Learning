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
  vector<int> lang;
  vector<int> bar(n, 0);
  char l;
  for (int i = 0; i < n; i++) {
    cin >> l;
    lang.push_back(int(l - 'A'));
  }

  int num, cur_deep = -1;
  for (int i = 0; i < 2 * (n + 1); i++) {
    cin >> num;
    if (deep.empty() || deep.top() != num) {
      deep.push(num);
      cur_deep++;

      if (num != 0) {
        ab[lang[num - 1]].push(cur_deep);
      }
    } else if (num != 0) {
      int my_deep = ab[lang[num - 1]].top();
      ab[lang[num - 1]].pop();
      bar[num - 1] = my_deep - ab[lang[num - 1]].top() - 1;

      deep.pop();
      cur_deep--;
    }
  }
  for (auto& i : bar) {
    cout << i << " ";
  }
  cout << endl;
}