// Given a string and a list of transforms [x,y,d] where x is the start index and y is the end index and d is 0 for 'down' (a becomes z)
// or 1 for 'up' (z becomes a)
#include<stdio.h>

char shiftChar(char c, int d) {
    if(d == 0) return (--c == 96 ? 122 : c);
    return (++c == 123 ? 97 : c);
}

char *shiftingLetters(char *s, int **shifts, int shiftsSize) {
    for(int i = 0; i<shiftsSize; i++) {
        int *current = shifts[i];
        int start = current[0], end = current[1], dir = current[2];
        for(int j = start; j<=end; j++) s[j] = shiftChar(s[j], dir);
    }
    return s;
}

int main(void) {
    int c1t1[3] = {0,1,0}, c1t2[3] = {1,2,1}, c1t3[3] = {0,2,1};
    int *testcase1[3] = {&c1t1[0], &c1t2[0], &c1t3[0]};
    char input1[4] = "abc\0";

    int c2t1[3] = {0,0,0}, c2t2[3] = {1,1,1};
    int *testcase2[2] = {&c2t1[0], &c2t2[0]};
    char input2[5] = "dztz\0";

    printf("Test case 1 - 'abc' and [[0,1,0],[1,2,1],[0,2,1]] - should return 'ace' - %s\n", shiftingLetters(input1, &testcase1[0], 3));
    printf("Test case 2 - 'dztz' and [[0,0,0],[1,1,1]] - should return 'catz' - %s\n", shiftingLetters(input2, &testcase2[0], 2));
}
