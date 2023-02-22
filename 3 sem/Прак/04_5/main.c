#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

unsigned long long
hash_function(unsigned long long);

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0660);
    long long cnt;
    unsigned long long h;
    sscanf(argv[2], "%llx", &h);
    sscanf(argv[3], "%lld", &cnt);
    off_t sm = sizeof(h) * (cnt - 1);
    off_t back = sizeof(h) * 2;
    lseek(fd, sm, SEEK_END);
    for (int i = cnt - 1; i >= 0; i--) {
        write(fd, &h, sizeof(h));
        h = hash_function(h);
        if (lseek(fd, 0, SEEK_CUR) - back >= 0) {
            lseek(fd, -back, SEEK_CUR);
        }
    }
    return 0;
}
