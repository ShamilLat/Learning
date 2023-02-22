#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

enum { ENDIAN_CHNG = 8 };

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    unsigned short buf = 0;
    unsigned short min = USHRT_MAX;
    while (read(fd, &buf, sizeof(buf)) > 0) {
        buf = (buf << ENDIAN_CHNG) | (buf >> ENDIAN_CHNG);
        if (min > buf && buf % 2 == 0) {
            min = buf;
        }
    }
    if (min % 2 == 0) {
        printf("%hu\n", min);
    }
    return 0;
}
