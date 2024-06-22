// Sorting Ints
#include<stdio.h>
#include<stdlib.h>

int compare(const void* a, const void* b) {
    return *((int*)a)-*((int*)b);
}

int main() {
    int list[8] = {5,3,2,1,6,8,9,0}, i=0;
    qsort(list, 8, sizeof(int), compare);
    for(i=0; i<8; i++) printf("%d ", list[i]);
    printf("\n");
}