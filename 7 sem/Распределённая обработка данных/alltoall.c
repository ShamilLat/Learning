#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*
Таблица процессов в матрице

     (0)  (1)  (2)  (3)  (4)

(0)   0 -- 1 -- 2 -- 3 -- 4
      |    |    |    |    |
(1)   5 -- 6 -- 7 -- 8 -- 9
      |    |    |    |    |
(2)   10 - 11 - 12 - 13 - 14
      |    |    |    |    |
(3)   15 - 16 - 17 - 18 - 19
      |    |    |    |    |
(4)   20 - 21 - 22 - 23 - 24

*/

const int SIZE = 5;

void copy_buf(int* a, int* b, int s) {
  for (int i = 0; i < s; i++) {
    a[i] = b[i];
  }
}

// Копирование буфера по столбцам (нужно при движени по горизонтали)
void copy_recv_buf_to_next_buf(int* a /* Что копируем */,
                               int* b /* Куда копируем */,
                               int num_a,
                               int num_b) {
  for (int i = 0; i < SIZE; i++) {
    b[i * SIZE + num_a] = a[i * SIZE + num_b];
  }
}

// Копирование буфера по строкам (нужно при движении по вертикали)
void copy_recv_buf_to_result_buf(int* a /* Что копируем */,
                                 int* b /* Куда копируем */,
                                 int num_a,
                                 int num_b) {
  for (int i = 0; i < SIZE; i++) {
    b[num_a * SIZE + i] = a[num_b * SIZE + i];
  }
}

