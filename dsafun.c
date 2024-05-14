// Fun with DSA
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

// List def
typedef struct linkedList {
    int entry;
    struct linkedList *next;
} linkedList;

// Append entry
struct linkedList* appendEntry(struct linkedList *listHead, int value) {
    struct linkedList* origHead = listHead;
    if(listHead == NULL) {
        listHead = malloc(sizeof(struct linkedList));
        listHead->entry = value;
        listHead->next = NULL;
        return listHead;
    }
    while(listHead->next) {
        listHead = listHead->next;
    }
    listHead->next = malloc(sizeof(struct linkedList));
    listHead->next->entry = value;
    listHead->next->next = NULL;
    return origHead;
}

// Dump list
void dumpList(struct linkedList *listHead) {
    while(listHead) {
        printf("%d,",listHead->entry);
        listHead = listHead->next;
    }
    printf("E\n");
}

// Reverse list
struct linkedList* reverseList(struct linkedList *listHead) {
    struct linkedList *previous = NULL, *next = NULL;

    while(listHead) {
        next = listHead->next;
        listHead->next = previous;
        previous = listHead;
        listHead = next;
    }

    return previous;
}

// Main
int main(void) {
    struct linkedList *listHead = NULL;
    for(int i = 0; i<10; i++) {
        listHead = appendEntry(listHead,i);
    }
    dumpList(listHead);
    listHead = reverseList(listHead);
    dumpList(listHead);
}