#include <mpi.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

double frand(double a, double b) {
  return a + (b - a) * (rand() / double(RAND_MAX));
}

int do_walk(int a, int b, int x, double p, double& t) {
  int step = 0;
  while (x > a && x < b) {
    if (frand(0, 1) < p)
      x += 1;
    else
      x -= 1;
    t += 1.0;
    step += 1;
  }
  return x;
}

void run_mc(int a, int b, int x, double p, int N) {
  double t = 0.0;
  double w = 0.0;

  for (int i = 0; i < N; i++) {
    int out = do_walk(a, b, x, p, t);
    if (out == b)
      w += 1;
  }

  double global_t, global_w;
  MPI_Reduce(&t, &global_t, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&w, &global_w, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (MPI_COMM_RANK == 0) {
    ofstream f("output.dat");
    f << global_w / (N * MPI_COMM_SIZE) << " " << global_t / (N * MPI_COMM_SIZE)
      << endl;
    f.close();
  }
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  int x = atoi(argv[3]);
  double p = atof(argv[4]);
  int N = atoi(argv[5]) / MPI_COMM_SIZE;

  int numprocs, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  run_mc(a, b, x, p, N);

  MPI_Finalize();
  return 0;
}
