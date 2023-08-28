#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

enum
{
    SUM_FLAG = 1,
    MUL_FLAG = 0
};

volatile int flag = SUM_FLAG;

void handler(int s)
{
    if (s == SIGQUIT) {
        flag = MUL_FLAG;
    } else if (s == SIGINT) {
        flag = SUM_FLAG;
    }
}

int main(int argc, char *argv[])
{
    struct sigaction s = {.sa_handler = handler, .sa_flags = SA_RESTART};
    sigaction(SIGINT, &s, NULL);
    sigaction(SIGQUIT, &s, NULL);

    printf("%d\n", getpid()); fflush(stdout);

    int res = 0;
    int num = 0;

    while (scanf("%d", &num) > 0) {
        if (flag == SUM_FLAG) {
            res = (int)((long long)res + num);
        } else if (flag == MUL_FLAG) {
            res = (int)((long long)res * num);
        }
        printf("%d\n", res);
        fflush(stdout);
    }
    return 0;
}
