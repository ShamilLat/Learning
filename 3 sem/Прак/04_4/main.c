#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR);

    long long num, min = LLONG_MAX, poz = 0, pozmin = 0;
    while (read(fd, &num, sizeof(num)) > 0) {
        if (min > num) {
            min = num;
            pozmin = poz;
        }
        poz++;
    }
    if (poz) {
        lseek(fd, pozmin * sizeof(num), 0);
        if (min != LLONG_MIN) {
            min *= (long long)(-1);
        }
        write(fd, &min, sizeof(min));
    }
    return 0;
}
