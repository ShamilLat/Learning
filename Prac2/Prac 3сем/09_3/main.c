#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int pid, status;
    pid = fork();
    if (!pid) {
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    waitpid(pid, &status, 0);
    if (!(WIFEXITED(status)) || WEXITSTATUS(status)) {
        pid = fork();
        if (!pid) {
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        waitpid(pid, &status, 0);
    }
    if (WIFEXITED(status) && !(WEXITSTATUS(status))) {
        pid = fork();
        if (!pid) {
            execlp(argv[3], argv[3], NULL);
            _exit(1);
        }
        waitpid(pid, &status, 0);
    }
    if (WIFEXITED(status) && !(WEXITSTATUS(status))) {
        return 0;
    }
    return 1;
}
