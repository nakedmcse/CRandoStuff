#include<stdio.h>

int64_t foo(int64_t n) {
    static int64_t memo[1024] = {0};
    if(n < 1) return 1;
    if(memo[n] > 0) return memo[n];
    int64_t retval = foo(n-4) + foo(n-3) + foo(n-2) + foo(n-1);
    memo[n] = retval;
    return retval;
}

int main(void) {
    printf("%lld\n", foo(40));
    return 0;
}