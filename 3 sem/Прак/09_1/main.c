#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int status;
    if (!fork()) {
        int fdin, fdout, fderr;
        if ((fdin = open(argv[2], O_RDONLY)) == -1) {
            exit(42);
        }
        if ((fdout = open(argv[3], O_WRONLY | O_CREAT | O_APPEND, 0660)) == -1) {
            exit(42);
        }
        if ((fderr = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0660)) == -1) {
            exit(42);
        }
        dup2(fdin, 0); close(fdin);
        dup2(fdout, 1); close(fdout);
        dup2(fderr, 2); close(fderr);

        if ((execlp(argv[1], argv[1], NULL)) == -1) {
            exit(42);
        }
        exit(0);
    }
    wait(&status);
    printf("%d\n", status);
    return 0;
}
