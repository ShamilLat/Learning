#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char path[PATH_MAX];
    int rd = open("/dev/urandom", O_RDONLY);
    unsigned long long name;
    read(rd, &name, sizeof(name));
    close(rd);

    char *way = 0;
    char temp[] = "/tmp";
    if (!(way = getenv("XDG_RUNTIME_DIR"))) {
        if (!(way = getenv("TMPDIR"))) {
            way = temp;
        }
    }
    
    sprintf(path, "%s/file%llx.py", way, name);
    
    int fd;
    if ((fd = open(path, O_RDWR | O_CREAT, 0755)) < 0) {
        fprintf(stderr, "File open error\n");
        return 0;
    }

    char first[] = "#!/usr/bin/python3\nimport os\nprint(";
    write(fd, first, strlen(first));
    write(fd, argv[1], strlen(argv[1]));
    for (int i = 2; i < argc; i++) {
        char mul[] = "*";
        write(fd, mul, strlen(mul));
        write(fd, argv[i], strlen(argv[i]));
    }
    char second[] = ")\nos.remove(\"";
    write(fd, second, strlen(second));
    write(fd, path, strlen(path));
    char end[] = "\")";
    write(fd, end, strlen(end));
    close(fd);

    execlp("/bin/sh", "sh", "-c", path, NULL);
    return 0;
}