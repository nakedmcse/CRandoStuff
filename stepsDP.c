//  Figure out steps path for 1 or 2 steps on stair size 1->n->MAXSTEPS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAXSTEPS 35

typedef struct list {
    int value;
    struct list *next;
} list;

typedef struct arrayList {
    int *values;
    int headIdx, tailIdx, maxIdx;
} arrayList;

void initArrayList(arrayList *queue) {
    queue->values = NULL;
    queue->headIdx = 0;
    queue->tailIdx = 0;
    queue->maxIdx = 10000;
}

void appendArrayList(int value, arrayList *queue) {
    if(queue->values == NULL) queue->values = (int *)malloc(10000 * sizeof(int));
    if(queue->tailIdx > queue->maxIdx) {
        printf("Attempting realloc\n");
        queue->values = (int *)realloc(queue->values, (queue->maxIdx + 10000) * sizeof(int));
        queue->maxIdx += 10000;
    }
    queue->values[queue->tailIdx] = value;
    queue->tailIdx += 1;
}

int dequeueArrayList(arrayList *queue) {
    if(queue->values == NULL || queue->headIdx == queue->tailIdx) return -1;
    queue->headIdx += 1;
    return queue->values[queue->headIdx-1];
}

list *appendList(int value, list **queue, list *tail) {
    list *head = *queue;
    if(head == NULL) {
        *queue = malloc(sizeof(struct list));
        head = *queue;
        head->value = value;
        head->next = NULL;
        return head;
    }
    list *new = malloc(sizeof(struct list));
    new->value = value;
    new->next = NULL;
    if(tail) {
        head = tail;
    } else {
        while(head->next) { head = head->next; };
    }
    head->next = new;
    return new;
}

int dequeueList(list **list) {
    struct list *head = *list;
    if(head == NULL) return -1;
    int retval = head->value;
    *list = head->next;
    free(head);
    return retval;
}

// Recursive Solution
int checkStepsRecursive(int step) {
    if(step > MAXSTEPS) return 0;   // End Case - bust
    if(step == MAXSTEPS) return 1;  // End Case - valid solution
    return checkStepsRecursive(step+1) + checkStepsRecursive(step+2);
}

// Queue Solution
int checkStepsQueue() {
    //list *queue = NULL, *tail = NULL;
    //tail = appendList(0, &queue, NULL);
    static arrayList queue;
    initArrayList(&queue);
    appendArrayList(0, &queue);
    int solutions = 0;
    while(queue.tailIdx > queue.headIdx) {
        int value = dequeueArrayList(&queue);
        if(value > MAXSTEPS) continue;
        if(value == MAXSTEPS) {
            solutions++;
            continue;
        }
        appendArrayList(value+1, &queue);
        appendArrayList(value+2, &queue);
    }
    return solutions;
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
    int solCountQ = checkStepsQueue();
    double elapsedQ = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    start_time = clock();
    int solCountDP = checkStepsDP();
    double elapsedDP = (double)(clock() - start_time) / CLOCKS_PER_SEC;

    printf("%d steps\n", MAXSTEPS);
    printf("%d recursive solutions in %fs\n", solCountR, elapsedR);
    printf("%d queue solutions in %fs\n", solCountQ, elapsedQ);
    printf("%d DP solutions in %fs\n", solCountDP, elapsedDP);
    return 0;
}