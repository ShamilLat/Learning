#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int
main(void)
{
    int32_t n;
    int w;
    uint32_t s;
    scanf("%"SCNd32" %"SCNu32" %d", &n, &s, &w);
    uint32_t st = 1;
    for (int32_t j = 1; j < n; j++) {
        st = (st << 1) | st;
    }
    uint32_t i;
    for (i = 0; i < st / 2 + 1; i += s) {
        printf("|%*"PRIo32"|", w, i);
        printf("%*"PRIu32"|", w, i);
        printf("% *"PRId32"|\n", w, i);
    }
    uint32_t pause = i;
    for (; i <= st && i >= pause; i += s) {
        printf("|%*"PRIo32"|", w, i);
        printf("%*"PRIu32"|", w, i);
        printf("%*"PRId32"|\n", w, (i - st / 2 - 1) * (-1));
    }
    return 0;
}
