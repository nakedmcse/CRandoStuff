// Knights tour
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct point {
    int x;
    int y;
    bool visited[8][8];
} point;

typedef struct moves {
    point moves[8];
} moves;

typedef struct pointQueue {
    point *values;
    int capacity;
    int size;
} pointQueue;

void append(pointQueue *queue, point value) {
    if (queue->size >= queue->capacity) {
        if (queue->capacity == 0) {
            queue->capacity = 256;
            queue->values = (point*)malloc(queue->capacity * sizeof(point));
        }
        else {
            queue->capacity *= 2;
            queue->values = (point*)realloc(queue->values, queue->capacity * sizeof(point));
        }
    }
    queue->values[queue->size++] = value;
}

point pop(pointQueue *queue) {
    point empty;
    if (queue->size == 0) {
        empty.x = -1;
        empty.y = -1;
        memset(empty.visited, false, sizeof(bool) * 64);
        return empty;
    }
    return queue->values[--queue->size];
}

bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < 8 && y < 8;
}

bool isComplete(point p) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (p.visited[i][j] == false) return false;
        }
    }
    return true;
}

moves getMoves(point p) {
    point validMoves[8] = {
        {1, 2 }, {1, -2},
        {-1, 2 }, {-1, -2},
        {2, 1}, {2, -1},
        {-2, 1}, {-2, -1}
    };

    moves retMoves;
    int modX, modY = 0;
    for (int i = 0; i < 8; i++) {
        modX = p.x + validMoves[i].x; modY = p.y + validMoves[i].y;
        retMoves.moves[i] = (point){-1, -1};
        if (isValid(modX, modY) && p.visited[modX][modY] == false) {
            retMoves.moves[i].x = modX; retMoves.moves[i].y = modY;
            memcpy(retMoves.moves[i].visited, p.visited, sizeof(bool) * 64);
        }
    }

    return retMoves;
}

int countMoves(moves m) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (m.moves[i].x != -1) count++;
    }
    return count;
}

moves getMinimalForwardMoves(moves o) {
    moves retMoves;
    int moveCounts[8] = {9999,9999,9999,9999,9999,9999,9999,9999};
    int minMoves = 9999;
    for (int i = 0; i < 8; i++) {
        if (o.moves[i].x != -1) moveCounts[i] = countMoves(getMoves(o.moves[i]));
        if (moveCounts[i] < minMoves) minMoves = moveCounts[i];
    }
    for (int i = 0; i < 8; i++) {
        if (moveCounts[i] == minMoves) retMoves.moves[i] = o.moves[i];
        else { retMoves.moves[i].x = -1; retMoves.moves[i].y = -1; }
    }
    return retMoves;
}

int knightstour(point p) {
    int solutions = 0;
    pointQueue queue = {NULL, 0, 0};
    append(&queue, p);

    while (queue.size > 0) {
        point next = pop(&queue);
        if (next.x == -1 && next.y == -1) break;  // somehow got past the end of the queue
        next.visited[next.x][next.y] = true;

        if (isComplete(next)) {
            // Tour Completed
            solutions++;
            continue;
        }

        moves m = getMinimalForwardMoves(getMoves(next));
        for (int i = 0; i < 8; i++) {
            if (m.moves[i].x != -1) append(&queue, m.moves[i]);
        }
    }
    return solutions;
}

int main(void) {
    point start = {2, 2};
    memset(start.visited, false, sizeof(bool) * 64);
    printf("Knights Tour from point (2,2) - %d\n", knightstour(start));
    return 0;
}
