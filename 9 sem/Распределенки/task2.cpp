#include <limits.h>
#include <mpi.h>
#include <algorithm>
#include <cfloat>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void add_comp(int first, int second, int rank, std::vector<double>& data) {
  int other_rank = (rank == first) ? second : first;
  std::vector<double> other_data(data.size());

  int size;

  MPI_Sendrecv(data.data(), data.size(), MPI_DOUBLE, other_rank, 0,
               other_data.data(), data.size(), MPI_DOUBLE, other_rank, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  vector<double> new_data(data.size());
  if (rank == first) {
    int i1 = 0, i2 = 0;
    for (int i = 0; i < data.size(); i++) {
      if (data[i1] < other_data[i2]) {
        new_data[i] = data[i1++];
      } else {
        new_data[i] = other_data[i2++];
      }
    }
  } else {
    int i1 = data.size() - 1, i2 = data.size() - 1;
    for (int i = data.size() - 1; i >= 0; i--) {
      if (data[i1] > other_data[i2]) {
        new_data[i] = data[i1--];
      } else {
        new_data[i] = other_data[i2--];
      }
    }
  }

  data = new_data;
}

void S(int first1,
       int first2,
       int step,
       int n,
       int m,
       int rank,
       std::vector<double>& vec) {
  if (n * m < 1) {
    return;
  }

  if (n == 1 && m == 1) {
    if (rank == first1 || rank == first2) {
      add_comp(first1, first2, rank, vec);
    }
    return;
  }

  int n1, m1, i;
  n1 = n - n / 2;
  m1 = m - m / 2;
  S(first1, first2, 2 * step, n1, m1, rank, vec);
  S(first1 + step, first2 + step, 2 * step, n - n1, m - m1, rank, vec);

  for (i = 1; i < n - 1; i += 2) {
    if (rank == first1 + step * i || rank == first1 + step * (i + 1)) {
      add_comp(first1 + step * i, first1 + step * (i + 1), rank, vec);
    }
  }

  if (n % 2 == 0) {
    if (rank == first1 + step * (n - 1) || rank == first2) {
      add_comp(first1 + step * (n - 1), first2, rank, vec);
    }
    i = 1;
  } else {
    i = 0;
  }

  for (; i < m - 1; i += 2) {
    if (rank == first2 + step * i || rank == first2 + step * (i + 1)) {
      add_comp(first2 + step * i, first2 + step * (i + 1), rank, vec);
    }
  }
}

void B(int first, int step, int count, int rank, std::vector<double>& vec) {
  if (count < 2) {
    return;
  }
  if (count == 2) {
    if (rank == first || rank == first + step) {
      add_comp(first, first + step, rank, vec);
    }
    return;
  }
  int count1 = count / 2 + count % 2;

  B(first, step, count1, rank, vec);
  B(first + step * count1, step, count - count1, rank, vec);
  S(first, first + step * count1, step, count1, count - count1, rank, vec);
}

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int array_size = 1024;

  if (argc != 2) {
    if (rank == 0) {
      std::cout << "Usage: " << argv[0] << " <array_size>\n";
    }
  } else {
    array_size = std::stoi(argv[1]);
  }

  std::vector<double> data;

  if (rank == 0) {
    data.resize(array_size);
    for (int i = 0; i < array_size; i++) {
      data[i] = rand() % array_size;
    }
  }

  if (array_size % size != 0) {
    int cnt = size - array_size % size;
    if (rank == 0) {
      data.insert(data.end(), cnt, DBL_MAX);
    }
    array_size += cnt;
  }

  int local_size = array_size / size;

  std::vector<double> local_data(local_size);

  MPI_Scatter(data.data(), local_size, MPI_DOUBLE, local_data.data(),
              local_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  double start_time = MPI_Wtime();

  std::sort(local_data.begin(), local_data.end());
  B(0, 1, size, rank, local_data);

  double end_time = MPI_Wtime();

  MPI_Gather(local_data.data(), local_size, MPI_DOUBLE, data.data(), local_size,
             MPI_DOUBLE, 0, MPI_COMM_WORLD);

  double result_time = end_time - start_time;
  
  double reduce_time;
  MPI_Reduce(&result_time, &reduce_time, 1, MPI_DOUBLE, MPI_SUM, 0,
             MPI_COMM_WORLD);

  if (rank == 0) {
    cout << "Time = " << reduce_time / (double)size << endl;
    data.resize(std::stoi(argv[1]));
  }

  MPI_Finalize();

  return 0;
}
