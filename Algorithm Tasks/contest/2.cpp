#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  unordered_map<int, int> cards_1;
  unordered_map<int, int> cards_2;
  int cnt1 = 0, cnt2 = 0;
  int n, m, q;
  cin >> n >> m >> q;

  int cnt = 0, num;
  for (int i = 0; i < n; i++) {
    cin >> num;
    cards_1[num]++;
    cnt1++;
  }
  for (int i = 0; i < m; i++) {
    cin >> num;
    if (cards_1[num] > 0) {
      cards_1[num]--;
      cnt1--;
    } else {
      cards_2[num]++;
      cnt2++;
    }
  }

  vector<int> res;

  int type, card;
  char player;
  for (int i = 0; i < q; i++) {
    cin >> type >> player >> card;
    if (type == 1) {
      if (player == 'A') {
        if (cards_2[card] > 0) {
          cards_2[card]--;
          cnt2--;
        } else {
          cards_1[card]++;
          cnt1++;
        }
      }
      if (player == 'B') {
        if (cards_1[card] > 0) {
          cards_1[card]--;
          cnt1--;
        } else {
          cards_2[card]++;
          cnt2++;
        }
      }
    }
    if (type == -1) {
      if (player == 'A') {
        if (cards_1[card] == 0) {
          cards_2[card]++;
          cnt2++;
        } else {
          cards_1[card]--;
          cnt1--;
        }
      }
      if (player == 'B') {
        if (cards_2[card] == 0) {
          cards_1[card]++;
          cnt1++;
        } else {
          cards_2[card]--;
          cnt2--;
        }
      }
    }
    // cout << cnt1 + cnt2 << " ";

    res.push_back(cnt1 + cnt2);
  }
  for (auto& i : res) {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}
