#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0751);
    if (fd == -1) {
        fprintf(stderr, "File open error\n");
        return 1;
    }
    char input_fd[] = "#!/usr/bin/python3\nnum = int(input())\nmod = ";
    write(fd, input_fd, strlen(input_fd));
    write(fd, argv[2], strlen(argv[2]));
    char print_fd[] = "\nprint(int(((num + 1) * num // 2) % mod))\n";
    write(fd, print_fd, strlen(print_fd));
    close(fd);
    return 0;
}