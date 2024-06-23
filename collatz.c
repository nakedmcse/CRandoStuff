// Collatz in C
#include<stdio.h>
#include<stdlib.h>

// Memo entry structure
typedef struct memoEntry {
    long entry;
    int steps;
} memoEntry;

// Memoized collatz
static int collatz(long seed, struct memoEntry *memos, long memo_size) {
    int steps = 0;
    memoEntry entry;
    while(seed > 1) {
        entry = memos[seed % memo_size];
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
    long memo_size = 100000000;
    memoEntry *memo = (memoEntry *)calloc(memo_size, sizeof(memoEntry));

    for(long i = 1; i<1000000000; i++) {
        int steps = collatz(i,&memo[0],memo_size);
        memo[i % memo_size].entry = i;
        memo[i % memo_size].steps = steps;
        if(i % 10000000 == 0) printf("Seed:%ld Steps:%d\n",i,steps);
    }

    free(memo);
    return 0;
}
