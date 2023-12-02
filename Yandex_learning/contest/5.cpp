#include <iostream>
#include <vector>

using namespace std;

int calculateSimilarity(const vector<int>& arr1,
                        const vector<int>& arr2,
                        int i = 0) {
  int minLength = min(arr1.size(), arr2.size());
  while (i < minLength && arr1[i] == arr2[i]) {
    i++;
  }

  return i;
}

int main() {
  int n;
  cin >> n;

  vector<vector<int>> vec(n);

  for (int i = 0; i < n; ++i) {
    int k;
    cin >> k;
    vec[i].resize(k);
    for (int j = 0; j < k; ++j) {
      cin >> vec[i][j];
    }
  }

  vector<int> prefs(n, 0);

  long long sum = 0;
  for (int i = 1; i < n; i++) {
    prefs[i] = calculateSimilarity(vec[0], vec[i]);
    sum += prefs[i];
  }

  for (int i = 1; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (prefs[i] == prefs[j]) {
        sum += calculateSimilarity(vec[i], vec[j], prefs[i]);
      } else {
        sum += min(prefs[i], prefs[j]);
      }
    }
  }

  cout << sum << endl;

  return 0;
}
