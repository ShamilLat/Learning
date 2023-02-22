#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    int fds[2];
    pipe(fds);
    int num;
    while ((scanf("%d", &num)) == 1) {
        write(fds[1], &num, sizeof(num));
    }
    int pid1, status;
    pid1 = fork();
    if (!pid1) {
        int pid2;
        pid2 = fork();
        if (!pid2) {
            close(fds[1]);
            int sum = 0;
            while ((read(fds[0], &num, sizeof(num))) != sizeof(num)) {
                sum += num;
            }
            printf("%d A\nA", sum);
            fflush(stdout);
            exit(0);
        }
        close(fds[1]);
        close(fds[0]);
        waitpid(pid2, &status, 0);
        exit(0);
    }
    waitpid(pid1, &status, 0);
    close(fds[0]);
    close(fds[1]);
    return 0;
}