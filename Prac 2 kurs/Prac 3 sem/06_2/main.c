#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

enum
{
    POINT_POZ = 3,
    EXE_LEN = 5,
    STRSTR_ANS = 1
};
int
main(int argc, char *argv[])
{
    DIR *dir = opendir(argv[1]);
    if (!dir) {
        fprintf(stderr, "Opendir Error\n");
        return 1;
    }
    struct dirent *ddir;
    int cnt = 0;
    while ((ddir = readdir(dir))) {
        struct stat info;
        char file[PATH_MAX];
        char exe[EXE_LEN] = ".exe";
        snprintf(file, sizeof(file), "%s/%s", argv[1], ddir->d_name);
        if (stat(file, &info) != -1) {
            if(S_ISREG(info.st_mode) && !access(file, X_OK)
                    && (strstr(file, exe) - file + STRSTR_ANS) == strlen(file) - POINT_POZ) {
                cnt++;
            }
        }
    }
    printf("%d\n", cnt);
    return 0;
}
