#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

enum
{
    NUM_CNT = 10,
    READ_CNT = 1,
    ERROR = -1
};

int
main(void)
{
    char s[PATH_MAX + 1];
    if (fgets(s, sizeof(s), stdin) == 0) {
        fprintf(stderr, "Input Error");
        return 1;
    }
    int slash_poz = 0;
    while (s[slash_poz] != '\r' && s[slash_poz] != '\n'){
        ++slash_poz;
    }
    s[slash_poz] = '\0';
    int file = open(s, O_RDONLY);
    if (file == ERROR) {
        fprintf(stderr, "File opwn Error\n");
        return 1;
    }
    unsigned long long cnt[NUM_CNT] = {0};
    if (file != -1) {
        char c[PATH_MAX];
        long long luck;
        while ((luck = read(file, c, sizeof(c))) > 0) {
            for (int i = 0; i < luck; i++) {
                if ('0' <= c[i] && c[i] <= '9') {
                    cnt[c[i] - '0']++;
                }
            }
        }
        if (luck == ERROR) {
            fprintf(stderr, "Read error\n");
            return 1;
        }   
    }
    for (int i = 0; i < NUM_CNT; i++) {
        printf("%d %llu\n", i, cnt[i]);
    }
    close(file);
    return 0;
}
