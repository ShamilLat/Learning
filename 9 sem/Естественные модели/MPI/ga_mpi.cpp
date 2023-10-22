#include <mpi.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

// Ваши функции frand, eval, init, shuffle, select, crossover, mutate,
// printthebest

// Функция для миграции особей между субпопуляциями
void migrate(int* P, int m, int n, int rank, int size) {
  int migration_size = m / 5;  // Размер миграции, например, 20% от популяции
  vector<int> migrants(migration_size * n);

  // Выбираем особей для миграции
  for (int i = 0; i < migration_size; ++i) {
    for (int j = 0; j < n; ++j) {
      migrants[i * n + j] = P[i * n + j];
    }
  }

  // Определение рангов соседних процессов
  int prev = rank - 1;
  int next = rank + 1;
  if (rank == 0)
    prev = size - 1;
  if (rank == size - 1)
    next = 0;

  // Отправляем и получаем мигрантов
  MPI_Sendrecv_replace(migrants.data(), migration_size * n, MPI_INT, prev, 0,
                       next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  // Заменяем часть текущей популяции мигрантами
  for (int i = 0; i < migration_size; ++i) {
    for (int j = 0; j < n; ++j) {
      P[(m - migration_size + i) * n + j] = migrants[i * n + j];
    }
  }
}

void runGA(int n, int m, int T, int rank, int size) {
  int* P = new int[n * m];
  init(P, m, n);
  for (int t = 0; t < T; t++) {
    select(P, m, n);
    crossover(P, m, n);
    mutate(P, m, n);
    if (t % 5 == 0) {  // Миграция каждые 5 поколений, например
      migrate(P, m, n, rank, size);
    }
    if (rank == 0) {  // Печать лучшего решения (опционально)
      printthebest(P, m, n);
    }
  }
  delete[] P;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int n = 10;
  int m = 20;
  int T = 100;

  runGA(n, m, T, rank, size);

  MPI_Finalize();
  return 0;
}