int main(int argc, char* argv[]) {

  MPI_Init(&argc, &argv);
  int number_of_processes, rank;

  MPI_Status status;

  MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  int num_row = rank % SIZE;
  int num_col = rank / SIZE;
  int total_s = SIZE * SIZE;
  int *my_buf, *buf_to_right, *buf_to_left;

  // Буферы:
  // my_buf - изначальный буфер в процессе. В нём же и будет результат
  // buf_to_* - буфер, который передаётся по направлению (right, left, up, down)
  // neighbors_buf - буфер, который хранит в себе промежуточные значения после
  // перессылок по горизонтали
  my_buf = calloc(total_s + 1, sizeof(*my_buf));
  buf_to_right = calloc(total_s + 1, sizeof(*buf_to_right));
  buf_to_left = calloc(total_s + 1, sizeof(*buf_to_left));

  int* neighbors_buf;
  neighbors_buf = calloc(total_s + 1, sizeof(*neighbors_buf));

  // Задание начального буфера
  for (int i = 0; i < total_s; i++) {
    my_buf[i] = (rank + 1) * i;
  }

  // Начальные буферы
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
    printf("////////////////////////////////////\n");
    printf("///////     START BUFS:      ///////\n");
    printf("////////////////////////////////////\n");
  }
  MPI_Barrier(MPI_COMM_WORLD);

  for (int i = 0; i < total_s; i++) {
    if (rank == i) {
      printf("rank = %d:\n", rank);
      for (int j = 0; j < total_s; j++) {
        printf("%d ", my_buf[j]);
        if ((j + 1) % SIZE == 0) {
          printf("\n");
        }
      }
      printf("\n");
      fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  // Последний элемент буфера хранит номер его столбца
  my_buf[total_s] = num_row;
  neighbors_buf[total_s] = num_col;

  copy_buf(buf_to_right, my_buf, total_s + 1);
  copy_buf(buf_to_left, my_buf, total_s + 1);

  // Необходимое копирование, чтобы процесс не потерял свой же столбец элементов
  // в neighbors_buf
  copy_recv_buf_to_next_buf(buf_to_right, neighbors_buf, num_row, num_row);

  int left = 0, right = SIZE - 1;
  const int c_left = 0, c_right = SIZE - 1;

  // Рассылка буферов вдоль строк
  while (left < c_right && right > c_left) {
    // Движение вправо
    if (num_row == left) {
      MPI_Send(buf_to_right, total_s + 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else if (num_row == c_right) {
      MPI_Recv(buf_to_right, total_s + 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
               &status);
    } else if (num_row > left && num_row < c_right) {
      MPI_Sendrecv_replace(buf_to_right, total_s + 1, MPI_INT, rank + 1, 0,
                           rank - 1, 0, MPI_COMM_WORLD, &status);
    }

    // Движение влево
    if (num_row == right) {
      MPI_Send(buf_to_left, total_s + 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD);
    } else if (num_row == c_left) {
      MPI_Recv(buf_to_left, total_s + 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD,
               &status);
    } else if (num_row > c_left && num_row < right) {
      MPI_Sendrecv_replace(buf_to_left, total_s + 1, MPI_INT, rank - 1, 0,
                           rank + 1, 0, MPI_COMM_WORLD, &status);
    }

    int tmp_num_right = buf_to_right[total_s];
    int tmp_num_left = buf_to_left[total_s];

    copy_recv_buf_to_next_buf(buf_to_right, neighbors_buf, tmp_num_right,
                              num_row);
    copy_recv_buf_to_next_buf(buf_to_left, neighbors_buf, tmp_num_left,
                              num_row);

    left++;
    right--;
  }

  int up = 0, down = SIZE - 1;
  int c_up = 0, c_down = SIZE - 1;
  int *buf_to_down, *buf_to_up;
  buf_to_down = calloc(total_s + 1, sizeof(*buf_to_down));
  buf_to_up = calloc(total_s + 1, sizeof(*buf_to_up));

  copy_buf(buf_to_up, neighbors_buf, total_s + 1);
  copy_buf(buf_to_down, neighbors_buf, total_s + 1);

  // Необходимое копирование, чтобы процесс не потерял свою же строку элементов
  // в my_result
  copy_recv_buf_to_result_buf(buf_to_down, my_buf, num_col, num_col);

  // Рассылка буферов вдоль столбцов
  while (up < c_down && down > c_up) {
    // Движение вниз
    if (num_col == up) {
      MPI_Send(buf_to_down, total_s + 1, MPI_INT, rank + SIZE, 0,
               MPI_COMM_WORLD);
    } else if (num_col == c_down) {
      MPI_Recv(buf_to_down, total_s + 1, MPI_INT, rank - SIZE, 0,
               MPI_COMM_WORLD, &status);
    } else if (num_col > up && num_col < c_down) {
      MPI_Sendrecv_replace(buf_to_down, total_s + 1, MPI_INT, rank + SIZE, 0,
                           rank - SIZE, 0, MPI_COMM_WORLD, &status);
    }

    // Движение вверх
    if (num_col == down) {
      MPI_Send(buf_to_up, total_s + 1, MPI_INT, rank - SIZE, 0, MPI_COMM_WORLD);
    } else if (num_col == c_up) {
      MPI_Recv(buf_to_up, total_s + 1, MPI_INT, rank + SIZE, 0, MPI_COMM_WORLD,
               &status);
    } else if (num_col > c_up && num_col < down) {
      MPI_Sendrecv_replace(buf_to_up, total_s + 1, MPI_INT, rank - SIZE, 0,
                           rank + SIZE, 0, MPI_COMM_WORLD, &status);
    }

    int tmp_num_down = buf_to_down[total_s];
    int tmp_num_up = buf_to_up[total_s];

    copy_recv_buf_to_result_buf(buf_to_down, my_buf, tmp_num_down, num_col);
    copy_recv_buf_to_result_buf(buf_to_up, my_buf, tmp_num_up, num_col);

    up++;
    down--;
  }

  // Результат
  MPI_Barrier(MPI_COMM_WORLD);
  if (rank == 0) {
    printf("////////////////////////////////////\n");
    printf("/////////     RESULTS:     /////////\n");
    printf("////////////////////////////////////\n");
  }
  MPI_Barrier(MPI_COMM_WORLD);

  for (int i = 0; i < total_s; i++) {
    if (rank == i) {
      printf("rank = %d:\n", rank);
      for (int j = 0; j < total_s; j++) {
        printf("%d ", my_buf[j]);
        if ((j + 1) % SIZE == 0) {
          printf("\n");
        }
      }
      printf("\n");
      fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }

  free(neighbors_buf);

  free(buf_to_right);
  free(buf_to_left);
  free(buf_to_up);
  free(buf_to_down);
  free(my_buf);

  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();

  return 0;
}