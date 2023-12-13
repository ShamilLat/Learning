#include <mpi.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Функция для определения состояния клетки
int cell_state(int* grid, int x, int y, int n) {
  int alive = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0)
        continue;
      alive += grid[((x + i + n) % n) * n + ((y + j + n) % n)];
    }
  }
  if (grid[x * n + y] == 1) {
    return (alive == 2 || alive == 3) ? 1 : 0;
  }
  return (alive == 3) ? 1 : 0;
}

// Функция для обновления состояния доски
void update_board(int* grid, int* new_grid, int n) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      new_grid[i * n + j] = cell_state(grid, i, j, n);
    }
  }
}

// Функция для обмена граничными строками и столбцами
void exchange_borders(int* grid, int n, int rank, int size, int p) {
  MPI_Status status;

  // Вычисляем координаты текущего процесса в 2D решетке
  int row = rank / p;
  int col = rank % p;

  // Определяем соседей
  int up = (row == 0) ? (p - 1) * p + col : rank - p;
  int down = (row == p - 1) ? col : rank + p;
  int left = (col == 0) ? rank + p - 1 : rank - 1;
  int right = (col == p - 1) ? rank - p + 1 : rank + 1;

  // Обмен верхней и нижней границы
  MPI_Sendrecv(&grid[n], n, MPI_INT, up, 0, &grid[0], n, MPI_INT, down, 0,
               MPI_COMM_WORLD, &status);
  MPI_Sendrecv(&grid[(n - 2) * n], n, MPI_INT, down, 1, &grid[(n - 1) * n], n,
               MPI_INT, up, 1, MPI_COMM_WORLD, &status);

  // Обмен левой и правой границы
  for (int i = 0; i < n; ++i) {
    MPI_Sendrecv(&grid[i * n + 1], 1, MPI_INT, left, 2, &grid[i * n], 1,
                 MPI_INT, right, 2, MPI_COMM_WORLD, &status);
    MPI_Sendrecv(&grid[i * n + n - 2], 1, MPI_INT, right, 3,
                 &grid[i * n + n - 1], 1, MPI_INT, left, 3, MPI_COMM_WORLD,
                 &status);
  }
}

// Главная функция для запуска "Игры Жизнь"
void run_life(int n, int T, int rank, int size) {
  int p = sqrt(size);
  int local_n = n / p + 2;  // Размер локальной доски для каждого процесса

  vector<int> grid(local_n * local_n, 0);
  vector<int> new_grid(local_n * local_n, 0);

  // Инициализация глайдера в центре локальной доски
  if (rank == p / 2 * (p + 1)) {
    grid[(local_n / 2) * local_n + local_n / 2 + 1] = 1;
    grid[(local_n / 2 - 1) * local_n + local_n / 2] = 1;
    grid[(local_n / 2 + 1) * local_n + local_n / 2 - 1] = 1;
    grid[(local_n / 2 + 1) * local_n + local_n / 2] = 1;
    grid[(local_n / 2 + 1) * local_n + local_n / 2 + 1] = 1;
  }

  double start_time = MPI_Wtime();

  for (int t = 0; t < T; ++t) {
    exchange_borders(grid.data(), local_n, rank, size, p);
    update_board(grid.data(), new_grid.data(), local_n);
    grid.swap(new_grid);
  }

  double end_time = MPI_Wtime();

  vector<int> final_grid;
  if (rank == 0) {
    // Сбор результатов и запись в файлы
    final_grid = vector<int>(n * n, 0);
    // Сборка и запись локальных досок...
    // Запись в output.txt

    ofstream stat("stat.txt");
    stat << "Total Time: " << (end_time - start_time) << " seconds" << endl;
    stat.close();
  }
}

int main(int argc, char** argv) {
  int n, T;
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (argc != 3) {
    if (rank == 0) {
      cerr << "Usage: " << argv[0] << " n T" << endl;
    }
    MPI_Finalize();
    return 1;
  }

  n = atoi(argv[1]);
  T = atoi(argv[2]);

  run_life(n, T, rank, size);

  MPI_Finalize();
  return 0;
}