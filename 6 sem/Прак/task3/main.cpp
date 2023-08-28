#include <omp.h>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

// omp_get_wtime();

struct Matrix {
  Matrix() {}
  Matrix(int cube_n_) : cube_n(cube_n_) { n = cube_n * cube_n * cube_n; }

  ~Matrix() {
    if (is_generated) {
      free(col);
      free(val);
    }
  }

  void make_step(int i, int j, int pos, double& sum) {
    val[i * m + pos] = cos(i * j + M_PI);
    sum += std::abs(val[i * m + pos]);
    col[i * m + pos] = j;
  }

  void generate() {
    col = (int*)calloc(n * m, sizeof(*col));
    val = (double*)calloc(n * m, sizeof(*val));
    for (int i = 0; i < n * m; i++) {
      col[i] = -1;
      val[i] = 0;
    }
    is_generated = true;

    for (int k = 0; k < cube_n; k++) {
      for (int j = 0; j < cube_n; j++) {
        for (int i = 0; i < cube_n; i++) {
          int i_matrix = k * cube_n * cube_n + j * cube_n + i;
          int j_matrix, val_col_pos;
          double str_sum = 0;
          if (k > 0) {
            j_matrix = i_matrix - cube_n * cube_n;
            val_col_pos = 0;
            make_step(i_matrix, j_matrix, val_col_pos, str_sum);
          }
          if (j > 0) {
            j_matrix = i_matrix - cube_n;
            val_col_pos = 1;
            make_step(i_matrix, j_matrix, val_col_pos, str_sum);
          }
          if (i > 0) {
            j_matrix = i_matrix - 1;
            val_col_pos = 2;
            make_step(i_matrix, j_matrix, val_col_pos, str_sum);
          }
          if (i < cube_n - 1) {
            j_matrix = i_matrix + 1;
            val_col_pos = 4;
            make_step(i_matrix, j_matrix, val_col_pos, str_sum);
          }
          if (j < cube_n - 1) {
            j_matrix = i_matrix + cube_n;
            val_col_pos = 5;
            make_step(i_matrix, j_matrix, val_col_pos, str_sum);
          }
          if (k < cube_n - 1) {
            j_matrix = i_matrix + cube_n * cube_n;
            val_col_pos = 6;
            make_step(i_matrix, j_matrix, val_col_pos, str_sum);
          }
          j_matrix = i_matrix;
          val_col_pos = 3;
          // for (int s = 0; s < m; s++) {
          //   str_sum += abs(val[i_matrix * m + s]);
          // }
          val[i_matrix * m + val_col_pos] = 1.5 * str_sum;
          col[i_matrix * m + val_col_pos] = j_matrix;
        }
      }
    }
  }

  double* for_m_condition() {
    double* b = (double*)calloc(n, sizeof(*b));
    for (int i = 0; i < n; i++) {
      int j = 0;
      while (col[i * m + j] != i) {
        j++;
      }
      b[i] = val[i * m + j];
    }
    return b;
  }

  std::string to_string() {
    std::stringstream ss;
    ss << "cube_n = " << cube_n;
    ss << "\nn = " << n;
    ss << "\nval:\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ss.width(3);
        ss << val[i * m + j] << " ";
      }
      ss << "\n";
    }
    ss << "\ncol:\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        ss.width(3);
        ss << col[i * m + j] << " ";
      }
      ss << "\n";
    }
    return ss.str();
  }

  int cube_n = 0, n = 0;
  int m = 7;
  bool is_generated = false;
  int* col;
  double* val;
};

void generate_vector(Matrix& matrix, double* b) {
  for (int i = 0; i < matrix.n; i++) {
    for (int j = 0; j < matrix.m; j++)
      b[i] += matrix.val[i * matrix.m + j];
  }
}

// y -> x
void copy_massive(double* x, double* y, int n) {
  for (int i = 0; i < n; i++) {
    x[i] = y[i];
  }
}

void copy_massive_omp(double* x, double* y, int n) {
  auto nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);

#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    x[i] = y[i];
  }
}

void copy_massive_with_m(double* x, double* y, int n, double* m) {
  double sum = 0;
  for (int i = 0; i < n; i++) {
    sum += y[i] * m[i];
  }
  for (int i = 0; i < n; i++) {
    x[i] = sum;
  }
}

void copy_massive_with_m_omp(double* x, double* y, int n, double* m) {
  double sum = 0;
  auto nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);

#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < n; i++) {
    sum += y[i] * m[i];
  }
#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    x[i] = sum;
  }
}

void set_value(double* x, int value, int n) {
  for (int i = 0; i < n; i++) {
    x[i] = value;
  }
}

void set_value_omp(double* x, int value, int n) {
  auto nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);

#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    x[i] = value;
  }
}

