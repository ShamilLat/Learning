#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum
{
    BUF_SIZE = 4,
    NUM_CNT = 10,
    FOUR_BYTES_SM = 4,
    SN_SIXTEEN = 16,
    BYTES_CLEAR = 0xf,
    ERROR = -1
};

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == ERROR) {
        fprintf(stderr, "File open error\n");
        return 1;
    }
    int num;
    while (scanf("%d", &num) != EOF) {
        unsigned char buf[BUF_SIZE] = {0};
        int poz = 0, i = sizeof(buf) - 1;
        while (num) {
            buf[i] =  buf[i] | ((num % SN_SIXTEEN) << (poz * FOUR_BYTES_SM));
            i -= poz;
            poz = (poz + 1) % 2;
            num /= SN_SIXTEEN;
        }
        buf[0] = buf[1] >> FOUR_BYTES_SM;
        buf[1] = ((buf[1] & BYTES_CLEAR) << FOUR_BYTES_SM) | (buf[2] >> FOUR_BYTES_SM);
        buf[2] = buf[2] & BYTES_CLEAR;
        if ((write(fd, buf, sizeof(buf))) == ERROR) {
            fprintf(stderr, "Write to fd error\n");
            return 1;
        }
    }
    return 0;
}
