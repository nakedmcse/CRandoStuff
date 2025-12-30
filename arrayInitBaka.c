// Array Init Methods
#include<stdio.h>
#include<strings.h>

int main(void) {
    const int SIZE = 10;

    // Depends on compiler - gcc and clang support
    int a[SIZE] = {[0 ... SIZE-1] = 0};
    for (int i = 0; i < SIZE; printf("%d,",a[i++]));
    printf("\n");

    // Old school
    int b[SIZE];
    memset(b,0,SIZE*sizeof(int));
    for (int i = 0; i < SIZE; printf("%d,",b[i++]));
    printf("\n");

    // Older school
    int c[SIZE];
    for (int i = 0; i < SIZE; (c[i]=0, printf("%d,",c[i++])));
    printf("\n");
}