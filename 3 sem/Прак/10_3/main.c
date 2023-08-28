#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    int pid[2], status;
    pid[0] = fork();
    if (!pid[0]) {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        int pid_in = fork();
        if (!pid_in) {
            int fd1;
            if ((fd1 = open(argv[4], O_RDONLY)) == -1) {
                fprintf(stderr, "open file1 Error\n");
                return 1;
            }
            dup2(fd1, 0);
            close(fd1);
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        waitpid(pid_in, &status, 0);

        if (!WEXITSTATUS(status)) {
            execlp(argv[2], argv[2], NULL);
            exit(1);
        }
        exit(0);
    }
    pid[1] = fork();
    if (!pid[1]) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        int fd2;
        if ((fd2 = open(argv[5], O_WRONLY | O_CREAT | O_APPEND, 0777)) == -1) {
            fprintf(stderr, "open file2 Error\n");
            return 1;
        }

        dup2(fd2, 1);
        close(fd2);
        execlp(argv[3], argv[3], NULL);
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);
    for (int i = 0; i < 2; i++) {
        waitpid(pid[i], &status, 0);
    }
    return 0;
}
