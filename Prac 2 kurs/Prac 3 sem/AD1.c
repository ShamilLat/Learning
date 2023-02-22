#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int rec(int i, int n)
{
    if (i < n) {
        pid_t pid = fork();
        if (!pid) {
            rec(i + 1, n);
        }
        wait(0);
    }
    printf("%d\n", i);
    fflush(stdout);
    exit(0);
}

int main(void)
{
    int n;
    scanf("%d", &n);
    pid_t pid = fork();
    if (!pid) {
        rec(1, n);
    }
    wait(0);
    printf("Finish\n");
    return 0;
}
