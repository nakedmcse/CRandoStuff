// Given a numbers of rooms n, and a list of meetings [starttime, endtime],
// return the room that held the most meetings.

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct room {
    int id;
    int meetingsHeld;
    int currentEndTime;
} room;

// Min heap implementation
void swap(room *a, room *b) {
    room temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(room arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].currentEndTime == arr[smallest].currentEndTime && arr[left].id < arr[smallest].id)
        smallest = left;
    else if (right < n && arr[right].currentEndTime == arr[smallest].currentEndTime && arr[right].id < arr[smallest].id)
        smallest = right;
    else if (left < n && arr[left].currentEndTime < arr[smallest].currentEndTime)
        smallest = left;
    else if (right < n && arr[right].currentEndTime < arr[smallest].currentEndTime)
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void heapPush(room **arr, int *n, int id, int endTime, int meetingsHeld) {
    *n += 1;
    *arr = realloc(*arr, *n * sizeof(room));
    int i = *n - 1;
    (*arr)[i].id = id;
    (*arr)[i].currentEndTime = endTime;
    (*arr)[i].meetingsHeld = meetingsHeld;

    while (i != 0 && (*arr)[(i - 1) / 2].currentEndTime > (*arr)[i].currentEndTime) {
        swap(&(*arr)[i], &(*arr)[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

room heapPop(room **arr, int *n) {
    if (*n <= 0)
        return (room){.id = -1, .meetingsHeld = 0, .currentEndTime = 0};

    room root = (*arr)[0];
    (*arr)[0] = (*arr)[*n - 1];
    *n -= 1;
    *arr = realloc(*arr, *n * sizeof(room));
    heapify(*arr, *n, 0);

    return root;
}

void dumpHeap(room *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d: %d,%d / ", arr[i].id, arr[i].currentEndTime, arr[i].meetingsHeld);
    }
    printf("\n");
}

int comparator(const void *a, const void *b) {
    const int *row_a = (int *)a;
    const int *row_b = (int *)b;
    return row_a[0] - row_b[0];
}

int mostBooked(int n, int meetings[][2], int meetingsCount) {
    room *roomHeap = NULL;
    int heapSize = 0;
    // Sort meetings
    qsort(meetings, meetingsCount, sizeof(meetings[0]), comparator);
    // Build room heap
    for (int i = 0; i < n; i++) heapPush(&roomHeap, &heapSize, i, 0, 0);
    // Process meetings
    for (int i = 0; i < meetingsCount; i++) {
        if (meetings[i][0] >= roomHeap[0].currentEndTime) {
            // Can host meeting - insert end time
            roomHeap[0].meetingsHeld++;
            roomHeap[0].currentEndTime = meetings[i][1];
            heapify(&roomHeap[0], heapSize, 0);
        } else {
            // Meeting delayed - add duration to end time
            roomHeap[0].meetingsHeld++;
            roomHeap[0].currentEndTime += meetings[i][1]-meetings[i][0];
            heapify(&roomHeap[0], heapSize, 0);
        }
    }
    // Find max bookings
    int maxBookings = 0;
    int maxBookingsIndex = 99999999;
    for (int i = 0; i < heapSize; i++) {
        if (roomHeap[i].meetingsHeld >= maxBookings && maxBookingsIndex > roomHeap[i].id) {
            maxBookings = roomHeap[i].meetingsHeld;
            maxBookingsIndex = roomHeap[i].id;
        }
    }
    dumpHeap(&roomHeap[0], heapSize);
    return maxBookingsIndex;
}

int main(void) {
    int meetings1[4][2] = {{0,10},{1,5},{2,7},{3,4}};
    int meetings2[5][2] = {{1,20},{2,10},{3,5},{4,9},{6,8}};
    clock_t start_time = clock();
    printf("Max bookings for example 1 - %d\n", mostBooked(2, meetings1, 4));
    printf("Max bookings for example 2 - %d\n", mostBooked(3, meetings2, 5));
    double elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Runtime: %fms\n", elapsed*1000);
}