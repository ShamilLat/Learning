#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

enum
{
    YEAR_START = 1900,
    THURSDAY_CODE = 4,
    DAY_NOTDIV_THREE = 3,
    WEEK_TIME = 86400 * 7,
    DAY_TIME = 86400,
    SAVE_TIME_UN = -1,
    TM_CNT_ELEM = 9,
    INT_SIZE = 4
};

int
day_check(int day)
{
    return((day >= 8 && day <= 14) || (day >= 22 && day <= 28));
}

int
main(int argc, char *argv[])
{
    int year;
    scanf("%d", &year);
    year -= YEAR_START;
    struct tm *cal = calloc(TM_CNT_ELEM, INT_SIZE);
    cal->tm_year = year;
    cal->tm_isdst = SAVE_TIME_UN;
    cal->tm_mday = 1;

    time_t find_days = mktime(cal);
    while (cal->tm_wday != THURSDAY_CODE) {
        find_days += DAY_TIME;
        localtime_r(&find_days, cal);
    }

    while (cal->tm_year == year) {
        if (cal->tm_mday % DAY_NOTDIV_THREE != 0 && day_check(cal->tm_mday)) {
            printf("%d %d\n", cal->tm_mon + 1, cal->tm_mday);
        }
        find_days += WEEK_TIME;
        localtime_r(&find_days, cal);
    }

    return 0;
}
