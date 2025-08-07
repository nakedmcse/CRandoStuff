// Simple dynamic array
#include <stdio.h>
#include <stdlib.h>

typedef struct dynArray {
    int *values;
    size_t count;
    size_t capacity;
} dynArray;

void append(dynArray *array, int value) {
    if (array->count >= array->capacity) {
        if (array->capacity == 0) {
            array->capacity = 256;
            array->values = (int*)malloc(array->capacity * sizeof(int));
        }
        else {
            array->capacity *= 2;
            array->values = (int*)realloc(array->values, array->capacity * sizeof(int));
        }
    }
    array->values[array->count++] = value;
}

int main(void) {
    dynArray array = { NULL, 0, 0 };
    for (int i = 0; i < 1000; i++) append(&array, i);
    for (int i = 0; i < array.count; i++) printf("%d ", array.values[i]);
    return 0;
}