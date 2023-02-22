#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fds[2];
    pipe(fds);
    time_t t;
    struct tm cal;
    int pid1, status;
    pid1 = fork();
    if (!pid1) {
        int pid2;
        pid2 = fork();
        if (!pid2) {
            int pid3;
            pid3 = fork();
            if (!pid3) {
                close(fds[0]);
                time(&t);
                if ((write(fds[1], &t, sizeof(t))) != sizeof(t)) {
                    fprintf(stderr, "write Error\n");
                    return 1;
                }
                if ((write(fds[1], &t, sizeof(t))) != sizeof(t)) {
                    fprintf(stderr, "write Error\n");
                    return 1;
                }
                if ((write(fds[1], &t, sizeof(t))) != sizeof(t)) {
                    fprintf(stderr, "write Error\n");
                    return 1;
                }
                close(fds[1]);
                exit(0);
            }
            close(fds[1]);
            waitpid(pid3, &status, 0);
            if ((read(fds[0], &t, sizeof(t))) != sizeof(t)) {
                fprintf(stderr, "read f3 Error\n");
                return 1;
            }
            close(fds[0]);
            gmtime_r(&t, &cal);
            printf("D:%02d\n", cal.tm_mday);
            fflush(stdout);
            exit(0);
        }
        close(fds[1]);
        waitpid(pid2, &status, 0);
        if ((read(fds[0], &t, sizeof(t))) != sizeof(t)) {
            fprintf(stderr, "read f2 Error\n%s\n", strerror(errno));
            return 1;
        }
        close(fds[0]);
        gmtime_r(&t, &cal);
        printf("M:%02d\n", cal.tm_mon + 1);
        fflush(stdout);
        exit(0);
    }
    close(fds[1]);
    waitpid(pid1, &status, 0);
    if ((read(fds[0], &t, sizeof(t))) != sizeof(t)) {
        fprintf(stderr, "read f1 Error\n%s\n", strerror(errno));
        return 1;
    }
    close(fds[0]);
    gmtime_r(&t, &cal);      
    printf("Y:%04d\n", cal.tm_year + 1900);
    return 0;
}