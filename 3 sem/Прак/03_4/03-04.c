#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

enum
{
    SIZE_BUF = 16,
    ERROR_READ = -1,
    TEN_MUL = 10
};

int main()
{
    char buf[SIZE_BUF] = {0};
    unsigned long long rezult = 0;
    int check_read;
    int set_zn = 1;
    unsigned long long num = 0;
    while ((check_read = read(0, buf, sizeof(buf))) != 0) {
        if (check_read == ERROR_READ) {
            fprintf(stderr, "Input Error\n");
            return 1;
        }
        for (int i = 0; i < check_read; i++) {
            if (isspace(buf[i])) {
                if (set_zn) {
                    rezult += num;
                } else {
                    rezult -= num;
                }
                set_zn = 1;
                num = 0;

            } else if (buf[i] == '+') {
                set_zn = 1;
            } else if (buf[i] == '-') {
                set_zn = 0;
            } else {
                num = (num * TEN_MUL + (unsigned long long)(buf[i] - '0'));
            }
        }
        if (check_read != SIZE_BUF) {
            if (set_zn) {
                rezult += num;
            } else {
                rezult -= num;
            }    
        }
    }
    /*
    if (num != 0) {
        if (set_zn) {
            rezult += num;
        } else {
            rezult -= num;
        }
    }
    */
    printf("%lld\n", rezult);
    return 0;
}
