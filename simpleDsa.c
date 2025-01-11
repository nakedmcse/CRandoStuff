// Simple list, dyn array and hashtable
#include<stdio.h>
#include<stdlib.h>

// List
typedef struct listNode {
    int value;
    struct listNode *next;
} listNode;

typedef struct list {
    struct listNode *head;
    struct listNode *tail;
    unsigned int count;
} list;

void addList(list* l, int value) {
    listNode *newNode = malloc(sizeof(listNode));
    newNode->value = value;
    newNode->next = NULL;
    if(l->head == NULL) l->head = newNode;
    if(l->tail != NULL) l->tail->next = newNode;
    l->tail = newNode;
    l->count++;
}

void removeList(list* l, int value) {
    listNode *current = l->head, *prev = NULL;
    if(l->head == NULL) return;
    while(current != NULL) {
        if(current->value == value) {
            if(prev != NULL) prev->next = current->next;
            else l->head = current->next;
            l->count--;
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

int* popList(list* l) {
    static int retval;
    listNode* newHead = NULL;
    if(l->head == NULL) return NULL;
    newHead = l->head->next;
    retval = l->head->value;
    free(l->head);
    l->count--;
    l->head = newHead;
    return &retval;
}

void printList(list* l) {
    listNode* current = l->head;
    if(l->head == NULL) {
        printf("Empty List\n");
        return;
    }
    while(current != NULL) {
        printf("%d, ", current->value);
        current = current->next;
    }
    printf("\n");
}

list* createList() {
    list* newList;
    newList = (list*)malloc(sizeof(list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->count = 0;
    return newList;
}

void destroyList(list* l) {
    if(l == NULL) return;
    listNode* current = l->head;
    while(current != NULL) {
        listNode* next = current->next;
        free(current);
        current = next;
    }
    free(l);
}

int main(void) {
    list *linkedList = createList();
    for(int i = 1; i<21; i++) {
        addList(linkedList, i);
    }

    printList(linkedList);
    printf("%d entries\n", linkedList->count);

    removeList(linkedList, 5);
    printList(linkedList);
    printf("%d entries\n", linkedList->count);

    while(linkedList->count > 0) {
        printf("%d, ", *popList(linkedList));
    }

    destroyList(linkedList);
}