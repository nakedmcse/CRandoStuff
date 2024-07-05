#include<stdio.h>

int main(void) {
    int a = 5;
    int b = 2;

    printf("Original a,b %d,%d\n", a, b);

    a = a^b;
    b = a^b;
    a = a^b;

    printf("Final a,b %d,%d\n", a, b);
}