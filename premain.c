// Example of running a function BEFORE main
#include<stdio.h>

// Apply constructor/destructor
void preMain(void) __attribute__ ((constructor));
void postMain(void) __attribute__ ((destructor));

// preMain function
void preMain(void) {
    printf("This will run before main starts\n");
}

// postMain function
void postMain(void) {
    printf("This will run after main ends\n");
}

// Main
int main(void) {
    printf("This is main running\n");
    return 0;
}