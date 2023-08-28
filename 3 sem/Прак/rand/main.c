#include <stdio.h>
#include <stdlib.h>

int main()
{
    int w = 0, m = 0, c = 0, cnt = 0;
    for(int i = 0; i < 100000; i++){
        for(int j = 0; j < 4; j++){
            unsigned int r = rand() % 10;
            //printf("%d ", r);
            if(!r)
                c++;
            else if(1 <= r && r <= 3)
                m++;
            else if(4 <= r && r <= 9)
                w++;
        }
        if(m > 0 && c > 0)
            cnt++;
        w = 0;
        m = 0;
        c = 0;
    }
    printf("%d\n", cnt);
    printf("%f\n", cnt / 100000.0);
    return 0;
}
