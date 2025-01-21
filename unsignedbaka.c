#include<stdio.h>

int main(void) {
    int x = -10;
    unsigned int y = 5;

    if(x > y) printf("Simple x > y is true\n");
    if(x < (int)y) printf("Cast to correct type x < y\n");

    return 0;
}