#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

enum
{
    MAX_COUNT = 4
};

volatile int num = 0;
volatile int count = 1;

void handler(int s)
{
    if (s == SIGINT && count < MAX_COUNT){
        printf("%d\n", num);
        fflush(stdout);
        count++;
    } else if ((s == SIGINT && count == MAX_COUNT) || s == SIGTERM) {
        exit(0);
    }
}

int prime(int low, int high)
{
    for(int i = low; i < high; i++) {
        int flag = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            num = i;
        }
    }
    return 0;
}

int main(int argc, char *argvp[])
{
    struct sigaction s = {.sa_handler = handler, .sa_flags = SA_RESTART};
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGTERM, &s, NULL);

    int low, high;
    scanf("%d %d", &low, &high);

    printf("%d\n", getpid());
    fflush(stdout);

    prime(low, high);
    printf("-1\n");
    fflush(stdout);
    r
