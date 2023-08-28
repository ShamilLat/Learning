#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int
mysys(const char *str)
{
    int pid, status;
    pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }
    waitpid(pid, &status, 0);
    int st;
    if((WIFEXITED(status)) != 0) {
        st = WEXITSTATUS(status);
        if (0 <= st && st <= 127) {
            return st;
        }
    }
    st = WTERMSIG(status);
    return 128 + st;
}
