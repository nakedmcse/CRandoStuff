// Collatz in C
#include<stdio.h>

// Memo entry structure
typedef struct memoEntry {
    long entry;
    int steps;
} memoEntry;

// Memoized collatz
static int collatz(long seed, struct memoEntry *memos) {
    int steps = 0;
    memoEntry entry;
    while(seed > 1) {
        entry = memos[seed % 500000];
        if(entry.steps>0 && entry.entry==seed) {
            steps += entry.steps;
            break;
        }
        if(seed % 2 == 0) {
            steps++;
            seed /= 2;
            continue;
        }
        steps++;
        seed = seed * 3 + 1;
    }
    return steps;
}

int main(void) {
    memoEntry memo[500000];
    for(long i = 1; i<100000000; i++) {
        int steps = collatz(i,&memo[0]);
        memo[i % 500000].entry = i;
        memo[i % 500000].steps = steps;
        if(i % 500000 == 0) printf("Seed:%ld Steps:%d\n",i,steps);
    }
    return 0;
}
