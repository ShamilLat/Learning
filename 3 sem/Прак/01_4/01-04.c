#include <ctype.h>

int
mystrspccmp(const char *str1, const char *str2)
{
    do {
        while (isspace((unsigned char)*str1)) {
            ++str1;
        }
        while (isspace((unsigned char)*str2)) {
            ++str2;
        }
        if (*str1 != *str2 || *str1 == '\0' || *str2 == '\0') {
            return (unsigned char)*str1 - (unsigned char)*str2;
        }
        ++str1;
        ++str2;
    } while(1);

    return (unsigned char)*str1 - (unsigned char)*str2;
}
