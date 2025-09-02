// 2023 day 5 parts 1 and 2
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

typedef struct mapping {
    long destStart;
    long sourceStart;
    long length;
} mapping;

typedef struct dynArray {
    mapping *values;
    size_t count;
    size_t capacity;
} dynArray;

typedef struct maps {
    dynArray *seeds;
    dynArray *seed2soil;
    dynArray *soil2fertilizer;
    dynArray *fertilizer2water;
    dynArray *water2light;
    dynArray *light2temp;
    dynArray *temp2humidity;
    dynArray *humidity2location;
} maps;

void append(dynArray *array, mapping value) {
    if (array->count >= array->capacity) {
        if (array->capacity == 0) {
            array->capacity = 256;
            array->values = (mapping*)malloc(array->capacity * sizeof(mapping));
        }
        else {
            array->capacity *= 2;
            array->values = (mapping*)realloc(array->values, array->capacity * sizeof(mapping));
        }
    }
    array->values[array->count++] = value;
}

// Part 1
// Iterate seeds through forward maps to find lowest location number, should be 111627841
// Maps go seed -> soil -> fertilizer -> water -> light -> temp -> humidity -> location
// maps are dest start, source start, length
// unmapped is 1-1
long transform(dynArray *map, long value) {
    for (int i = 0; i < map->count; i++) {
        if (value >= map->values[i].sourceStart && value <= map->values[i].sourceStart + map->values[i].length) {
            // In range
            long offset = value - map->values[i].sourceStart;
            return map->values[i].destStart + offset;
        }
    }
    return value;
}

long part1(maps* maps) {
    long minLocation = LONG_MAX;
    for (int i = 0; i < maps->seeds->count; i++) {
        long location = maps->seeds->values[i].destStart;
        location = transform(maps->seed2soil, location);
        location = transform(maps->soil2fertilizer, location);
        location = transform(maps->fertilizer2water, location);
        location = transform(maps->water2light, location);
        location = transform(maps->light2temp, location);
        location = transform(maps->temp2humidity, location);
        location = transform(maps->humidity2location, location);
        if (location < minLocation) minLocation = location;
    }
    return minLocation;
}

// Part 2
// Seeds are now start, length pairs, what is the lowest number now, should be 69323688
bool isValidSeed(dynArray *seeds, long value) {
    for (int i = 0; i < seeds->count; i += 2) {
        if (value >= seeds->values[i].destStart && value <= seeds->values[i].destStart + seeds->values[i+1].destStart) {
            return true;
        }
    }
    return false;
}

long reverseTransform(dynArray *map, long value) {
    for (int i = 0; i < map->count; i++) {
        if (value >= map->values[i].destStart && value <= map->values[i].destStart + map->values[i].length) {
            // In range
            long offset = value - map->values[i].destStart;
            return map->values[i].sourceStart + offset;
        }
    }
    return value;
}

long part2(maps* maps) {
    long minLocation = LONG_MAX;
    for (long i = 0; i < 1000000000; i++) {
        long location = reverseTransform(maps->humidity2location, i);
        location = reverseTransform(maps->temp2humidity, location);
        location = reverseTransform(maps->light2temp, location);
        location = reverseTransform(maps->water2light, location);
        location = reverseTransform(maps->fertilizer2water, location);
        location = reverseTransform(maps->soil2fertilizer, location);
        location = reverseTransform(maps->seed2soil, location);
        if (isValidSeed(maps->seeds, location)) {
            minLocation = i;
            break;
        }
    }
    return minLocation;
}

void getMaps(maps* maps) {
    FILE* file = fopen("2023_day5_input.txt", "r");
    char *line = NULL;
    char *token = NULL;
    size_t len = 0;

    // Seeds
    getline(&line, &len, file);
    token = strtok(line, " "); // skip first
    token = strtok(NULL, " ");
    while (token != NULL) {
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(token, "%ld", &temp->destStart);
        append(maps->seeds, *temp);
        token = strtok(NULL, " ");
    }

    // Seed 2 Soil
    getline(&line, &len, file);  // Skip blank
    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(maps->seed2soil, *temp);
    }

    // Soil 2 Fertilizer
    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(maps->soil2fertilizer, *temp);
    }

    // Fertilizer 2 Water
    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(maps->fertilizer2water, *temp);
    }

    // Water 2 Light
    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(maps->water2light, *temp);
    }

    // Light 2 Temp
    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(maps->light2temp, *temp);
    }

    // Temp 2 Humidity
    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(maps->temp2humidity, *temp);
    }

    // Humidity 2 Location
    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(maps->humidity2location, *temp);
    }

    fclose(file);

    printf("READ MAPS:\n");
    printf("Seeds: %lu Seed2Soil: %lu Soil2Fertilizer: %lu Fertilizer2Water: %lu\n",
        maps->seeds->count, maps->seed2soil->count, maps->soil2fertilizer->count, maps->fertilizer2water->count);
    printf("Water2Light: %lu Light2Temp: %lu Temp2Humidity: %lu Humidity2Location: %lu\n\n",
        maps->water2light->count, maps->light2temp->count, maps->temp2humidity->count, maps->humidity2location->count);
}

int main(void) {
    dynArray seeds = {NULL, 0, 0};
    dynArray seeds2soil = {NULL, 0, 0};
    dynArray soil2fertilizer = {NULL, 0, 0};
    dynArray fertilizer2water = {NULL, 0, 0};
    dynArray water2light = {NULL, 0, 0};
    dynArray light2temp = {NULL, 0, 0};
    dynArray temp2humidity = {NULL, 0, 0};
    dynArray humidity2location = {NULL, 0, 0};
    maps maps = {&seeds, &seeds2soil, &soil2fertilizer, &fertilizer2water, &water2light, &light2temp, &temp2humidity, &humidity2location};
    getMaps(&maps);

    printf("Part 1 lowest location - %ld\n", part1(&maps));
    printf("Part 2 lowest location - %ld\n", part2(&maps));

    return 0;
}