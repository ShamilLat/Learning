#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>

enum { SIZE = 1024 };

int
main(int argc, char *argv[])
{
    unsigned long long cnt = 0;
    for (int i = 1; i < argc; ++i) {
        struct stat info;
        if (lstat(argv[i], &info) != -1 && S_ISREG(info.st_mode) && info.st_nlink == 1 && info.st_size % SIZE == 0) {
            cnt += info.st_size;
        }
    }
    printf("%llu\n", cnt);
    return 0;
}
