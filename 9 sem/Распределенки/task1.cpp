#include <algorithm>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

vector<pair<int, int>> comps;
void add_comp(int first, int second) {
  comps.push_back({first, second});
}

void comparator(vector<int>& vec, int a, int b) {
  if (a < vec.size() && b < vec.size() && vec[a] > vec[b]) {
    swap(vec[a], vec[b]);
  }
}

int S(int first1, int first2, int step, int n, int m) {
  if (n * m < 1) {
    return 0;
  }

  if (n == 1 && m == 1) {
    add_comp(first1, first2);
    return 1;
  }

  int n1, m1, i, ret = 0;
  n1 = n - n / 2;
  m1 = m - m / 2;
  ret = max(ret, S(first1, first2, 2 * step, n1, m1));
  ret = max(ret, S(first1 + step, first2 + step, 2 * step, n - n1, m - m1));

  for (i = 1; i < n - 1; i += 2) {
    add_comp(first1 + step * i, first1 + step * (i + 1));
  }

  if (n % 2 == 0) {
    add_comp(first1 + step * (n - 1), first2);
    i = 1;
  } else {
    i = 0;
  }

  for (; i < m - 1; i += 2) {
    add_comp(first2 + step * i, first2 + step * (i + 1));
  }

  return ret + 1;
}

int B(int first, int step, int count) {
  if (count < 2) {
    return 0;
  }
  if (count == 2) {
    add_comp(first, first + step);
    return 1;
  }
  int count1 = count / 2 + count % 2;

  int ret = 0;
  ret = max(ret, B(first, step, count1));
  ret = max(ret, B(first + step * count1, step, count - count1));

  ret += S(first, first + step * count1, step, count1, count - count1);

  return ret;
}

int main(int argc, char* argv[]) {
  int n;
  if (argc < 2) {
    cout << "Need input n: ";
    cin >> n;
    cout << "\n";
  } else {
    n = atoi(argv[1]);
  }

  cout << n << " 0 0\n";

  int tact_count = B(0, 1, n);

  int c_size = comps.size();
  for (auto& comp : comps) {
    cout << comp.first << " " << comp.second << "\n";
  }
  cout << c_size << "\n";
  cout << tact_count << "\n";

  if (argc > 2 && strcmp(argv[2], "test") == 0) {
    if (n > 24) {
      cout << "n must be >= 1 and <= 24\n";
      return 0;
    }
    cout << "TESTING" << endl;
    int number = 1;
    for (int i = 0; i < n; i++) {
      number *= 2;
    }
    number--;
    while (number >= 0) {
      bool check = true;
      int c_num = number, it = n - 1;
      vector<int> test(n, 0);
      while (c_num) {
        test[it] = c_num % 2;
        it--;
        c_num /= 2;
      }
      vector<int> copy_test(test);
      sort(copy_test.begin(), copy_test.end());
      for (auto& comp : comps) {
        comparator(test, comp.first, comp.second);
      }

      for (int i = 0; i < n; i++) {
        if (test[i] != copy_test[i]) {
          check = false;
          break;
        }
      }
      if (!check) {
        cout << "NOT OK: " << number << "\n";
      }
      number--;
    }
    cout << "Test end" << endl;
  }

  return 0;
}