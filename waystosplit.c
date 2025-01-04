//  Return the number of ways to split an array such that sum(0-n) >= sum(n+1 - last)
#include<stdio.h>

int waysToSplit(int* nums, int size) {
    int retval = 0, lsum = 0, rsum = 0, i = 0, j = 0;
    while(i < size-1) {
        lsum += nums[i];
        if(i == 0) while(++j < size) rsum += nums[j];
        else rsum -= nums[i];
        if(lsum >= rsum) retval++;
        i++;
    }
    return retval;
}

int main(void) {
    int testCase1[4] = {10,4,-8,7};
    int testCase2[4] = {2,3,1,0};
    int testCase3[100000];
    int testCase4[100000];

    for(int i = 0; i<100000; i++) {
        testCase3[i] = i;
        testCase4[i] = 100000-i;
    }

    printf("Test case 1 - [10,4,-8,7] - should return 2 - %d\n", waysToSplit(&testCase1[0], 4));
    printf("Test case 2 - [2,3,1,0] - should return 2 - %d\n", waysToSplit(&testCase2[0], 4));
    printf("Test case 3 - 100k entries all increasing - %d\n", waysToSplit(&testCase3[0], 100000));
    printf("Test case 4 - 100k entries all decreasing - %d\n", waysToSplit(&testCase4[0], 100000));
}