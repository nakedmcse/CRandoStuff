// 2015 day 14 parts 1 and 2
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct reindeer {
    char name[10];
    int speed;
    int sustain;
    int rest;
    int distance;
    int points;
} reindeer;

typedef struct dynArray {
    reindeer *values;
    size_t count;
    size_t capacity;
} dynArray;

void append(dynArray *array, reindeer value) {
    if (array->count >= array->capacity) {
        if (array->capacity == 0) {
            array->capacity = 256;
            array->values = (reindeer*)malloc(array->capacity * sizeof(reindeer));
        }
        else {
            array->capacity *= 2;
            array->values = (reindeer*)realloc(array->values, array->capacity * sizeof(reindeer));
        }
    }
    array->values[array->count++] = value;
}

// Part 1 - read definitions of reindeer and show how far winner travelled in 2503 seconds - should be 2640
int calcDistance(reindeer r, int timeElapsed) {
    int blockTime = r.sustain + r.rest;
    int blocks = timeElapsed / blockTime;
    int remaining = timeElapsed % blockTime;
    if (remaining > r.sustain) remaining = r.sustain;
    int distance = (blocks * r.sustain * r.speed) + (remaining * r.speed);
    return distance;
}

int part1(dynArray *reindeers) {
    int maxDistance = 0;
    for (int i = 0; i < reindeers->count; i++) {
        reindeers->values[i].distance = calcDistance(reindeers->values[i], 2503);
        if (reindeers->values[i].distance > maxDistance) {
            maxDistance = reindeers->values[i].distance;
        }
    }
    return maxDistance;
}

// Part 2 - the lead reindeer on each second gets 1 point (multiple same all get the point), how many points does the winner have in 2503 seconds - should be 1102
int part2(dynArray *reindeers) {
    int maxPoints = 0;
    for (int k = 0; k < reindeers->count; k++) reindeers->values[k].distance = 0;
    for (int i = 1; i<2503; i++) {
        int maxDistance = 0;
        // Work out distances on each second
        for (int j = 0; j < reindeers->count; j++) {
            reindeers->values[j].distance = calcDistance(reindeers->values[j], i);
            if (reindeers->values[j].distance > maxDistance) {
                maxDistance = reindeers->values[j].distance;
            }
        }
        // Figure out who gets points - all that match the max distance for that second
        for (int j = 0; j < reindeers->count; j++) {
            if (reindeers->values[j].distance == maxDistance) reindeers->values[j].points++;
        }
    }
    for (int i = 0; i < reindeers->count; i++) {
        if (reindeers->values[i].points > maxPoints) {
            maxPoints = reindeers->values[i].points;
        }
    }
    return maxPoints;
}

int main(void) {
    dynArray reindeerArray = { NULL, 0, 0 };
    reindeer r = {"", 0, 0, 0, 0, 0};
    FILE* file = fopen("day14input.txt", "r");
    while (fscanf(file, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", r.name, &r.speed, &r.sustain, &r.rest) != -1) {
        append(&reindeerArray, r);
    }
    fclose(file);

    for (size_t i = 0; i < reindeerArray.count; i++) {
        printf("%s %d %d %d\n", reindeerArray.values[i].name, reindeerArray.values[i].speed, reindeerArray.values[i].sustain, reindeerArray.values[i].rest);
    }
    printf("\n");

    printf("Part 1 - Distance covered by winner in 2503s: %d\n", part1(&reindeerArray));
    printf("Part 2 - Points scored by winner in 2503s: %d\n", part2(&reindeerArray));
    return 0;
}
