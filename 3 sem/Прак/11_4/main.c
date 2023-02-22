#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

volatile int max_num = 0;

void handler(int s)
{

}

void task(FILE *in, FILE *out, int num, int id)
{
    struct sigaction s = {.sa_handler = handler, .sa_flags = SA_RESTART};
    sigaction(SIGUSR1, &s, NULL);
    int pid;
    if (id == 2) pause();
    while (1) {
        fscanf(in, "%d%d", &pid, &num);
        if (num == max_num) {
            fclose(in);
            fclose(out);
            exit(0);
        }
        printf("%d %d\n", id, num);
        fflush(stdout);
        num++;

        fprintf(out, "%d\n%d\n", getpid(), num);
        fflush(out);

        kill(pid, SIGUSR1);
        pause();
    }
}


int main(int argc, char *argv[])
{
    sscanf(argv[1], "%d", &max_num);
    int fds[2];
    if ((pipe(fds)) == -1) {
        fprintf(stderr, "pipe Error\n");
    }

    int pid[2];
    FILE *in = fdopen(fds[0], "r");
    FILE *out = fdopen(fds[1], "w");
    int num = 1;
    pid[0] = fork();
    if (!pid[0]) {
        task(in, out, num, 1);
    }
    pid[1] = fork();
    if (!pid[1]) {
        fprintf(out, "%d\n%d\n", getpid(), num);
        fflush(out);

        task(in, out, num, 2);
    }
    int son;
    son = wait(0);
    if (son == pid[0]) {
        kill(pid[1], SIGKILL);
    } else {
        kill(pid[0], SIGKILL);
    }
    wait(0);
    printf("Done\n");
    fflush(stdout);
    return 0;
}
