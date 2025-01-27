#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmpfunc(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main(void) {
    char *numbers[] = {"one", "two", "three"};
    qsort(numbers, 3, sizeof(char *), cmpfunc);
    for(int i = 0; i < 3; i++) printf("%s, ", numbers[i]);
    printf("\n");
    return 0;
}