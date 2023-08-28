#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

enum
{
    YEAR_POZ = 1900,
    MONTH_POZ = 1
};

int main(int argc, char *argv[])
{
    int fds[2];
    pipe(fds);
    time_t t;
    struct tm cal;
    int pid[3], status;
    for (int i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i]) {
            close(fds[1]);
            waitpid(pid[i], &status, 0);
            if ((read(fds[0], &t, sizeof(t))) != sizeof(t)) {
                fprintf(stderr, "read f2 Error\n%s\n", strerror(errno));
                return 1;
            }
            close(fds[0]);
            localtime_r(&t, &cal);
            switch(i) {
            case 0:
                printf("Y:%04d\n", cal.tm_year + YEAR_POZ);
                break;
            case 1:
                printf("M:%02d\n", cal.tm_mon + MONTH_POZ);
                break;
            case 2:
                printf("D:%02d\n", cal.tm_mday);
                break;
            default:
                break;
            }
            fflush(stdout);
            exit(0);
        }
        if (i == 2 && !pid[i]) {
            close(fds[0]);
            time(&t);
            for (int k = 0; k < 3; k++) {
                if ((write(fds[1], &t, sizeof(t))) != sizeof(t)) {
                    fprintf(stderr, "write Error%s\n", strerror(errno));
                    return 1;
                }
            }
            close(fds[1]);
            exit(0);
        }
    }
    return 0;
}
