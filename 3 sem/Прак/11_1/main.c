#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

enum
{
    MAX_COUNT = 5
};

volatile int count = 0;

void handler(int s)
{
    if (count == MAX_COUNT)
        exit(0);
    printf("%d\n", count++);
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    struct sigaction s = {.sa_handler = handler, .sa_flags = SA_RESTART};
    sigaction(SIGHUP, &s, NULL);
    printf("%d\n", getpid()); fflush(stdout);
    while (1) {
        pause();
    }
    return 0;
}
