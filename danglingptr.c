// Dangling pointer
#include <stdio.h>
int *rp;

void dangling() {
    int x = 10;
    rp = &x;
}

int main(void) {
    int *r;
    {
        int x = 5;
        r = &x;
    }
    printf("%d\n", *r);

    dangling();
    printf("%d\n", *rp);

    return 0;
}