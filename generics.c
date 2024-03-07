// Generics in C
#include <stdio.h>

#define doSomething(T) _Generic((T),\
        char*: "String",\
        int: "Int",\
        default: "Unknown")

int main(void) {
    printf("%s\n", doSomething("string"));
    printf("%s\n", doSomething(1));
    printf("%s\n", doSomething(1.01));
    return 0;
}