#include <cmath>
#include <iostream>
#include <vector>
#include "solver.hpp"

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  double c[m], p[n];
  double lambda[m - 1];

  for (int i = 0; i < m; i++) {
    cin >> c[i];
    if (i < m - 1)
      lambda[i] = 1.0;
  }

  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }

  double w[n][m];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> w[i][j];
    }
  }

  ListSolver solver(n, c[m - 1]);
  int iter_count = 20000, iter_number = 1;
  double eps = 0.001;
  double loss = 0.0;
  while (iter_number <= iter_count) {
    vector<double> copy_p(n, 0.0);
    double sum_c = 0.0;
    for (int i = 0; i < n; i++) {
      double sum_pi = 0.0;
      for (int j = 0; j < m - 1; j++) {
        if (!i) {
          sum_c += c[j] * lambda[j];
        }
        sum_pi += w[i][j] * lambda[j];
      }
      copy_p[i] = p[i] - sum_pi;
    }

    vector<double> copy_w(n, 0.0);
    for (int i = 0; i < n; i++) {
      copy_w[i] = w[i][m - 1];
    }

    vector<bool> result(n, false);
    pair<double, vector<int>> values = solver.solve(copy_p, copy_w);
    double max_p = values.first;
    for (auto& it : values.second) {
      result[it] = true;
    }

    if (eps > abs(max_p + sum_c - loss)) {
      break;
    } else {
      loss = max_p + sum_c;
    }

    vector<double> D(m - 1, 0.0);
    for (int i = 0; i < m - 1; i++) {
      double sum_w = 0.0;
      for (int j = 0; j < n; j++) {
        if (result[j])
          sum_w += w[j][i];
      }
      D[i] = c[i] - sum_w;
    }

    double D_abs = 0.0;
    for (int i = 0; i < m - 1; i++) {
      D_abs += D[i] * D[i];
    }
    D_abs = sqrt(D_abs);

    for (int i = 0; i < m - 1; i++) {
      lambda[i] = max(
          lambda[i] - 1.0 / (double)iter_number * D[i] / (D_abs + eps), 0.0);
    }

    iter_number++;
  }

  cout << loss << endl;
  for (int i = 0; i < m - 1; ++i) {
    cout << lambda[i] << endl;
  }
}