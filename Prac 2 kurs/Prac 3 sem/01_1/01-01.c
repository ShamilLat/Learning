#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double a = 0, b = 0;
    scanf("%lf\n%lf", &a, &b);
    printf("%d", b <= 5.0 && b >= 2.0 && a >= 1.0 && a <= 7.0 && a + b <= 10.0);
    return 0;
}
