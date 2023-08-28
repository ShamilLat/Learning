#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    long long unum = 0, snum = 0;
    for(int i = 1; i < argc; ++i)
    {
        int num;
        sscanf(argv[i], "%d", &num);
        if(num >= 0)
        {
            unum += num;
        }
        else
        {
            snum += num;
        }
    }
    printf("%lld\n%lld\n", unum, snum);
    return 0;
}
