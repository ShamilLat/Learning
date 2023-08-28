#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void sum_buf(int* a, int* b, int* c, int buf_size) {
  for (int i = 0; i < buf_size; i++) {
    a[i] = b[i] + c[i];
  }
}

int main(int argc, char** argv) {
  int rank, numprocs, iterations_number = 1000;
  int buf_size = 0;
  double start, stop, all_time;

  MPI_Status status;

  MPI_Init(&argc, &argv);

  if (argc == 2) {
    buf_size = atoi(argv[1]);
  } else {
    buf_size = 1000;
  }

  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int *r, *v, *rv;
  r = calloc(buf_size, sizeof(int));
  v = calloc(buf_size, sizeof(int));
  rv = calloc(buf_size, sizeof(int));

  for (int i = 0; i < buf_size; i++) {
    r[i] = rank;
    v[i] = rank;
  }

  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
    start = MPI_Wtime();
  }

  for (int iter = 0; iter < iterations_number; iter++) {
    if (rank == 0) {
      MPI_Recv(rv, buf_size, MPI_INT, numprocs - 1, 0, MPI_COMM_WORLD, &status);
      MPI_Send(r, buf_size, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
      sum_buf(r, rv, v, buf_size);
    } else {
      MPI_Send(r, buf_size, MPI_INT, (rank + 1) % numprocs, 0, MPI_COMM_WORLD);
      MPI_Recv(rv, buf_size, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
      sum_buf(r, rv, v, buf_size);
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
    stop = MPI_Wtime();
    all_time = stop - start;
    printf("buf size: %d\n", buf_size);
    printf("Time: %f\n", all_time);
    printf("r: %d\n", r[0]);
  }

  free(r);
  free(v);
  free(rv);

  MPI_Finalize();

  return 0;
}