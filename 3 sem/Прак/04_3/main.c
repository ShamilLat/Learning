#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

enum { INT_CNT_INSTR = 3 };

void
dfs(int fd){
    int32_t buf[INT_CNT_INSTR];
    read(fd, buf, sizeof(buf));
    if (buf[2] != 0) {
        lseek(fd, buf[2] * sizeof(buf), 0);
        dfs(fd);
    }
    printf("%d ", buf[0]);
    if (buf[1] != 0) {
        lseek(fd, buf[1] * sizeof(buf), 0);
        dfs(fd);
    }
}

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd != -1) {
        dfs(fd);
    }
    printf("\n");
    return 0;
}
