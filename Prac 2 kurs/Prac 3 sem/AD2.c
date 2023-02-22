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
        int fdin, fdout;
        fdin = open(argv[2], O_RDONLY);
        fdout = open(argv[3], O_WRONLY | O_CREAT, 0777);
        
        dup2(fdin, 0); close(fdin);
        dup2(fdout, 1); close(fdout);
        
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }
    wait(&status);
    printf("%d\n", WEXITSTATUS(status));
    return 0;
}