double dot(double* x, double* y, int n) {
  double res = 0.0;

  for (int i = 0; i < n; i++)
    res += x[i] * y[i];

  return res;
}

double dot_omp(double* x, double* y, int n) {
  double res = 0.0;

  auto nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);

#pragma omp parallel for reduction(+ : res)
  for (int i = 0; i < n; i++)
    res += x[i] * y[i];

  return res;
}

void axpby(double a, double* x, double b, double* y, int n, double* res) {
  for (int i = 0; i < n; i++) {
    res[i] = a * x[i] + b * y[i];
  }
}

void axpby_omp(double a, double* x, double b, double* y, int n, double* res) {
  auto nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);

#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    res[i] = a * x[i] + b * y[i];
  }
}

void spmv(Matrix& matrix, double* x, double* y) {
  int n = matrix.n;
  int m = matrix.m;

  for (int i = 0; i < n; i++) {
    y[i] = 0.0;
    for (int j = 0; j < m; j++) {
      if (matrix.col[i * m + j] != -1) {
        y[i] += x[matrix.col[i * m + j]] * matrix.val[i * m + j];
      }
    }
  }
}

void spmv_omp(Matrix& matrix, double* x, double* y) {
  int n = matrix.n;
  int m = matrix.m;

  auto nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);

#pragma omp parallel for
  for (int i = 0; i < n; i++) {
    y[i] = 0.0;
    for (int j = 0; j < m; j++) {
      if (matrix.col[i * m + j] != -1) {
        y[i] += x[matrix.col[i * m + j]] * matrix.val[i * m + j];
      }
    }
  }
}

double get_norm(const double* input_massive, int size) {
  double sum = 0.0;
  for (int i = 0; i < size; i++) {
    sum += input_massive[i] * input_massive[i];
  }
  return std::sqrt(sum);
}

double get_solution_difference(double* x, int size) {
  for (int i = 0; i < size; i++)
    x[i]--;
  return get_norm(x, size);
}

double get_residual(Matrix& matrix, double* x, double* b) {
  double* difference = (double*)calloc(matrix.n, sizeof(*difference));
  spmv(matrix, x, difference);
  for (int i = 0; i < matrix.n; i++)
    difference[i] -= b[i];

  auto return_norm = get_norm(difference, matrix.n);
  free(difference);
  return return_norm;
}

void equality(double* test1, double* test2, bool& check, int n) {
  for (int i = 0; i < n; i++) {
    if (test1[i] != test2[i]) {
      check = false;
    }
  }
}

int testing_omp_functions() {
  // set_value
  // copy_massive
  // copy_massive_m
  // dot
  // axpby
  // spmv

  double alpha = 1, betta = -1;
  int m = 5;
  int n = m * m * m;
  double* x = (double*)calloc(n, sizeof(*x));
  double* y = (double*)calloc(n, sizeof(*y));
  for (int i = 0; i < n; i++) {
    x[i] = cos(i * i);
    y[i] = sin(i * i);
  }
  bool check = true;
  double* test_1 = (double*)calloc(n, sizeof(*test_1));
  double* test_2 = (double*)calloc(n, sizeof(*test_2));

  int sum = 0;

  // SET_VALUE
  set_value(test_1, 5, n);
  set_value_omp(test_2, 5, n);
  equality(test_1, test_2, check, n);
  if (check)
    sum++;
  // std::cout << "Test set_value " << (check ? "OK\n" : "ERROR\n");
  check = true;

  // COPY
  copy_massive(test_1, x, n);
  copy_massive_omp(test_2, x, n);
  equality(test_1, test_2, check, n);
  if (check)
    sum++;
  // std::cout << "Test copy " << (check ? "OK\n" : "ERROR\n");
  check = true;

  // DOT
  auto t1 = dot(x, y, n);
  auto t2 = dot_omp(x, y, n);
  // std::cout << "DOT t1 = " << t1 << " t2 = " << t2 << std::endl;
  check = (t1 - t2 < 1e-6);
  if (check)
    sum++;
  // std::cout << "Test dot " << (check ? "OK\n" : "ERROR\n");
  check = true;

  // AXPBY
  set_value(test_1, 0, n);
  set_value(test_2, 0, n);
  axpby(alpha, x, betta, y, n, test_1);
  axpby_omp(alpha, x, betta, y, n, test_2);
  auto t3 = get_norm(test_1, n);
  auto t4 = get_norm(test_2, n);
  check = (t3 == t4);
  if (check)
    sum++;
  // std::cout << "Test axpby " << (check ? "OK\n" : "ERROR\n");
  check = true;

  // SPMV
  set_value(test_1, 0, n);
  set_value(test_2, 0, n);
  Matrix test(m);
  test.generate();
  spmv(test, x, test_1);
  spmv_omp(test, x, test_2);
  equality(test_1, test_2, check, n);
  if (check)
    sum++;
  // std::cout << "Test spmv " << (check ? "OK\n" : "ERROR\n");

  free(test_1);
  free(test_2);
  free(x);
  free(y);

  return sum;
}

