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
    point upleft;
    point upright;
    point downleft;
    point downright;
    point leftup;
    point leftdown;
    point rightup;
    point rightdown;
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
    moves m = {{-1,-1},{-1,-1},{-1,-1},{-1,-1},
                {-1, -1}, {-1, -1}, {-1, -1}, {-1,-1}};

    if (isValid(p.x+1, p.y+2) && p.visited[p.x+1][p.y+2] == false) {
        m.upright.x = p.x + 1;
        m.upright.y = p.y + 2;
        memcpy(m.upright.visited, p.visited, 64 * sizeof(bool));
    }
    if (isValid(p.x-1, p.y+2) && p.visited[p.x-1][p.y+2] == false) {
        m.upleft.x = p.x - 1;
        m.upleft.y = p.y + 2;
        memcpy(m.upleft.visited, p.visited, 64 * sizeof(bool));
    }
    if (isValid(p.x+1, p.y-2) && p.visited[p.x+1][p.y-2] == false) {
        m.downright.x = p.x + 1;
        m.downright.y = p.y - 2;
        memcpy(m.downright.visited, p.visited, 64 * sizeof(bool));
    }
    if (isValid(p.x-1, p.y-2) && p.visited[p.x-1][p.y-2] == false) {
        m.downleft.x = p.x - 1;
        m.downleft.y = p.y - 2;
        memcpy(m.downleft.visited, p.visited, 64 * sizeof(bool));
    }
    if (isValid(p.x+2, p.y+1) && p.visited[p.x+2][p.y+1] == false) {
        m.rightup.x = p.x + 2;
        m.rightup.y = p.y + 1;
        memcpy(m.rightup.visited, p.visited, 64 * sizeof(bool));
    }
    if (isValid(p.x+2, p.y-1) && p.visited[p.x+2][p.y-1] == false) {
        m.rightdown.x = p.x + 2;
        m.rightdown.y = p.y - 1;
        memcpy(m.rightdown.visited, p.visited, 64 * sizeof(bool));
    }
    if (isValid(p.x-2, p.y+1) && p.visited[p.x-2][p.y+1] == false) {
        m.leftup.x = p.x - 2;
        m.leftup.y = p.y + 1;
        memcpy(m.leftup.visited, p.visited, 64 * sizeof(bool));
    }
    if (isValid(p.x-2, p.y-1) && p.visited[p.x-2][p.y-1] == false) {
        m.leftdown.x = p.x - 2;
        m.leftdown.y = p.y - 1;
        memcpy(m.leftdown.visited, p.visited, 64 * sizeof(bool));
    }

    return m;
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

        moves m = getMoves(next);
        if (m.upleft.x != -1 && m.upleft.y != -1) append(&queue, m.upleft);
        if (m.upright.x != -1 && m.upright.y != -1) append(&queue, m.upright);
        if (m.downleft.x != -1 && m.downleft.y != -1) append(&queue, m.downleft);
        if (m.downright.x != -1 && m.downright.y != -1) append(&queue, m.downright);
        if (m.leftup.x != -1 && m.leftup.y != -1) append(&queue, m.leftup);
        if (m.leftdown.x != -1 && m.leftdown.y != -1) append(&queue, m.leftdown);
        if (m.rightup.x != -1 && m.rightup.y != -1) append(&queue, m.rightup);
        if (m.rightdown.x != -1 && m.rightdown.y != -1) append(&queue, m.rightdown);
    }
    return solutions;
}

int main(void) {
    point start = {2, 2};
    memset(start.visited, false, sizeof(bool) * 64);
    printf("Knights Tour solutions from point (2,2) - %d\n", knightstour(start));
    return 0;
}
