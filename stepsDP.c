//  Figure out steps path for 1 or 2 steps on stair size 1->n->MAXSTEPS
#include<stdio.h>
#include<time.h>
#define MAXSTEPS 45

// Recursive Solution
int checkStepsRecursive(int step) {
    if(step > MAXSTEPS) return 0;   // End Case - bust
    if(step == MAXSTEPS) return 1;  // End Case - valid solution
    return checkStepsRecursive(step+1) + checkStepsRecursive(step+2);
}

// Dynamic Programming Solution
int checkStepsDP() {
    int steps[MAXSTEPS+1] = {0};

    steps[0] = 1;  // One way for no steps
    steps[1] = 1;  // One way for one step

    for(int i=2; i<=MAXSTEPS; i++) {
        steps[i] = steps[i-1] + steps[i-2];  // step i can be reached from 1 step before or 2 steps
    }

    return steps[MAXSTEPS];
}

int main(void) {
    clock_t start_time = clock();
    int solCountR = checkStepsRecursive(0);
    double elapsedR = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    start_time = clock();
    int solCountDP = checkStepsDP();
    double elapsedDP = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    printf("%d steps\n", MAXSTEPS);
    printf("%d recursive solutions in %fs, %d DP solutions in %fs\n", solCountR, elapsedR, solCountDP, elapsedDP);
    return 0;
}