int main(int argc, char* argv[]) {
  int nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);
  std::cout << "Threads number: " << omp_get_max_threads() << std::endl;

  // Testing omp versions of functions
  std::cout << "Testing Started\n";
  auto test_time_1 = omp_get_wtime();
  int testing_res = testing_omp_functions();
  auto test_time_2 = omp_get_wtime();
  std::cout << "Testing Finished: " << (testing_res == 5 ? "OK\n" : "ERROR\n");
  std::cout << "Time: " << test_time_2 - test_time_1 << "\n";

  int cube_size = 50;
  int maxiter = 100;
  if (argc > 2) {
    cube_size = atoi(argv[1]);
    maxiter = atoi(argv[2]);
  }

  std::cout << "Cube size = " << cube_size << std::endl;
  std::cout << "Maxiter = " << maxiter << std::endl << std::endl;

  int n = cube_size * cube_size * cube_size;

  double* b = (double*)calloc(n, sizeof(*b));
  double* copy_b = (double*)calloc(n, sizeof(*copy_b));

  auto get_time_1 = omp_get_wtime();

  Matrix matrix(cube_size);
  matrix.generate();

  generate_vector(matrix, b);
  // copy_massive(copy_b, b, n);
  copy_massive_omp(copy_b, b, n);

  auto get_time_2 = omp_get_wtime();
  std::cout << "Generation time: " << get_time_2 - get_time_1 << "\n";

  // std::cout << matrix.to_string();

  double* m = matrix.for_m_condition();
  double* x = (double*)calloc(n, sizeof(*x));
  double* p = (double*)calloc(n, sizeof(*p));
  double* z = (double*)calloc(n, sizeof(*z));
  double* q = (double*)calloc(n, sizeof(*q));
  double* r;

  bool convergence = false;
  int k = 1;

  double cg_time = 0;
  int iterations = 0;

  for (int run = 0; run < 100; run) {
    copy_massive(b, copy_b, n);

    auto time1 = omp_get_wtime();

    // set_value(x, 0, n);
    set_value_omp(x, 0, n);

    r = b;
    convergence = false;
    k = 1;

    double ro = 0, pr_ro = 0, betta = 0, alpha = 0;
    while (!convergence) {
      // copy_massive_with_m(z, r, n, m);
      copy_massive_with_m_omp(z, r, n, m);
      // copy_massive(z, r, n);
      // copy_massive_omp(z, r, n);
      pr_ro = ro;
      ro = dot(r, z, n);

      if (k == 1) {
        // copy_massive(p, z, n);
        copy_massive_omp(p, z, n);
      } else {
        betta = ro / pr_ro;
        // axpby(1, z, betta, p, n, p);
        axpby_omp(1, z, betta, p, n, p);
      }
      // spmv(matrix, p, q);
      spmv_omp(matrix, p, q);
      // alpha = ro / dot(p, q, n);
      alpha = ro / dot_omp(p, q, n);

      // axpby(1, x, alpha, p, n, x);
      // axpby(1, r, -alpha, q, n, r);
      axpby_omp(1, x, alpha, p, n, x);
      axpby_omp(1, r, -alpha, q, n, r);

      if (get_norm(r, n) < 1e-9 || k > maxiter) {
        convergence = true;
      } else
        k++;
    }

    auto time2 = omp_get_wtime();

    iterations++;
    cg_time += time2 - time1;
    run = run + 1;
  }

  std::cout << "Iterations = " << iterations << std::endl;
  std::cout << "All Time = " << cg_time << std::endl;
  std::cout << "Medium CG Time: " << cg_time / iterations << std::endl;
  std::cout << "\n||Ax-b|| = " << get_residual(matrix, x, copy_b) << std::endl;
  std::cout << "Solution difference: " << get_solution_difference(x, n)
            << std::endl;

  free(b);
  free(copy_b);
  free(m);
  free(x);
  free(p);
  free(z);
  free(q);
  return 0;
}

/*
bsub < 50_0.lsf && bsub < 50_1.lsf && bsub < 50_2.lsf && bsub < 50_3.lsf && bsub
< 50_4.lsf && bsub < 50_5.lsf && bsub < 100_0.lsf && bsub < 100_1.lsf && bsub <
100_2.lsf && bsub < 100_3.lsf && bsub < 100_4.lsf && bsub < 100_5.lsf && bsub <
200_0.lsf && bsub < 200_1.lsf && bsub < 200_2.lsf && bsub < 200_3.lsf && bsub <
200_4.lsf && bsub < 200_5.lsf

*/