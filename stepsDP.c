//  Figure out steps path for 1 or 2 steps on stair size 1->n->MAXSTEPS
#include<stdio.h>
#define MAXSTEPS 5

int checkSteps(int step) {
    if(step > MAXSTEPS) return 0;   // End Case - bust
    if(step == MAXSTEPS) return 1;  // End Case - valid solution
    return checkSteps(step+1) + checkSteps(step+2);
}

int main(void) {
    int solCount = checkSteps(0);
    printf("%d solutions\n", solCount);
    return 0;
}