#include <mpi.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Функция для обновления данных в соответствии с правилами L-системы
string update_data(const string& data, map<char, string>& R) {
  string buf = "";
  for (char c : data) {
    buf += R[c];
  }
  return buf;
}

int get_count(int l, int r) {
  if (l > r) {
    return (l - r) / 2;
  }
  return 0;
}

string align_load(string& w, int rank, int size) {
  int prev, next;
  if (rank != 0) {
    prev = rank - 1;
  } else {
    prev = MPI_PROC_NULL;
  }

  if (rank != size - 1) {
    next = rank + 1;
  } else {
    next = MPI_PROC_NULL;
  }

  int l_next, l;
  l_next = l = w.length();

  MPI_Sendrecv(&l, 1, MPI_INT, prev, 0, &l_next, 1, MPI_INT, next, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  int c = get_count(l, l_next);
  string sub_w = w.substr(l - c, c), v = "";
  MPI_Sendrecv(&sub_w, sub_w.length() + 1, MPI_CHAR, next, 0, &v, 2048,
               MPI_CHAR, prev, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  w = v + w.substr(0, l - c);

  int l_prev;
  l_prev = l = w.length();

  MPI_Sendrecv(&l, 1, MPI_INT, next, 0, &l_prev, 1, MPI_INT, prev, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  int c = get_count(l, l_prev);

  sub_w = w.substr(0, c), v = "";
  MPI_Sendrecv(&sub_w, sub_w.length() + 1, MPI_CHAR, prev, 0, &v, 2048,
               MPI_CHAR, next, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  string new_w = w.substr(c, l - c);
  return (new_w + v);
}

// Функция для запуска L-системы
void run_lsystem(int m, int k) {
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Инициализация аксиомы и правил L-системы
  string data = "a";
  map<char, string> R;
  R['a'] = "ab";  // Пример правила: a → ab
  R['b'] = "a";   // Пример правила: b → a

  string w = "";
  if (rank == size / 2) {
    w = data;
  }

  for (int t = 0; t < m; ++t) {
    w = update_data(w, R);

    if (t % k == 0) {
      w = align_load(w, rank, size);
    }
  }

  if (rank != 0) {
    MPI_Send(&w, w.length() + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  } else {
    string v = "";
    for (int p = 1; p < size; p++) {
      MPI_Recv(&v, 2048, MPI_CHAR, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      w = w + v;
    }
    cout << w << endl;
  }

  vector<int> loads(size, 0);  // Вектор для хранения информации о загрузке

  // Запись окончательных данных только процессом с rank 0
  if (rank == 0) {
    ofstream output("output.txt");
    output << data;
    output.close();
  }

  // Запись статистики загрузки каждым процессом
  ofstream stat("stat.txt", ios_base::app);
  stat << "Process " << rank << ", Load: " << loads[rank] << endl;
  stat.close();
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <number_of_iterations> <exchange_step>"
         << endl;
    MPI_Finalize();
    return 1;
  }

  int m = atoi(argv[1]);  // Число итераций
  int k = atoi(argv[2]);  // Шаг обмена

  run_lsystem(m, k);

  MPI_Finalize();
  return 0;
}