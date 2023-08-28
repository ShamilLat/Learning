#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>

enum { STR_SIZE = 30 };

int main(int argc, char *argv[])
{
    int x = 0;
    char str1[STR_SIZE], str2[STR_SIZE];
    char zn;
    sscanf("x %c %d?%s:%s", &zn, &x, str1, str2);
    int num, flag = 0;

    if (zn == '>') {
        flag = 1;
    } else if (zn == '<') {
        flag = 0;
    }
    while (scanf("%d", &num) == 1) {
        if (flag) {
            printf("%s\n", num > x?str1:str2);
        }
        else if (!flag) {
            printf("%s\n", num < x?str1:str2);
        }
    }
    

    return 0;
}