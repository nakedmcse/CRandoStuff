// Default arguments in C
#include <stdio.h>

#define multiply(...) MULTIPLY(__VA_ARGS__, 2, 0)
#define MULTIPLY(a, b, ...) multiply(a, b)

int (multiply)(int a, int b) {
    return a * b;
}

int main(void) {
    printf("%d\n", multiply(5, 4));
    printf("%d\n", multiply(5));
    return 0;
}