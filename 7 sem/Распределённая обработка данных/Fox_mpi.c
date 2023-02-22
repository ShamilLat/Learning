#include <math.h>
#include <mpi-ext.h>
#include <mpi.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int number_of_processes, rank;
int kill_rank = 3;
MPI_Comm main_comm = MPI_COMM_WORLD;
int error_occured = 0;

static void err_handler(MPI_Comm* pcomm, int* perr, ...) {
  error_occured = 1;
  int err = *perr;
  char errstr[MPI_MAX_ERROR_STRING];
  int size, failed_len, len;

  MPI_Group failed_group;
  MPI_Comm_size(main_comm, &size);

  MPIX_Comm_failure_ack(main_comm);
  MPIX_Comm_failure_get_acked(main_comm, &failed_group);

  MPI_Group_size(failed_group, &failed_len);
  MPI_Error_string(err, errstr, &len);
  printf("\nRank %d / %d: Error %s. Dead %d\n", rank, size, errstr, nf);

  // создаем новый коммуникатор без вышедшего из строя процесса
  MPIX_Comm_shrink(main_comm, &main_comm);
  MPI_Comm_rank(main_comm, &rank);

  create_filename(rank, filename);
  strcat(filename, ".txt");
}

static void data_save() {
  if (myrank == 0) {
    FILE* f = fopen("elimination.bin", "wb");
    fwrite(&A[0], sizeof(double), (N - 1) * N, f);
    fclose(f);

    if (reverse_sub) {
      FILE* f = fopen("reverse_sub.bin", "wb");
      fwrite(&X[0], sizeof(double), N, f);
      fclose(f);
    }
  }
  MPI_Barrier(main_comm);
}

static void data_load() {
  FILE* f = fopen("elimination.bin", "rb");

  fread(&A[0], sizeof(double), (N - 1) * N, f);
  fclose(f);
  printf("Proc %d\n", myrank);

  if (reverse_sub) {
    FILE* f = fopen("reverse_sub.bin", "wb");
    fwrite(&X[0], sizeof(double), N, f);
    fclose(f);
  }

  MPI_Barrier(main_comm);
}

void print_m(int** m, int size) {
  char output_format[] = "%*d ";
  int max_elem = m[size - 1][size - 1];
  int x = 1, st = 0;
  while (x < max_elem) {
    x *= 10;
    st++;
  }
  output_format[1] = st + '0';
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf(output_format, m[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void get_block(int* tmp, int** m_a, int block_i, int block_j, int block_size) {
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      tmp[i * block_size + j] =
          m_a[block_i * block_size + i][block_j * block_size + j];
    }
  }
}

void buf_to_matr(int* tmp, int** matrix, int block_size) {
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      matrix[i][j] = tmp[i * block_size + j];
    }
  }
}

void matr_to_buf(int* tmp, int** matrix, int block_size) {
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      tmp[i * block_size + j] = matrix[i][j];
    }
  }
}

void block_to_matrix(int** block,
                     int** matrix,
                     int block_i,
                     int block_j,
                     int block_size) {
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      matrix[block_i * block_size + i][block_j * block_size + j] = block[i][j];
    }
  }
}

void matrix_mul(int** m_a, int** m_b, int** m_c, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        m_c[i][j] += m_a[i][k] * m_b[k][j];
      }
    }
  }
}

