#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    int rows = 0, cols = 0;
    sscanf(argv[2], "%d", &rows);
    sscanf(argv[3], "%d", &cols);
    ftruncate(fd, rows * cols * sizeof(int));
    int *n = mmap(NULL, rows * cols * sizeof(*n), PROT_WRITE, MAP_SHARED, fd, 0);
    int *mas = (int *)n;
    int k = 1, i = 0, j = 0, imax = rows, jmax = cols, imin = 0, jmin = 0;
    while (k <= rows * cols)
    {
        while (j < jmax) {
            mas[i * cols + j] = k;
            k++;
            j++;
        }
        i++;
        j--;
        while (i < imax) {
            mas[i * cols + j] = k;
            k++;
            i++;
        }
        j--;
        i--;
        while (j >= jmin && mas[i * cols + j] == 0) {
            mas[i * cols + j] = k;
            k++;
            j--;
        }
        i--;
        j++;
        while (i > imin && mas[i * cols + j] == 0) {
            mas[i * cols + j] = k;
            k++;
            i--;
        }
        j++;
        i++;
        imin++, jmin++;
        imax--, jmax--;
    }
    close(fd);
    munmap(n, rows * cols * sizeof(int));
    return 0;
}
