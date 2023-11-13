#include <mpi.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

double frand()  // вещественное случайное число в диапазоне [0,1)
{
  return double(rand()) / RAND_MAX;
}

int eval(int* a, int n) {
  int sum = 0;
  for (int i = 0; i < n; i++)
    sum += a[i];
  return sum;
}

void init(int* P, int m, int n) {
  for (int k = 0; k < m; k++)
    for (int i = 0; i < n; i++)
      P[k * n + i] = rand() % 2;
}

void shuffle(int* P, int m, int n) {
  for (int k = 0; k < m; k++) {
    int l = rand() % m;
    for (int i = 0; i < n; i++)
      swap(P[k * n + i], P[l * n + i]);
  }
}

void select(int* P, int m, int n) {
  double pwin = 0.75;
  shuffle(P, m, n);
  for (int k = 0; k < m / 2; k++) {
    int a = 2 * k;
    int b = 2 * k + 1;
    int fa = eval(P + a * n, n);
    int fb = eval(P + b * n, n);
    double p = frand();
    if (fa < fb && p < pwin || fa > fb && p > pwin)
      for (int i = 0; i < n; i++)
        P[b * n + i] = P[a * n + i];
    else
      for (int i = 0; i < n; i++)
        P[a * n + i] = P[b * n + i];
  }
}

void crossover(int* P, int m, int n) {
  shuffle(P, m, n);
  for (int k = 0; k < m / 2; k++) {
    int a = 2 * k;
    int b = 2 * k + 1;
    int j = rand() % n;
    for (int i = j; i < n; i++)
      swap(P[a * n + i], P[b * n + i]);
  }
}

void mutate(int* P, int m, int n) {
  double pmut = 0.1;
  for (int k = 0; k < m; k++)
    for (int i = 0; i < n; i++)
      if (frand() < pmut)
        P[k * n + i] = 1 - P[k * n + i];
}

void printthebest(int* P, int m, int n) {
  int k0 = -1;
  int f0 = -1;
  for (int k = 0; k < m; k++) {
    int f = eval(P + k * n, n);
    if (f > f0) {
      f0 = f;
      k0 = k;
    }
  }
  cout << f0 << ": ";
  for (int i = 0; i < n; i++)
    cout << P[k0 * n + i];
  cout << endl;
}

void migrate(int* P, int n, int local_m, int world_rank, int world_size) {
  int migration_size = 50;  // Размер миграции, количество особей для обмена
  int* to_send = new int[n * migration_size];
  int* to_recv = new int[n * migration_size];

  // Выбор особей для миграции (в этом примере просто берем первых в списке)
  for (int i = 0; i < migration_size; ++i) {
    for (int j = 0; j < n; ++j) {
      to_send[i * n + j] = P[i * n + j];
    }
  }

  int next_rank = (world_rank + 1) % world_size;
  int prev_rank = (world_rank - 1 + world_size) % world_size;

  // Отправка и получение особей
  MPI_Sendrecv(to_send, n * migration_size, MPI_INT, next_rank, 0, to_recv,
               n * migration_size, MPI_INT, prev_rank, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);

  // Интеграция мигрировавших особей (заменяем последних в списке)
  for (int i = 0; i < migration_size; ++i) {
    for (int j = 0; j < n; ++j) {
      P[(local_m - 1 - i) * n + j] = to_recv[i * n + j];
    }
  }

  delete[] to_send;
  delete[] to_recv;
}

const double global_minimum_f0 = 0;

// void runGA(int n, int m, int T, int world_rank, int world_size) {
//   int local_m = m / world_size;  // Размер локальной субпопуляции
//   int* P = new int[n * local_m];
//   if (world_rank == 0) {
//     int* global_P = new int[n * m];
//     init(global_P, m, n);
//     MPI_Scatter(global_P, n * local_m, MPI_INT, P, n * local_m, MPI_INT, 0,
//                 MPI_COMM_WORLD);
//     delete[] global_P;
//   } else {
//     MPI_Scatter(0, n * local_m, MPI_INT, P, n * local_m, MPI_INT, 0,
//                 MPI_COMM_WORLD);
//   }

//   for (int t = 0; t < T; t++) {
//     select(P, local_m, n);
//     crossover(P, local_m, n);
//     mutate(P, local_m, n);
//     if (t % 5 == 0) {  // Миграция каждые 5 итераций, к примеру
//       migrate(P, n, local_m, world_rank, world_size);
//     }
//     printthebest(P, local_m, n);
//   }

//   delete[] P;
// }

void runGA(int n, int m, int T, int world_rank, int world_size) {
  int local_m = m / world_size;
  int* P = new int[n * local_m];
  if (world_rank == 0) {
    int* global_P = new int[n * m];
    init(global_P, m, n);
    MPI_Scatter(global_P, n * local_m, MPI_INT, P, n * local_m, MPI_INT, 0,
                MPI_COMM_WORLD);
    delete[] global_P;
  } else {
    MPI_Scatter(NULL, n * local_m, MPI_INT, P, n * local_m, MPI_INT, 0,
                MPI_COMM_WORLD);
  }

  double total_error;
  double local_error;
  // double global_minimum = 0;

  for (int t = 0; t < T; t++) {
    select(P, local_m, n);
    crossover(P, local_m, n);
    mutate(P, local_m, n);

    local_error = 0;
    for (int i = 0; i < local_m; ++i) {
      local_error += abs(eval(&P[i * n], n) - global_minimum_f0);
    }
    local_error /= local_m;

    MPI_Reduce(&local_error, &total_error, 1, MPI_DOUBLE, MPI_SUM, 0,
               MPI_COMM_WORLD);

    if (world_rank == 0) {
      total_error /= world_size;
      std::cout << "Итерация " << t << ", Средняя погрешность: " << total_error
                << std::endl;
    }

    if (t % 250 == 0) {  // Миграция каждые 5 итераций
      migrate(P, n, local_m, world_rank, world_size);
    }

    printthebest(P, local_m, n);
  }

  delete[] P;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int n = 500;
  int m = 500;
  int T = 1000;

  if (m % world_size != 0) {
    if (world_rank == 0) {
      std::cerr << "Ошибка: общий размер популяции должен быть кратен "
                   "количеству процессов MPI."
                << std::endl;
    }
    MPI_Finalize();
    return 1;
  }

  runGA(n, m, T, world_rank, world_size);

  MPI_Finalize();
  return 0;
}
