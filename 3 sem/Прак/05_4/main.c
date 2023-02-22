#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
parse_rwx_permissions(const char *str)
{
    char temp[] = {"rwxrwxrwx"};
    int size = sizeof(temp) - 1;
    if (str == 0) {
        return -1;
    }
    if (strlen(str) != size) {
        return -1;
    }
    int mask = 0;
    for (int i = 0; i < size; i++) {
        mask = mask << 1;
        if (temp[i] == str[i]) {
            mask = mask | 1;
        } else if (str[i] != '-') {
            return -1;
        }
    }
    return mask;
}
