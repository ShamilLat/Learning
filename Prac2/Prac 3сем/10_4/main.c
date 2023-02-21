#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

void k_child(int (*fds)[2], int *pid, int i)
{
    for (int k = 0; k < i; k++) {
        kill(pid[k], SIGKILL);
    }
    free(fds);
    free(pid);
    while(wait(0) != -1){}
}

int main(int argc, char *argv[])
{
    int (*fds)[2] = malloc((argc - 1) * 2 * sizeof((*fds)[0]));
    int *pid = malloc((argc - 1) * sizeof(*pid)), status;
    for (int i = 0; i < argc - 1; i++) {
        if ((pipe(fds[i])) == -1) {
            if (i > 0) {
                close(fds[i - 1][0]);
                close(fds[i - 1][1]);
            }
            k_child(fds, pid, i);
            return 1;
        }
        if((pid[i] = fork()) < 0) {
            if (i > 0) {
                close(fds[i - 1][0]);
                close(fds[i - 1][1]);
            }
            close(fds[i][0]);
            close(fds[i][1]);
            k_child(fds, pid, i);
            return 1;
        }
        if (!pid[i]) {
            if (i > 0) {
                dup2(fds[i - 1][0], 0);
                close(fds[i - 1][0]);
                close(fds[i - 1][1]);
            }
            if (i < argc - 2) {
                dup2(fds[i][1], 1);
            }
            close(fds[i][1]);
            close(fds[i][0]);
            execlp(argv[i + 1], argv[i + 1], NULL);
            exit(1);
        }
        if (i > 0) {
            if ((close(fds[i - 1][1])) == -1) {
                close(fds[i - 1][0]);
                k_child(fds, pid, i);
                return 1;
            }
            if ((close(fds[i - 1][0])) == -1) {
                k_child(fds, pid, i);
                return 1;
            }
        }
    }
    close(fds[argc - 2][0]);
    close(fds[argc - 2][1]);
    for (int i = 0; i < argc - 1; i++) {
        waitpid(pid[i], &status, 0);
    }
    free(fds);
    free(pid);
    return 0;
}
