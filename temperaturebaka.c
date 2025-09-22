// Temperature stupidity
#include <stdio.h>

int main(void) {
    void *opts[2] = { &&tooCold, &&notTooCold };
    int temperature = 15;

    goto *opts[temperature>20];

    tooCold:
        printf("Its a wee bit chilly\n");

    notTooCold:
        return 0;
}