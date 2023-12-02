#include <iostream>
#include <vector>

using namespace std;

int main() {
  long long y1, m1, d1, h1, mt1, s1, y2, m2, d2, h2, mt2, s2;
  cin >> y1 >> m1 >> d1 >> h1 >> mt1 >> s1;
  cin >> y2 >> m2 >> d2 >> h2 >> mt2 >> s2;

  vector<int> months = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  y1 *= 365;
  y2 *= 365;
  long long sum = 0;
  for (int i = 0; i < m1 - 1; i++) {
    sum += months[i];
  }
  y1 += sum + d1;

  sum = 0;
  for (int i = 0; i < m2 - 1; i++) {
    sum += months[i];
  }
  y2 += sum + d2;

  y1 = y1 * 24 * 3600 + h1 * 3600 + mt1 * 60 + s1;
  y2 = y2 * 24 * 3600 + h2 * 3600 + mt2 * 60 + s2;

  y1 = abs(y1 - y2);
  cout << y1 / (3600 * 24) << " " << y1 % (3600 * 24) << endl;

  return 0;
}