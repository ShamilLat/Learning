#include <omp.h>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

struct Matrix {
  Matrix() {}
  Matrix(int _size) : size(_size) {}

  void generate_matrix() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> random_num(0, 100);
    for (int i = 0; i < size; i++) {
      std::vector<double> row;
      for (int j = 0; j < size; j++) {
        // row.push_back((i + 1) / (j + 1) + 100);
        row.push_back(random_num(gen));
      }
      matrix.push_back(row);
      row.clear();
    }
  }

  void transpose() {
    for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
        std::swap(matrix[i][j], matrix[j][i]);
      }
    }
  }

  int size;
  std::vector<std::vector<double> > matrix;
};

double* multiply_matrix_vector(const Matrix& matrix, const double* b) {
  int size = matrix.size;
  double* x = (double*)calloc(size, sizeof(*x));

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      x[i] += matrix.matrix[i][j] * b[j];
    }
  }
  return x;
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

double get_residual(const Matrix& matrix, const double* x, const double* b) {
  double* difference = multiply_matrix_vector(matrix, x);
  for (int i = 0; i < matrix.size; i++)
    difference[i] -= b[i];

  auto return_norm = get_norm(difference, matrix.size);
  free(difference);
  return return_norm;
}

double number_sign(double number) {
  return number > 0.0 ? 1.0 : number < 0.0 ? -1.0 : 0.0;
}

void generate_vector(const Matrix& matrix, std::vector<double>& b) {
  for (int i = 0; i < matrix.size; i++) {
    double sum = 0.0;
    for (int j = 0; j < matrix.size; j++)
      sum += matrix.matrix[i][j];
    b.push_back(sum);
  }
}

auto get_time() {
  return std::chrono::high_resolution_clock::now();
}

int main(int argc, char* argv[]) {
  int nthreads = omp_get_max_threads();
  omp_set_num_threads(nthreads);
  std::cout << "\n//////////////////\nMax threads count " << nthreads
            << std::endl;

  int size = 0;
  if (argc < 2) {
    size = 1000;
  } else {
    size = atoi(argv[1]);
  }

  std::cout << "Size = " << size << std::endl;

  auto generation_time_start = get_time();
  std::cout << "Gen start\n";
  Matrix matrix_a(size);
  matrix_a.generate_matrix();

  std::vector<double> b;
  generate_vector(matrix_a, b);
  auto generation_time_end = get_time();
  std::cout << "Gen end\n";

  //////////////////////////////////////////////////

  double* a_k = (double*)calloc(size, sizeof(*a_k));

  matrix_a.transpose();

  auto time1 = get_time();

  for (int i = 0; i < size - 1; i++) {
#pragma omp parallel for
    for (int j = i; j < size; j++)
      a_k[j - i] = matrix_a.matrix[i][j];

    double a_k_norm = get_norm(a_k, size - i);
    a_k[0] += number_sign(a_k[0]) * a_k_norm;
    a_k_norm = get_norm(a_k, size - i);

#pragma omp parallel for
    for (int j = 0; j < size - i; j++)
      a_k[j] /= a_k_norm;

#pragma omp parallel for
    for (int column = i; column < size; column++) {
      double sum = 0.0;
      for (int j = 0; j < size - i; j++)
        sum += 2.0 * a_k[j] * matrix_a.matrix[column][i + j];
      for (int j = 0; j < size - i; j++)
        matrix_a.matrix[column][i + j] -= sum * a_k[j];
    }

    double sum = 0.0;
    for (int j = 0; j < size - i; j++)
      sum += 2.0 * a_k[j] * b[j + i];
    for (int j = 0; j < size - i; j++)
      b[j + i] -= sum * a_k[j];
  }

  auto time2 = get_time();

  double* copy_b = (double*)calloc(size, sizeof(*copy_b));
  for (int i = 0; i < size; i++)
    copy_b[i] = b[i];

  // Gauss
  double* x = (double*)calloc(size, sizeof(*x));
  for (int i = size - 1; i >= 0; i--) {
    for (int j = i + 1; j < size; j++)
      b[i] -= matrix_a.matrix[j][i] * x[j];

    x[i] = b[i] / matrix_a.matrix[i][i];
  }

  auto time3 = get_time();

  matrix_a.transpose();

  std::chrono::duration<float> generation_time =
      generation_time_end - generation_time_start;
  std::chrono::duration<float> household_time = time2 - time1;
  std::chrono::duration<float> gauss_time = time3 - time2;
  std::chrono::duration<float> algorithm_time = time3 - time1;
  std::chrono::duration<float> total_time = time3 - generation_time_start;

  // std::cout << "\nGeneration time: " << generation_time.count() << std::endl;
  std::cout << "Hosehold time: " << household_time.count() << std::endl;
  std::cout << "Gauss time: " << gauss_time.count() << std::endl;
  std::cout << "Algorithm time: " << algorithm_time.count() << std::endl;
  // std::cout << "Total time: " << total_time.count() << std::endl;

  std::cout << "\n||Ax-b|| = " << get_residual(matrix_a, x, copy_b)
            << std::endl;
  std::cout << "Solution difference: " << get_solution_difference(x, size)
            << std::endl;
  std::cout << "(" << nthreads << "," << algorithm_time.count() << ")\n";

  free(a_k);
  free(copy_b);
  free(x);

  return 0;
}