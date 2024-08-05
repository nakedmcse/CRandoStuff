// 8 bit negative if
#include<stdio.h>
#include<stdlib.h>

int main(void) {
    int8_t x = 0;
    printf("x=0 returns %d\n", -x==x);
    x = 10;
    printf("x=10 returns %d\n", -x==x);
    x = -128;
    printf("x=-128 returns %d\n", -x==x);
    return 0;
}
