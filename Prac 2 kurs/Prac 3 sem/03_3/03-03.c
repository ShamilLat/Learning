#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum
{
    HUNDRED = 100,
    T_THOUSAND = 10000
};

int
main(int argc, char* argv[])
{
    double num;
    sscanf(argv[1], "%lf", &num);
    for (int i = 2; i < argc; ++i) {
        double pr;
        sscanf(argv[i], "%lf", &pr);
        num = num + (pr / (double)HUNDRED) * num;
        num = round(num * (double)T_THOUSAND) / (double)T_THOUSAND;
    }
    printf("%.4lf\n", num);
    return 0;
}
