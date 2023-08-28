#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char shb[] = {"rwxrwxrwx"};

enum
{
    NUMPOZ_STR = sizeof(shb) - 2,
    CHECK_BYTE = 1
};

int
main(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        int num = 0;
        sscanf(argv[i], "%o", &num);
        char str[sizeof(shb)];
        int poz = NUMPOZ_STR;
        while (poz >= 0) {
            if (num & CHECK_BYTE) {
                str[poz] = shb[poz];
            } else {
                str[poz] = '-';
            }
            num = num >> 1;
            poz--;
        }
        str[sizeof(shb) - 1] = '\0';
        printf("%s\n", str);
    }

    return 0;
}
