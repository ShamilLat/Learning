#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("%d", i);
        if (i != n) {
            int pid = fork();
            if (pid > 0) {
                wait(0);
                _exit(0);
            }
            printf(" ");
        }
    }
    printf("\n");
    return 0;
}
