#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

/*
Recent pings counter:
Return count of pings, those were made <= 3000 ms ago
*/

class RecentCounter {
 public:
  RecentCounter() {}

  int ping(int t) {
    pings.push_back(t);
    while (pings[it] < t - 3000) {
      it++;
    }
    return pings.size() - it;
  }

  vector<int> pings;
  int it = 0;
};

int main() {
  RecentCounter* obj = new RecentCounter();

  int num;
  while (cin >> num) {
    cout << obj->ping(num) << "\n";
  }

  return 0;
}