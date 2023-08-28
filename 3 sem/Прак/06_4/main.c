#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

enum
{
    YEAR_TM = 1900,
    YEAR_START = 25,
    MONTH_START = 9,
    DAY_START = 7,
    TM_CNT_ELEM = 9,
    INT_SIZE = 4,
    SEC_IN_DAY = 86400,
    DAY_IN_MON = 30,
    MON_IN_YEAR = 12
};

int
main(int argc, char *argv[])
{
    int yy, mm, dd;
    struct tm *newcal = calloc(TM_CNT_ELEM, INT_SIZE);
    newcal->tm_year = YEAR_START;
    newcal->tm_mon = MONTH_START;
    newcal->tm_mday = DAY_START;
    newcal->tm_isdst = -1;
    time_t newtime = timegm(newcal);
    while ((scanf("%d %d %d", &yy, &mm, &dd)) != EOF) {
        newcal->tm_year = yy - YEAR_TM;
        newcal->tm_mon = mm - 1;
        newcal->tm_mday = dd;
        newcal->tm_isdst = -1;
        long long now = (long long)timegm(newcal) - newtime;
        int y_res = 1, m_res = 1, d_res = 1;
        d_res += (now / SEC_IN_DAY) % DAY_IN_MON;
        m_res += (now / SEC_IN_DAY / DAY_IN_MON) % MON_IN_YEAR;
        y_res += now / SEC_IN_DAY / DAY_IN_MON / MON_IN_YEAR;
        printf("%d %d %d\n", y_res, m_res, d_res);
    }
    return 0;
}
