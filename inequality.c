// Stupid C Tricks
#include <stdio.h>
#define a ++b

int main(void) {
    int b = 0;
    if(a == 1 && a == 2 && a == 3) printf("Yes, it does\n");
}