int main(int argc, char** argv) {
  int matrix_size = atoi(argv[1]);

  MPI_Init(&argc, &argv);

  int number_of_processes, rank;

  MPI_Comm_size(MPI_COMM_WORLD, &number_of_processes);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // обработчик ошибок
  MPI_Errhandler errh;
  MPI_Comm_create_errhandler(err_handler, &errh);
  MPI_Comm_set_errhandler(MPI_COMM_WORLD, errh);
  MPI_Barrier(MPI_COMM_WORLD);

  create_filename(rank, filename);
  strcat(filename, ".txt");

  if (matrix_size * matrix_size % (number_of_processes - 1) != 0) {
    printf("Incorrect Number of processes\n");
    return 0;
  }
  int block_size = matrix_size * matrix_size / (number_of_processes - 1);
  block_size = sqrt(block_size);
  int block_cnt = matrix_size / block_size;

  if (rank == 0) {
    // Выделение памяти для исходных матриц A и B и результирующей матрицы C
    int **matrix_a, **matrix_b, **matrix_c;

    matrix_a = calloc(matrix_size, sizeof(*matrix_a));
    matrix_b = calloc(matrix_size, sizeof(*matrix_b));
    matrix_c = calloc(matrix_size, sizeof(*matrix_c));

    for (int i = 0; i < matrix_size; i++) {
      matrix_a[i] = calloc(matrix_size, sizeof(*matrix_a[i]));
      matrix_b[i] = calloc(matrix_size, sizeof(*matrix_b[i]));
      matrix_c[i] = calloc(matrix_size, sizeof(*matrix_c[i]));
    }

    // Заполнения матриц A и B
    for (int i = 0; i < matrix_size; i++) {
      for (int j = 0; j < matrix_size; j++) {
        matrix_a[i][j] = i * matrix_size + j;
        matrix_b[i][j] = matrix_a[i][j];
      }
    }

    double start_time = MPI_Wtime();

    int* tmp = calloc(block_size * block_size, sizeof(*tmp));

    // Рассылка блоков Aij и Bij в соответствующие процессы
    for (int p = 1; p < number_of_processes; p++) {
      int i = (p - 1) / block_cnt, j = (p - 1) % block_cnt;

      get_block(tmp, matrix_a, i, j, block_size);
      MPI_Send(tmp, block_size * block_size, MPI_INT, p, 0, MPI_COMM_WORLD);

      get_block(tmp, matrix_b, i, j, block_size);
      MPI_Send(tmp, block_size * block_size, MPI_INT, p, 0, MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int** get_block;
    get_block = calloc(block_size, sizeof(*get_block));
    for (int k = 0; k < block_size; k++) {
      get_block[k] = calloc(block_size, sizeof(**get_block));
    }

    for (int p = 1; p < number_of_processes; p++) {
      int i = (p - 1) / block_cnt, j = (p - 1) % block_cnt;

      // Получение получившихся блоков Cij из каждого процесса
      MPI_Recv(tmp, block_size * block_size, MPI_INT, p, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
      buf_to_matr(tmp, get_block, block_size);
      // Вставляем этот блок в матрицу C
      block_to_matrix(get_block, matrix_c, i, j, block_size);
    }
    // Замер времени
    double end_time = MPI_Wtime();
    printf("Time taken to execute is\n%lf\n", end_time - start_time);

    // print_m(matrix_c, matrix_size);

    // Освобождение памяти
    free(tmp);
    for (int i = 0; i < block_size; i++) {
      free(get_block[i]);
    }
    free(get_block);

    for (int i = 0; i < matrix_size; i++) {
      free(matrix_a[i]);
      free(matrix_b[i]);
      free(matrix_c[i]);
    }
    free(matrix_a);
    free(matrix_b);
    free(matrix_c);
  } else if (rank != 0) {
    int i = (rank - 1) / block_cnt, j = (rank - 1) % block_cnt;
    int* tmp;    // Для разных переносимых буферов
    int* buf_a;  // Хранит свой блок Aij в виде буфера
    tmp = calloc(block_size * block_size, sizeof(*tmp));
    buf_a = calloc(block_size * block_size, sizeof(*tmp));

    int **get_a, **get_b, **get_c;  // Для хранения блоков Aij, Bij и Cij
    get_a = calloc(block_size, sizeof(*get_a));
    get_b = calloc(block_size, sizeof(*get_b));
    get_c = calloc(block_size, sizeof(*get_c));

    for (int k = 0; k < block_size; k++) {
      get_a[k] = calloc(block_size, sizeof(**get_a));
      get_b[k] = calloc(block_size, sizeof(**get_b));
      get_c[k] = calloc(block_size, sizeof(**get_c));
    }

    // Получение от главного процесса блоков Aij и Bij
    MPI_Recv(buf_a, block_size * block_size, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    buf_to_matr(buf_a, get_a, block_size);

    MPI_Recv(tmp, block_size * block_size, MPI_INT, 0, 0, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    buf_to_matr(tmp, get_b, block_size);
    MPI_Barrier(MPI_COMM_WORLD);

    int m = 0;  // Цикл по m
    for (m = 0; m < block_cnt; m++) {
      int col_num_sended_A = (i + m) % block_cnt;
      // Рассылка блока Aij всем процессам в этой строке
      if (block_cnt > 1) {
        if (j == col_num_sended_A) {
          for (int k = 0; k < block_cnt; k++) {
            if (k != j) {
              MPI_Send(buf_a, block_size * block_size, MPI_INT,
                       i * block_cnt + k + 1, 0, MPI_COMM_WORLD);
            }
          }
        } else {
          MPI_Recv(tmp, block_size * block_size, MPI_INT,
                   i * block_cnt + col_num_sended_A + 1, 0, MPI_COMM_WORLD,
                   MPI_STATUS_IGNORE);
          buf_to_matr(tmp, get_a, block_size);
        }
      }

      // Умножение блоков Aij и Bij, запись результата в Cij
      matrix_mul(get_a, get_b, get_c, block_size);

      if (block_cnt > 1) {
        int send_num = rank - block_cnt;
        int recv_num = rank + block_cnt;

        if (recv_num >= number_of_processes) {
          recv_num -= (number_of_processes - 1);
        }
        if (send_num <= 0) {
          send_num += number_of_processes - 1;
        }

        matr_to_buf(tmp, get_b, block_size);

        // Циклическая перессылка блока Bij в направление убывания строк.
        // Условия if и else необходимы для избежания Deadlock
        if (i % 2) {
          MPI_Send(tmp, block_size * block_size, MPI_INT, send_num, 0,
                   MPI_COMM_WORLD);
          MPI_Recv(tmp, block_size * block_size, MPI_INT, recv_num, 0,
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE);

          buf_to_matr(tmp, get_b, block_size);
        } else {
          int* tmp_b = calloc(block_size * block_size, sizeof(*tmp));
          matr_to_buf(tmp_b, get_b, block_size);
          MPI_Recv(tmp_b, block_size * block_size, MPI_INT, recv_num, 0,
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE);
          MPI_Send(tmp, block_size * block_size, MPI_INT, send_num, 0,
                   MPI_COMM_WORLD);
          buf_to_matr(tmp_b, get_b, block_size);
          free(tmp_b);
        }
      }

      buf_to_matr(buf_a, get_a, block_size);
    }

    matr_to_buf(tmp, get_c, block_size);

    // Сохранение данных и убийство процесса
    if (rank == kill_rank) {
      data_save();
      raise(SIGKILL);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    // При существовании ошибки нужный ранг забирает данные и высылает их
    if (error_occured && rank == number_of_processes - 1) {
      error_occured = 0;
      data_load();
    }
    // Пересылка получившегося блока Cij в главный процесс с номером 0
    MPI_Send(tmp, block_size * block_size, MPI_INT, 0, 0, MPI_COMM_WORLD);

    // Освобождение всей памяти в процессе
    for (int k = 0; k < block_size; k++) {
      free(get_a[k]);
      free(get_b[k]);
      free(get_c[k]);
    }
    free(get_a);
    free(get_b);
    free(get_c);
    free(tmp);
    free(buf_a);
  }

  MPI_Finalize();
  return 0;
}
