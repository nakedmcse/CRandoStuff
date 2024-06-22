// Leibniz Approximation of Pi
#include <stdio.h>

double leibniz(int iterations) {
    double n = 1.0;
    double topterm = -1.0;

    for(int i = 2; i<iterations; i++) {
        double bottomterm = (double)i * 2.0;
        double term = topterm / (bottomterm - 1.0);
        n += term;
        topterm = -topterm;
    }

    return n*4.0;
}

int main(void) {
    printf("Leibniz Approximation of Pi\n");
    printf("%f\n",leibniz(1000000000));
}