#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void
path_clear(char *str)
{
    char up[5] = "/../";
    char up2[4] = "/..";
    char here[4] = "/./";
    char here2[3] = "/.";
    char sl[2] = "/";
    char *t_poz;
    while ((t_poz = strstr(str, here)) != NULL) {
        char buf[2 * PATH_MAX + 1] = {0};
        snprintf(buf, strlen(str) + 1, "%s", t_poz + 2);
        snprintf(t_poz, strlen(str) + 1, "%s", buf);
    }
    int sl_poz = 0;
    while ((t_poz = strstr(str, up)) != NULL) {
        sl_poz = 0;
        for (int i = 0; i < (unsigned)(t_poz - str); i++) {
            if (str[i] == '/') {
                sl_poz = i;
            }
        }
        char buf[2 * PATH_MAX + 1] = {0};
        snprintf(buf, strlen(str) + 1, "%s", t_poz + 3);
        snprintf(str + sl_poz, strlen(str) + 1, "%s", buf);
    }

    sl_poz = 0;
    if (strlen(str) > 2 && (t_poz = strstr(str + strlen(str) - 3, up2)) == str + strlen(str) - 3) {
        for (int i = 0; i < (unsigned)(t_poz - str); i++) {
            if (str[i] == '/') {
                sl_poz = i;
            }
        }
        if (sl_poz == 0) {
            snprintf(str, 3, "%s", sl);
        } else {
            *(str + sl_poz) = '\0';
        }
    } else if (strlen(str) > 1 && (t_poz = strstr(str + strlen(str) - 2, here2)) == str + strlen(str) - 2) {
        if (t_poz == str) {
            snprintf(str, 3, "%s", sl);
        } else {
            *(t_poz) = '\0';
        }
    }
}

char
*relativize_path(const char *path1, const char *path2)
{
    char *res, *p1, *p2;
    res = calloc(2 * PATH_MAX + 2, sizeof(*res));
    p1 = malloc((2 * PATH_MAX + 2) * sizeof(*p1));
    p2 = malloc((2 * PATH_MAX + 2) * sizeof(*p2));

    sprintf(p1, "%s", path1);
    sprintf(p2, "%s", path2);

    path_clear(p1);
    path_clear(p2);

    char up[3] = "..";
    char here[2] = ".";

    int i = 0, j = 0;
    while (p1[i] == p2[i] && i < strlen(p1)) {
        if (p1[i] == '/') {
            j = i;
        }
        i++;
    }
    j++;
    int up_cnt = 0;

    int check_end1 = 0;     //for . in the beginning str
    if (strlen(p1) == 1 && p2[i] == '\0') {
        check_end1 = 1;
    }

    int check_end2 = 0;     //for . in the beginning str
    if (i == strlen(p2)) {
        if (p1[i] == '/') {
            up_cnt--;
            check_end2 = 1;
        } else if (i == 1) {
            check_end2 = 1;
        }
    }

    while (p1[i] != '\0') {
        if (p1[i] == '/') {
            up_cnt++;
        }
        i++;
    }

    for (int k = 0; k < up_cnt; k++) {
        sprintf(res + k * 3, "%s/", up);
    }
    if (check_end1 || (check_end2 && up_cnt == 0)) {
        sprintf(res, "%s/", here);
    } else if (!check_end2 && j < strlen(p2) && p2[j] != '\0') {
        sprintf(res + up_cnt * 3, "%s/", p2 + j);
    }

    res[strlen(res) - 1] = '\0';
    free(p1);
    free(p2);
    return res;
}

int main(int argc, char *argv[])
{
    char *str1, *str2;
    str1 = argv[1];
    str2 = argv[2];
    printf("%s\n", relativize_path(str1, str2));

    return 0;
}