#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pid[3], status;
    for (int i = 0; i < 3; i++) {
        pid[i] = fork();
        if (!pid[i]) {
            char num[8];
            read(0, num, sizeof(num));
            int n = 0;
            sscanf(num, "%d", &n);
            n *= n;
            printf("%d %d\n", i + 1, n);
            fflush(stdout);
            exit(0);
        }
    }
    for (int i = 0; i < 3; i++) {
        waitpid(pid[i], &status, 0);
    }
    return 0;
}
