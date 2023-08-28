#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void task(int fds0, int fds1, int num, int max_num, int pid)
{
    FILE *out = fdopen(fds1, "w");
    if (out == NULL) {
        fprintf(stderr, "In pid = %d fds1 Error\n", pid);
    }
    FILE *in = fdopen(fds0, "r");
    if (in == NULL) {
        fprintf(stderr, "In pid = %d fds0 Error\n", pid);
    }
    while ((fscanf(in, "%d", &num)) == 1 && num != max_num) {
        printf("%d %d\n", pid, num);
        fflush(stdout);
        num++;
        fprintf(out, "%d\n", num); fflush(out);
    }
    close(fds0);
    close(fds1);
    fclose(in);
    fclose(out);
    exit(0);
}


int main(int argc, char *argv[])
{
    int max_num = 0;
    sscanf(argv[1], "%d", &max_num);

    int fds1[2], fds2[2];
    pipe(fds1);
    pipe(fds2);

    int num = 1;
    int pid[2], status;
    pid[0] = fork();
    if (!pid[0]) {
        close(fds2[0]);

        FILE *out = fdopen(fds1[1], "w");
        if (out == NULL) {
            fprintf(stderr, "fds1[1] Error\n");
        }
        fprintf(out, "%d\n", num); fflush(out);
        close(fds1[1]);
        fclose(out);

        task(fds1[0], fds2[1], num, max_num, 1);
    }
    close(fds1[0]);
    close(fds2[1]);
    pid[1] = fork();
    if (!pid[1]) {
        task(fds2[0], fds1[1], num, max_num, 2);
    }
    close(fds2[0]);
    close(fds1[1]);
    for (int i = 0; i < 2; i++) {
        waitpid(pid[i], &status, 0);
    }
    printf("Done\n");
    fflush(stdout);
    return 0;
}
