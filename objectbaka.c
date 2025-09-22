// Object fun
#include <stdio.h>

typedef struct counter {
    int count;
    void (*inc)(void *);
    void (*dec)(void *);
    void (*dbl)(void *);
} counter;

void increment(void *c) {
    counter *ct = (counter *)c;
    ct->count++;
}

void decrement(void *c) {
    counter *ct = (counter *)c;
    ct->count--;
}

void double_counter(void *c) {
    counter *ct = (counter *)c;
    ct->count *= 2;
}


int main(void) {
    counter ct = {1, increment, decrement, double_counter};
    printf("Initial: %d,\n", ct.count);
    ct.inc(&ct);
    printf("Inc: %d,\n", ct.count);
    ct.dbl(&ct);
    printf("Double: %d,\n", ct.count);
    ct.dec(&ct);
    printf("Dec: %d\n", ct.count);
}