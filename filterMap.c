#include<stdio.h>

int main(void) {
    int numbers[10] = {1,2,3,4,5,6,7,8,9,10};
    int outnumbers[5], o = 0;
    for(int i = 0; i < 10; i++) if(numbers[i] % 2 == 0) outnumbers[o++] = numbers[i]*numbers[i];
    for(int j = 0; j < 5; j++) printf("%d,", outnumbers[j]);
    printf("\n");
    return 0;
}