#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum Symbols
{
    SM_FIRST = 1,
    SM_SMALL_L = SM_FIRST + '9' - '0' + 1,
    SM_BIG_L = SM_SMALL_L + 'Z' - 'A' + 1,
    EIGHT_XOR = 0x8,
    FOUR_AND = 0x3b,
    RESERV_FIRST = 0,
    RESERV_LAST = 63
};

int
main(void)
{
    int s = 0;
    while ((s = getchar()) != EOF) {
        if (isalnum(s)) {
            if (isdigit(s)) {
                s = s - '0' + SM_FIRST;
            } else if ('a' <= s && s <= 'z') {
                s = s - 'a' + SM_SMALL_L;
            } else {
                s = s - 'A' + SM_BIG_L;
            }

            s ^= EIGHT_XOR;
            s &= FOUR_AND;

            if (s == RESERV_FIRST) {
                s = '@';
            } else if (s == RESERV_LAST) {
                s = '#';
            } else {
                if (s < SM_SMALL_L) {
                    s = s + '0' - SM_FIRST;
                } else if (SM_SMALL_L <= s && s < SM_BIG_L) {
                    s = s + 'a' - SM_SMALL_L;
                } else {
                    s = s + 'A' - SM_BIG_L;
                }
            }
            putchar(s);
        }
    }
    return 0;
}
