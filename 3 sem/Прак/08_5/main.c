#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void
out(void)
{
    int n;
    if ((scanf("%d", &n)) == 1) {
        int pid = fork();
        int status = 0;
        if (pid < 0) {
            printf("-1\n");
            fflush(stdout);
            exit(1);
        }
        if (!pid) {
            out();
        }
        wait(&status);
        if (!WEXITSTATUS(status)) {
            printf("%d\n", n);
            fflush(stdout);
            _exit(0);
        } else {
            exit(1);
        }

    }
    _exit(0);
}

int main(int argc, char *argv[])
{
    int pid = fork(), status = 0;
    if (pid < 0) {
        printf("-1\n");
        return 0;
    }
    if (!pid) {
        out();
    }
    wait(&status);
    return 0;
}
