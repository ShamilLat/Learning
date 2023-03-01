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

int main(int argc, char** argv) {
  int matrix_size = atoi(argv[1]), block_size = atoi(argv[2]);
  if (matrix_size % block_size) {
    printf("Incorrect block size. Now it's equal to 1");
    block_size = 1;
  }
  int block_cnt = (matrix_size / block_size) * (matrix_size / block_size);

  // printf("%d %d\n", matrix_size, block_size);

  int **matrix, **block;
  matrix = calloc(matrix_size, sizeof(*matrix));
  block = calloc(block_size, sizeof(*block));
  for (int i = 0; i < matrix_size; i++) {
    matrix[i] = calloc(matrix_size, sizeof(**matrix));
  }
  for (int i = 0; i < block_size; i++) {
    block[i] = calloc(block_size, sizeof(**block));
  }

  for (int i = 0; i < matrix_size; i++) {
    for (int j = 0; j < matrix_size; j++) {
      matrix[i][j] = i * matrix_size + j;
    }
  }

  // print_m(matrix, matrix_size);

  //

  for (int i = 0; i < block_cnt; i++) {
    get_block(block, matrix, block_size, i, matrix_size / block_size);
    // print_m(block, block_size);
    // printf("\n");
  }

  //

  for (int i = 0; i < matrix_size; i++) {
    free(matrix[i]);
  }
  for (int i = 0; i < block_size; i++) {
    free(block[i]);
  }

  free(block);
  free(matrix);

  return 0;
}