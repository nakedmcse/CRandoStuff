// Ouroboros pointers
#include<stdio.h>

int main(void) {
    int origin = 42;
    int *tail;
    int **body;
    int ***head;

    tail = &origin;
    body = &tail;
    head = &body;

    printf("%d->%d->%d\n", ***head, **body, *tail);
    return 0;
}