#include <stdio.h>
#include <stdlib.h>

void print_m(int** m, int size) {
  printf("\n");
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

void get_matrix_a(int** m_a,
                  int** get_a,
                  int block_i,
                  int block_size,
                  int col_param) {
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      get_a[i][j] = m_a[block_i * block_size + i][col_param + j];
    }
  }
}

void get_matrix_b(int** m_b,
                  int** get_b,
                  int block_j,
                  int block_size,
                  int row_param) {
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      get_b[i][j] = m_b[row_param + i][block_j * block_size + j];
    }
  }
}

void matrix_mul(int** m_a,
                int** m_b,
                int** m_c,
                int block_i,
                int block_j,
                int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      for (int k = 0; k < size; k++) {
        m_c[block_i * size + i][block_j * size + j] += m_a[i][k] * m_b[k][j];
      }
    }
  }
}

int main(int argc, char** argv) {
  int matrix_size = atoi(argv[1]), block_size = atoi(argv[2]);
  if (matrix_size % block_size != 0) {
    printf(
        "Incorrect input. Block_size must be a multiple of the matrix size\n");
    return 0;
  }
  int **matrix_a, **matrix_b, **matrix_c;

  matrix_a = calloc(matrix_size, sizeof(*matrix_a));
  matrix_b = calloc(matrix_size, sizeof(*matrix_b));
  matrix_c = calloc(matrix_size, sizeof(*matrix_c));

  for (int i = 0; i < matrix_size; i++) {
    matrix_a[i] = calloc(matrix_size, sizeof(*matrix_a[i]));
    matrix_b[i] = calloc(matrix_size, sizeof(*matrix_b[i]));
    matrix_c[i] = calloc(matrix_size, sizeof(*matrix_c[i]));
  }

  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      matrix_a[i][j] = i * matrix_size + j;
      matrix_b[i][j] = matrix_a[i][j];
    }
  }

  printf("\nmatrix A:");
  print_m(matrix_a, matrix_size);
  printf("matrix B:");
  print_m(matrix_b, matrix_size);

  int block_cnt = matrix_size / block_size;

  double start_time = omp_get_wtime();

  int p = 0;
  omp_set_num_threads(block_cnt * block_cnt);
#pragma omp parallel for private(p) \
    shared(matrix_a, matrix_b, matrix_c, matrix_size, block_size, block_cnt)
  for (p = 0; p < block_cnt * block_cnt; p++) {
    int i = p / block_cnt, j = p % block_cnt;
    int **get_a, **get_b;
    get_a = calloc(block_size, sizeof(*get_a));
    get_b = calloc(block_size, sizeof(*get_b));

    for (int k = 0; k < block_size; k++) {
      get_a[k] = calloc(block_size, sizeof(*get_a[k]));
      get_b[k] = calloc(block_size, sizeof(*get_b[k]));
    }

    get_matrix_b(matrix_b, get_b, j, block_size, i * block_size);

    int m = 0;
    for (m = 0; m < block_cnt; m++) {
      int col_num_sended_A = (i + m) % block_cnt;
      get_matrix_a(matrix_a, get_a, i, block_size,
                   col_num_sended_A * block_size);

      matrix_mul(get_a, get_b, matrix_c, i, j, block_size);

      if ((i + m + 1) * block_size >= matrix_size) {
        get_matrix_b(matrix_b, get_b, j, block_size,
                     (i + m + 1) * block_size - matrix_size);
      } else {
        get_matrix_b(matrix_b, get_b, j, block_size, (i + m + 1) * block_size);
      }
#pragma omp barrier
    }

    for (int k = 0; k < block_size; k++) {
      free(get_a[k]);
      free(get_b[k]);
    }
    free(get_a);
    free(get_b);
  }

  printf("Result matrix C is:");
  print_m(matrix_c, matrix_size);

  double end_time = omp_get_wtime();
  printf("Time taken to execute is\n%lf\n", end_time - start_time);

  for (int i = 0; i < matrix_size; i++) {
    free(matrix_a[i]);
    free(matrix_b[i]);
    free(matrix_c[i]);
  }
  free(matrix_a);
  free(matrix_b);
  free(matrix_c);
}