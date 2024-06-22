// Generics in C
#include <stdio.h>
#include <string.h>
#include "generics-types.h"

#define doSomething(T) _Generic((T),\
        struct ints: handle_ints,\
        struct strings: handle_strings) (T)

int main(void) {
    ints IntsObj;
    IntsObj.a = 1;
    IntsObj.b = 2;

    strings StringsObj;
    StringsObj.a = "One";
    StringsObj.b = "Two";

    printf("%s\n", doSomething(StringsObj));
    printf("%d\n", doSomething(IntsObj));
    return 0;
}