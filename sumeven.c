// Sum even numbers between bottom and top
#include <stdio.h>

int sumEven(int bottom, int top) {
    top = top & ~1;
    bottom = (bottom+1) & ~1;  // make both even by making LSB 0
    int sum = 0;
    if (bottom > top) return 0;
    for (int i = bottom; i <= top; i += 2) sum += i;
    return sum;
}

int sumEvenArith(int bottom, int top) {
    top = top & ~1;
    bottom = (bottom+1) & ~1;  // make both even by making LSB 0
    if (bottom > top) return 0;
    return (((top - bottom) >> 1) + 1) * (bottom+top)/2;
}

int main(void) {
    printf("SumEven loop 1 through 10 - %d\n", sumEven(1, 10));
    printf("SumEven arith 1 through 10 - %d\n", sumEvenArith(1, 10));
    return 0;
}
