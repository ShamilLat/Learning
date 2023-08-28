#include <stdio.h>
#include <stdlib.h>

enum
{
    MIN_VALUE = 2,
    MAX_VALUE = 2000
};

int
main(void)
{
    int n = 0, chk = 0;
    scanf("%d", &n);

    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            chk = 1;
        }
    }

    if (n <  MIN_VALUE || n >= MAX_VALUE || chk) {
        fprintf(stderr, "Input Error\n");
        return 1;
    }

    int **check;
    if (!(check = malloc(n * sizeof(*check)))) {
        fprintf(stderr, "Memory Error\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (!(check[i] = malloc(n * sizeof(**check)))) {
            fprintf(stderr, "Memory Error\n");
            return 1;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int j = 1; j < n; j++) {
            int rez = j * k % n;
            check[rez][j] = k;
        }
    }


    for (int k = 0; k < n; k++) {
        for (int j = 1; j < n; j++) {
            printf("%d ", check[k][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(check[i]);
    }
    free(check);
    return 0;
}
