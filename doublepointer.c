// Example of double pointer object isolation
#include<stdio.h>

typedef struct LongPair {
    long first;
    long second;
    long third;
} LongPair;

int main(void){
    LongPair object;          // the actual object
    LongPair *pointer;        // pointer to object
    LongPair **doublepointer; // double pointer to pointer

    object.first = 1;
    object.second = 2;
    object.third = 3;

    pointer = &object;
    doublepointer = &pointer;

    // First level pointer can access properties
    printf("Pointer Values are %d, %d, %d\n", pointer->first, pointer->second, pointer->third);

    // Double pointers cannot - NOTICE RED LINES BELOW - it will not compile
    printf("Double Pointer Values are %d, %d, %d\n", doublepointer->first, doublepointer->second, doublepointer->third);
}