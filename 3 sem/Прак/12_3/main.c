#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

volatile int num = 0;
volatile int flag = 0;
volatile int sig;

void handler(int s)
{
    if (s == SIGUSR1) {
        num += 5;
        sig = s;
        flag = 1;
    } else if (s == SIGUSR2) {
        num -= 4;
        sig = s;
        flag = 1;
    }
}

int main(int argc, char *argv[])
{
    struct sigaction s = {.sa_handler = handler, .sa_flags = SA_RESTART};
    sigaction(SIGUSR1, &s, NULL);
    sigaction(SIGUSR2, &s, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        while (flag == 0) 
            pause();
        printf("%d %d\n", sig, num);
        fflush(stdout);
        flag = 0;
        if (num < 0) {
            break;
        }
    }
    return 0;
}