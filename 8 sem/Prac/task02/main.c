// #include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void exchange_with_blocking(double* send_buffer_top,
                            double* send_buffer_bottom,
                            double* recv_buffer_top,
                            double* recv_buffer_bottom,
                            int top_process,
                            int bottom_process) {
  MPI_Status status;

  MPI_Send(send_buffer_top, SIZE, MPI_DOUBLE, top_process, 0, MPI_COMM_WORLD);
  MPI_Send(send_buffer_bottom, SIZE, MPI_DOUBLE, bottom_process, 0,
           MPI_COMM_WORLD);

  MPI_Recv(recv_buffer_top, SIZE, MPI_DOUBLE, top_process, 0, MPI_COMM_WORLD,
           &status);
  MPI_Recv(recv_buffer_bottom, SIZE, MPI_DOUBLE, bottom_process, 0,
           MPI_COMM_WORLD, &status);
}

void exchange_with_nonblocking(double* send_buffer_top,
                               double* send_buffer_bottom,
                               double* recv_buffer_top,
                               double* recv_buffer_bottom,
                               int top_process,
                               int bottom_process) {
  MPI_Request requests[4];

  MPI_Isend(send_buffer_top, SIZE, MPI_DOUBLE, top_process, 0, MPI_COMM_WORLD,
            &requests[0]);
  MPI_Isend(send_buffer_bottom, SIZE, MPI_DOUBLE, bottom_process, 0,
            MPI_COMM_WORLD, &requests[1]);

  MPI_Irecv(recv_buffer_top, SIZE, MPI_DOUBLE, top_process, 0, MPI_COMM_WORLD,
            &requests[2]);
  MPI_Irecv(recv_buffer_bottom, SIZE, MPI_DOUBLE, bottom_process, 0,
            MPI_COMM_WORLD, &requests[3]);

  MPI_Waitall(4, requests, MPI_STATUSES_IGNORE);
}

int main(int argc, char** argv) {
  int rank, size;
  double t1, t2;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int buf_size;

  if (argc < 2) {
    printf("Need to input buf size");
  } else {
    buf_size = atoi(argv[1]);
  }

  int top_process = (rank - 1 + size) % size;
  int bottom_process = (rank + 1) % size;

  double* send_buffer_top = (double*)malloc(SIZE * sizeof(double));
  double* send_buffer_bottom = (double*)malloc(SIZE * sizeof(double));
  double* recv_buffer_top = (double*)malloc(SIZE * sizeof(double));
  double* recv_buffer_bottom = (double*)malloc(SIZE * sizeof(double));

  // Заполняем буферы данными
  for (int i = 0; i < SIZE; i++) {
    send_buffer_top[i] = rank * 100 + i;
    send_buffer_bottom[i] = rank * 100 + i;
  }

  // Используем блокирующий обмен
  t1 = MPI_Wtime();
  exchange_with_blocking(send_buffer_top, send_buffer_bottom, recv_buffer_top,
                         recv_buffer_bottom, top_process, bottom_process);
  t2 = MPI_Wtime();
  printf("Blocking exchange time (rank %d): %f seconds\n", rank, t2 - t1);

  // Используем неблокирующий обмен
  t1 = MPI_Wtime();
  exchange_with_nonblocking(send_buffer_top, send_buffer_bottom,
                            recv_buffer_top, recv_buffer_bottom, top_process,
                            bottom_process);
  t2 = MPI_Wtime();
  printf("Non-blocking exchange time (rank %d): %f seconds\n", rank, t2 - t1);

  free(send_buffer_top);
  free(send_buffer_bottom);
  free(recv_buffer_top);
  free(recv_buffer_bottom);

  MPI_Finalize();
  return 0;
}