#include <iostream>
#include <vector>

using namespace std;

struct State {
  State() : v(0), prev(0), w(0), p(0) {}
  State(int _v, int _prev, int _w, int _p) : v(_v), prev(_prev), w(_w), p(_p) {}

  bool operator>(State& other) { return (w <= other.w && p >= other.p); }

  int v;
  int prev;
  int w;
  int p;
};

int func(int it_number,
         vector<State> first,
         vector<State> second,
         int w[],
         int p[],
         int n,
         int c,
         vector<bool>& res) {
  vector<State> my_first, my_second;
  auto it1 = first.begin(), it2 = second.begin();

  while (it1 != first.end() && it2 != second.end()) {
    if (*it1 > *it2) {
      it2++;
    } else if (*it2 > *it1) {
      it1++;
    } else {
      if (it1->p < it2->p) {
        my_first.emplace(my_first.end(),
                         State{0, (int)(it1 - first.begin()), it1->w, it1->p});
        it1++;
      } else {
        my_first.emplace(my_first.end(),
                         State{it2->v, it2->prev, it2->w, it2->p});
        it2++;
      }
    }
  }

  while (it1 != first.end()) {
    my_first.emplace(my_first.end(),
                     State{0, (int)(it1 - first.begin()), it1->w, it1->p});
    it1++;
  }

  while (it2 != second.end()) {
    my_first.emplace(my_first.end(), State{it2->v, it2->prev, it2->w, it2->p});
    it2++;
  }

  // Working with second vector
  if (it_number < n - 1) {
    it1 = my_first.begin();
    for (; it1 != my_first.end(); it1++) {
      if (it1->w + w[it_number + 1] <= c) {
        my_second.emplace(
            my_second.end(),
            State{1, (int)(it1 - my_first.begin()), it1->w + w[it_number + 1],
                  it1->p + p[it_number + 1]});
      }
    }
  }

  int prev_number = (my_first.end() - 1)->prev;
  if (it_number < n) {
    prev_number = func(it_number + 1, my_first, my_second, w, p, n, c, res);
  }

  res[it_number] = my_first[prev_number].v;
  return my_first[prev_number].prev;
}

int main() {
  int n, c;
  cin >> n >> c;

  int w[n], p[n];

  for (int i = 0; i < n; i++) {
    cin >> w[i] >> p[i];
  }

  State begin{};

  vector<bool> result(n, false);
  vector<State> my_first, my_second;
  my_first.emplace(my_first.end(), begin);

  if (n > 0) {
    my_second.emplace(my_second.end(), State{1, 0, w[0], p[0]});
  }

  func(0, my_first, my_second, w, p, n, c, result);

  int sum = 0, cnt = 0;
  for (int i = 0; i < n; i++) {
    sum += p[i] * result[i];
    cnt += result[i];
  }
  cout << sum << " " << cnt << endl;

  for (int i = n - 1; i >= 0; i--) {
    if (result[i])
      cout << i << endl;
  }
  return 0;
}






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