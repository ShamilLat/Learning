#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

typedef int STYPE;
typedef unsigned int UTYPE;

void d( int n )
 {
 
if ( n >= 2 )
{
d( n/2 );
}
printf("%d", n % 2);
 
}

STYPE bit_reverse(STYPE value)
{
    STYPE num2 = 0;
    STYPE cnt = 0;
    while ((UTYPE)value != 0) {
        num2 = num2 << 1;
        num2 = num2 | (value & 1);
        value = ((UTYPE)value) >> 1;
        cnt++;
    }
    num2 = ((UTYPE)num2) << (sizeof(STYPE) * 8 - cnt);
    return num2;
}

int main(int argc, char *argv[])
{
    d(1);
    printf("\n");
    d(bit_reverse(1));
    printf("\n");
    return 0;
}