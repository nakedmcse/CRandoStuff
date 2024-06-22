// Filter and sort a list
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

// Append entry in correct position
struct linkedList* appendSortedEntry(struct linkedList *listHead, int value) {
    struct linkedList *origHead = listHead, *prev = NULL;

    if(listHead == NULL) {
        listHead = malloc(sizeof(struct linkedList));
        listHead->entry = value;
        listHead->next = NULL;
        return listHead;
    }

    while(listHead->next) {
        if(listHead->entry > value) break;
        prev = listHead;
        listHead = listHead->next;
    }

    if(prev) {
        prev->next = malloc(sizeof(struct linkedList));
        prev->next->entry = value;
        prev->next->next = listHead;
    } else {
        prev = malloc(sizeof(struct linkedList));
        prev->entry = value;
        prev->next = listHead;
        origHead = prev;
    }

    return origHead;
}

// Filter and Sort list
struct linkedList* sortFilter(struct linkedList *listHead, int threshold) {
    struct linkedList *filtered = NULL;

    if(listHead == NULL) return listHead;

    while(listHead) {
        if(listHead->entry > threshold) filtered = appendSortedEntry(filtered, listHead->entry);
        listHead = listHead->next;
    }

    return filtered;
}

// Main
int main(void) {
    struct linkedList *listHead = NULL, *filteredList = NULL;
    for(int i = 10; i>0; i--) {
        listHead = appendEntry(listHead,i);
    }
    dumpList(listHead);
    filteredList = sortFilter(listHead,5);
    dumpList(filteredList);
}