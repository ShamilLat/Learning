#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid1, pid2;
    int st;
    pid1 = fork();
    if (!pid1) {
        pid2 = fork();
        if (!pid2) {
            printf("3 ");
            exit(0);
        }
        wait(&st);
        printf("2 ");
        exit(0);
    }
    wait(0);
    printf("1\n");
    exit(0);
    return 0;
}
