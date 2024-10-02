#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

bool isOddMath(int num) {
    return num % 2;
}

bool isOddBit(int num) {
    return num & 1;
}

int main(void) {
    int testCases[1000000];
    bool bitRes[1000000];
    bool mathRes[1000000];

    for(int i=0; i<1000000; i++) {
        testCases[i] = rand() % 1000;
    }

    clock_t start_time = clock();
    for(int i=0; i<1000000; i++) {
        bitRes[i] = isOddBit(testCases[i]);
    }
    double elapsedR = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Bit comparison time: %fs\n",elapsedR);

    start_time = clock();
    for(int i=0; i<1000000; i++) {
        mathRes[i] = isOddMath(testCases[i]);
    }
    elapsedR = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Math comparison time: %fs\n",elapsedR);
}
