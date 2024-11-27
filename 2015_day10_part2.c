//2015 day 10 part 1 & 2
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *runLenEncode(const char *s) {
    char *retval = (char *)malloc(strlen(s) * 2 + 1);
    char append[16];
    retval[0] = '\0';
    char cur, prev = s[0];
    int runlen = 1;
    for(int i = 1; i < strlen(s); i++) {
        cur = s[i];
        if(runlen > 9) {
            snprintf(append, sizeof(append), "9%c", prev);
            strcat(retval, append);
            runlen = 1;
        }
        if(cur == prev) {
            runlen++;
        } else {
            snprintf(append, sizeof(append), "%d%c", runlen, prev);
            strcat(retval, append);
            runlen = 1;
        }
        prev = cur;
    }

    if (runlen > 0) {
        snprintf(append, sizeof(append), "%d%c", runlen, prev);
        strcat(retval, append);
    }

    return retval;
}

int main(void) {
    char *encoded1 = "1321131112";
    for(int i = 0; i < 40; i++) encoded1 = runLenEncode(encoded1);
    printf("Part 1: %lu\n", strlen(encoded1));
    free(encoded1);

    char *encoded2 = "1321131112";
    for(int i = 0; i < 50; i++) encoded2 = runLenEncode(encoded2);
    printf("Part 2: %lu\n", strlen(encoded2));
    free(encoded2);

    return 0;
}
