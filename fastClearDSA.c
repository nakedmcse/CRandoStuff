// Fast Clear Bool Array
// Bool array with o(1) complete array clear
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct fastClear {
    int capacity;
    unsigned int falseValue;
    unsigned int *values;
} fastClear;

void init(fastClear *clear, int capacity) {
    clear->capacity = capacity;
    clear->falseValue = 0;
    clear->values = (unsigned int *) malloc(capacity * sizeof(int));
    if (clear->values == NULL) {
        printf("Error in init()\n");
        exit(1);
    }
}

void set(fastClear *clear, int index, bool value) {
    if (index >= 0 && index < clear->capacity) {
        clear->values[index] = clear->falseValue+1;
    }
}

bool get(fastClear *clear, int index) {
    if (index >= 0 && index < clear->capacity) {
        return clear->values[index] > clear->falseValue;
    }
    return false;
}

void clear(fastClear *clear) {
    clear->falseValue++;
}

void dispose(fastClear *clear) {
    free(clear->values);
}

int main(void) {
    fastClear bools;
    init(&bools, 10);
    set(&bools, 5, true);
    printf("After init and set, entry 5 %s\n", get(&bools, 5) ? "true" : "false");
    clear(&bools);
    printf("After clear, entry 5 %s\n", get(&bools, 5) ? "true" : "false");
    dispose(&bools);
    return 0;
}
