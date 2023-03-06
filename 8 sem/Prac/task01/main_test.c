// #include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void print_m(int** m, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

void swap(int* a, int* b) {
  int c = *a;
  *a = *b;
  *b = c;
}

void transpose(int** block, int block_size) {
  for (int i = 0; i < block_size; i++) {
    for (int j = i + 1; j < block_size; j++) {
      swap(&block[i][j], &block[j][i]);
    }
  }
}

void get_block(int** get_block,
               int** public_block,
               int block_size,
               int block_number,
               int blocks_in_line_cnt) {
  int val_i = 0, val_j = 0;
  val_i = (block_number / blocks_in_line_cnt) * block_size;
  val_j = (block_number % blocks_in_line_cnt) * block_size;
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      get_block[i][j] = public_block[i + val_i][j + val_j];
    }
  }
}

void put_block(int** put_block,
               int** public_block,
               int block_size,
               int block_number,
               int blocks_in_line_cnt) {
  int val_i = 0, val_j = 0;
  val_i = (block_number / blocks_in_line_cnt) * block_size;
  val_j = (block_number % blocks_in_line_cnt) * block_size;
  for (int i = 0; i < block_size; i++) {
    for (int j = 0; j < block_size; j++) {
      public_block[i + val_j][j + val_i] = put_block[i][j];
    }
  }
}

int main(int argc, char** argv) {
  int matrix_size = 0, block_size = 0;
  if (argc < 2) {
    printf("Need to input matrix_size and block_size\n");
    scanf("%d%d", &matrix_size, &block_size);
  } else {
    matrix_size = atoi(argv[1]), block_size = atoi(argv[2]);
  }
  if (matrix_size % block_size) {
    printf("Incorrect block size. Now it's equal to 1\n");
    block_size = 1;
  }
  int block_cnt = (matrix_size / block_size) * (matrix_size / block_size);

  int** matrix;
  matrix = calloc(matrix_size, sizeof(*matrix));
  for (int i = 0; i < matrix_size; i++) {
    matrix[i] = calloc(matrix_size, sizeof(**matrix));
  }

  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      matrix[i][j] = i * matrix_size + j;
    }
  }

  //

  print_m(matrix, matrix_size);

  for (int num = 0; num < block_cnt; num++) {
    printf("my_num = %d\n", num);
    int** block = calloc(block_size, sizeof(*block));
    for (int i = 0; i < block_size; i++) {
      block[i] = calloc(block_size, sizeof(**block));
    }

    get_block(block, matrix, block_size, num, matrix_size / block_size);
    transpose(block, block_size);
#pragma omp barrier
    // put_block(block, matrix, block_size, num, matrix_size / block_size);
    printf("put block\n");
    print_m(block, block_size);
    printf("to pos %d %d\n\n", (num / (matrix_size / block_size)) * block_size,
           (num % (matrix_size / block_size)) * block_size);

    for (int i = 0; i < block_size; i++) {
      free(block[i]);
    }
    free(block);
  }

  //

  print_m(matrix, matrix_size);

  for (int i = 0; i < matrix_size; i++) {
    free(matrix[i]);
  }

  free(matrix);

  return 0;
}