#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

enum { STR_SIZE = 16 };

int
main(int argc, char *argv[])
{
    int check_max2 = -1;
    long long max1 = LLONG_MIN, max2 = LLONG_MIN;
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        int sum[5];
        while (read(fd, sum, sizeof(sum)) > 0) {
            if (sum[4] > max1) {
                check_max2++;
                max2 = max1;
                max1 = sum[4];
            } else if (sum[4] > max2 && sum[4] != max1) {
                check_max2++;
                max2 = sum[4];
            }
        }
    }
    if (check_max2 >= 1) {
        printf("%.2lf\n", ((float)max2)/ 100);
    }
    return 0;
}
