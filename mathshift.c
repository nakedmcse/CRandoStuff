// Time 1B mathshift and mask
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {
    int testCases[1000000];
    for(int i=0; i<1000000; i++) {
        testCases[i] = rand() % 1000;
    }

    clock_t start_time = clock();
    for(int j=0; j<1000; j++) {
        for(int i=0; i<1000000; i++) {
            testCases[i] = (testCases[i] / 65536) % 256;
        }
    }
    double elapsedR = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Math shift time: %fs\n",elapsedR);
    printf("5th element %d\n", testCases[4]);
}