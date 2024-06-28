// Simple Factorials
#include<stdio.h>

static unsigned long factorial(int num) {
    unsigned long fact = 1;
    for(unsigned long i = 2; i<=num; ++i) fact *= i;
    return fact;
}

int main(void) {
    for(int i = 1; i<10000; i++) {
        printf("Int:%d, Fact:%lu\n",i,factorial(i));
    }
    return 0;
}