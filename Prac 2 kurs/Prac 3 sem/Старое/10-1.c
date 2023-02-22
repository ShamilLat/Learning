#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>

enum
{
    TM_CNT_ELEM = 9,
    INT_SIZE = 4
}

int main(int argc, char *argv[])
{
    int pid1;
    pid1 = fork();
    int fds[2];
    pipe(fds);
    time_t t;
    struct tm *cal = calloc(TM_CNT_ELEM, INT_SIZE);
    if (!pid1) {
        int pid2;
        pid2 = fork();
        if (!pid2) {
            int pid3;
            pid3 = fork();
            if (!pid3) {
                time(&t);
                write(fds[1], &t, 1);
                exit(0);
            }
            wait(0);
            read(fds[0], &t, 1);
            gmtime_r(&t, cal);
            printf("D:%02d\n", cal->tm_mday);
            fflush(stdout);
            exit(0);
        }
        wait(0);
        printf("M:%02d\n", cal->tm_mon);
        fflush(stdout);
        exit(0);
    }
    wait(0);
    printf("Y:%04d\n", cal->tm_year);
    fflush(stdout);
    return 0;
}