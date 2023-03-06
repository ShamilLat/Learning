#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int a = 1;
  for (; a <= 64; a *= 2) {
    printf("%d %d\n", 1024 * 10, (1024 / a) * 10);
  }

  a = 1;
  for (; a < 64; a *= 2) {
    printf("%d %d\n", 3072 * 10, (3072 / a) * 10);
  }

  a = 1;
  for (; a < 64; a *= 2) {
    printf("%d %d\n", 5120 * 10, (5120 / a) * 10);
  }

  return 0;
}

/*
    16
    48
    80
*/