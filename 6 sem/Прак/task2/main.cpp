#include <mpi.h>
#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

struct Matrix {
  Matrix() {}
  Matrix(int _size) : size(_size) {}

  ~Matrix() {
    if (matrix_generated) {
      free(matrix);
    }
  }

  void generate_matrix() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> random_num(0, 100);
    matrix = (double*)calloc(size * size, sizeof(*matrix));
    matrix_generated = true;

    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        matrix[i * size + j] = random_num(gen);
        // matrix[i * size + j] = (i + 1) / (j + 1) + 10;
      }
    }
  }

  void transpose() {
    for (int i = 0; i < size; i++) {
      for (int j = i + 1; j < size; j++) {
        std::swap(matrix[i * size + j], matrix[j * size + i]);
      }
    }
  }

  std::string to_string() {
    std::stringstream ss;
    ss << "size = " << size << "\n";
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        ss << matrix[i * size + j] << " ";
      }
      ss << "\n";
    }
    return ss.str();
  }

  int size = 100;
  double* matrix;
  bool matrix_generated = false;
};

double* multiply_matrix_vector(Matrix& matrix, double* b) {
  int size = matrix.size;
  double* x = (double*)calloc(size, sizeof(*x));

  for (int i = 0; i < size; i++) {
    x[i] = 0;
    for (int j = 0; j < size; j++) {
      x[i] += matrix.matrix[i * size + j] * b[j];
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

double get_residual(Matrix& matrix, double* x, double* b) {
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

void generate_vector(const Matrix& matrix, double* b) {
  for (int i = 0; i < matrix.size; i++) {
    for (int j = 0; j < matrix.size; j++)
      b[i] += matrix.matrix[i * matrix.size + j];
  }
}

double get_mpi_time() {
  return MPI_Wtime();
}

auto get_time() {
  return std::chrono::high_resolution_clock::now();
}

int main(int argc, char* argv[]) {
  int size = 0;
  if (argc < 2) {
    size = 1000;
  } else {
    size = atoi(argv[1]);
  }

  MPI_Init(&argc, &argv);

  int mpi_size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    std::cout << "Size = " << size << std::endl;
    std::cout << "Threads count " << mpi_size << std::endl;
  }

  int matrix_buf_size = size / mpi_size;
  int r = size % mpi_size;
  if (rank < r) {
    matrix_buf_size++;
  }

  double** matrix_buf = (double**)calloc(matrix_buf_size, sizeof(*matrix_buf));
  for (int i = 0; i < matrix_buf_size; i++) {
    matrix_buf[i] = (double*)calloc(size, sizeof(**matrix_buf));
  }
  double* b = (double*)calloc(size, sizeof(*b));
  double* copy_b = (double*)calloc(size, sizeof(*copy_b));
  double* a_k = (double*)calloc(size, sizeof(*a_k));

  double* x = (double*)calloc(size, sizeof(*x));
  double* all_x = (double*)calloc(size, sizeof(*all_x));

  Matrix matrix_a(size);

  if (rank == 0) {
    matrix_a.generate_matrix();

    generate_vector(matrix_a, b);

    matrix_a.transpose();
  }

  // Рассылка столбцов по буферам процессов
  for (int i = 0; i < size / mpi_size; i++) {
    MPI_Scatter(matrix_a.matrix + i * mpi_size * size, size, MPI_DOUBLE,
                matrix_buf[i], size, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  }

  // Учёт некратности размера матрицы и количества MPI процессов
  if (rank == 0) {
    for (int i = 1; i < r; i++) {
      MPI_Send(matrix_a.matrix + size * mpi_size * (size / mpi_size) + i * size,
               size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
    }
    if (r != 0) {
      for (int i = 0; i < size; i++) {
        matrix_buf[matrix_buf_size - 1][i] =
            *(matrix_a.matrix + mpi_size * size * (size / mpi_size) + i);
      }
      // matrix_buf[matrix_buf_size - 1] =
      //     matrix_a.matrix + mpi_size * size * (size / mpi_size);
    }
  } else if (rank < r) {
    MPI_Recv(matrix_buf[matrix_buf_size - 1], size, MPI_DOUBLE, 0, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  if (size % mpi_size != 0) {
    if (rank == 0)
      MPI_Send(b, size, MPI_DOUBLE, size % mpi_size, 0, MPI_COMM_WORLD);
    else if (rank == size % mpi_size)
      MPI_Recv(b, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  //////////////////////////////////////////////////

  MPI_Barrier(MPI_COMM_WORLD);

  auto time1 = get_mpi_time();

  for (int i = 0; i < size - 1; i++) {
    if (rank == i % mpi_size) {
      for (int j = i; j < size; j++) {
        a_k[j - i] = matrix_buf[i / mpi_size][j];
      }

      double a_k_norm = get_norm(a_k, size - i);
      a_k[0] += number_sign(a_k[0]) * a_k_norm;
      a_k_norm = get_norm(a_k, size - i);

      for (int j = 0; j < size - i; j++) {
        a_k[j] /= a_k_norm;
      }
    }

    MPI_Bcast(a_k, size - i, MPI_DOUBLE, i % mpi_size, MPI_COMM_WORLD);

    for (int column = i / mpi_size; column < matrix_buf_size; column++) {
      if (column * mpi_size + rank >= i) {
        double sum = 0.0;
        for (int j = 0; j < size - i; j++)
          sum += 2.0 * a_k[j] * matrix_buf[column][j + i];
        for (int j = 0; j < size - i; j++)
          matrix_buf[column][j + i] -= sum * a_k[j];
      }
    }

    if (rank == size % mpi_size) {
      double sum = 0.0;
      for (int j = 0; j < size - i; j++)
        sum += 2.0 * a_k[j] * b[j + i];
      for (int j = 0; j < size - i; j++)
        b[j + i] -= sum * a_k[j];
    }
  }

  auto time2 = get_mpi_time();

  //

  if (size % mpi_size != 0) {
    if (rank == size % mpi_size) {
      MPI_Send(b, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else if (rank == 0) {
      MPI_Recv(copy_b, size, MPI_DOUBLE, size % mpi_size, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
    }
  } else if (rank == 0) {
    for (int i = 0; i < size; i++)
      copy_b[i] = b[i];
  }

  MPI_Barrier(MPI_COMM_WORLD);

  auto time3 = get_mpi_time();

  // Gauss
  for (int i = size - 1; i >= 0; i--) {
    if (rank == i % mpi_size) {
      if (mpi_size > 1)
        MPI_Recv(b, size, MPI_DOUBLE, (i + 1) % mpi_size, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
      x[i] = b[i] / matrix_buf[i / mpi_size][i];
      for (int j = 0; j <= i; j++)
        b[j] -= x[i] * matrix_buf[i / mpi_size][j];

    } else if (rank == (i + 1) % mpi_size) {
      if (mpi_size > 1)
        MPI_Send(b, size, MPI_DOUBLE, i % mpi_size, 0, MPI_COMM_WORLD);
    }
  }

  auto time4 = get_mpi_time();

  MPI_Allreduce(x, all_x, size, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

  double mpi_household_time = time2 - time1;
  double mpi_gauss_time = time4 - time3;
  double mpi_algorithm_time = time4 - time1;

  double household_time, gauss_time, algorithm_time;

  MPI_Reduce(&mpi_household_time, &household_time, 1, MPI_DOUBLE, MPI_MAX, 0,
             MPI_COMM_WORLD);
  MPI_Reduce(&mpi_gauss_time, &gauss_time, 1, MPI_DOUBLE, MPI_MAX, 0,
             MPI_COMM_WORLD);
  MPI_Reduce(&mpi_algorithm_time, &algorithm_time, 1, MPI_DOUBLE, MPI_MAX, 0,
             MPI_COMM_WORLD);

  // Сбор всех подбуферов в общий буфер
  for (int i = 0; i < size / mpi_size; i++) {
    MPI_Gather(matrix_buf[i], size, MPI_DOUBLE,
               matrix_a.matrix + i * mpi_size * size, size, MPI_DOUBLE, 0,
               MPI_COMM_WORLD);
  }

  // Учитываем некратность размера матриц и количества процессов
  for (int i = 1; i < r; i++) {
    if (rank == i)
      MPI_Send(matrix_buf[matrix_buf_size - 1], size, MPI_DOUBLE, 0, 0,
               MPI_COMM_WORLD);
    else if (rank == 0)
      MPI_Recv(matrix_a.matrix + mpi_size * size * (size / mpi_size) + i * size,
               size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  if (r > 0 && rank == 0) {
    for (int i = 0; i < size; i++) {
      matrix_a.matrix[mpi_size * size * (size / mpi_size) + i] =
          matrix_buf[matrix_buf_size - 1][i];
    }
  }

  if (rank == 0) {
    matrix_a.transpose();

    std::cout << "Hosehold time: " << household_time << std::endl;
    std::cout << "Gauss time: " << gauss_time << std::endl;
    std::cout << "Algorithm time: " << algorithm_time << std::endl;
    // std::cout << "Total time: " << total_time.count() << std::endl;

    std::cout << "\n||Ax-b|| = " << get_residual(matrix_a, all_x, copy_b)
              << std::endl;
    std::cout << "Solution difference: " << get_solution_difference(all_x, size)
              << std::endl;
    std::cout << "(" << mpi_size << "," << algorithm_time << ")\n";
  }

  MPI_Barrier(MPI_COMM_WORLD);

  free(b);
  free(copy_b);
  free(a_k);
  free(x);
  free(all_x);
  for (int i = 0; i < matrix_buf_size; i++) {
    free(matrix_buf[i]);
  }
  free(matrix_buf);

  MPI_Finalize();

  return 0;
}

/*
mpisubmit.pl -p 1 main && mpisubmit.pl -p 2 main && mpisubmit.pl -p 4 main && mpisubmit.pl -p 8 main && mpisubmit.pl -p 16 main && mpisubmit.pl -p 32 main && mpisubmit.pl -p 1 main -- 3000 && mpisubmit.pl -p 2 main -- 3000 && mpisubmit.pl -p 4 main -- 3000 && mpisubmit.pl -p 8 main -- 3000 && mpisubmit.pl -p 16 main -- 3000 && mpisubmit.pl -p 32 main -- 3000 && mpisubmit.pl -p 1 main -- 6000 && mpisubmit.pl -p 2 main -- 6000 && mpisubmit.pl -p 4 main -- 6000 && mpisubmit.pl -p 8 main -- 6000 && mpisubmit.pl -p 16 main -- 6000 && mpisubmit.pl -p 32 main -- 6000

*/