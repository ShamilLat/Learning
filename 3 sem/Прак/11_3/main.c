#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    int *pid = malloc((argc - 2) * sizeof(*pid)), status;
    int i, n;
    sscanf(argv[1], "%d", &n);
    //////////////////////////////////////////
    for (i = 0; i < n && i < argc - 2; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            free(pid);
            exit(1);
        }
        if (!pid[i]) {
            char str[PATH_MAX];
            int fd = open(argv[i + 2], O_RDONLY);
            dup2(fd, 0);
            scanf("%s", str);
            close(fd);
            execlp(str, str, NULL);
            exit(1);
        }
    }
    int count = 0, k = 0;
    while ((waitpid(pid[k], &status, 0)) != -1) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            count++;
        }
        k++;
    }
    ///////////////////////////////////////////
    for(; i < argc - 2; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            free(pid);
            exit(1);
        }
        if (!pid[i]) {
            char str[PATH_MAX];
            int fd = open(argv[i + 2], O_RDONLY);
            dup2(fd, 0);
            scanf("%s", str);
            close(fd);
            execlp(str, str, NULL);
            exit(1);
        }
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            count++;
        }
    }
    //////////////////////////////////////////////
    printf("%d\n", count);
    free(pid);
    return 0;
}
