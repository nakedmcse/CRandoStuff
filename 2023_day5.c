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
long transform(dynArray *map, long value, bool reverse) {
    for (int i = 0; i < map->count; i++) {
        if (reverse) {
            if (value >= map->values[i].destStart && value <= map->values[i].destStart + map->values[i].length) {
                // In reverse range
                long offset = value - map->values[i].destStart;
                return map->values[i].sourceStart + offset;
            }
        }
        else {
            if (value >= map->values[i].sourceStart && value <= map->values[i].sourceStart + map->values[i].length) {
                // In forward range
                long offset = value - map->values[i].sourceStart;
                return map->values[i].destStart + offset;
            }
        }
    }
    return value;
}

long part1(maps* maps) {
    long minLocation = LONG_MAX;
    for (int i = 0; i < maps->seeds->count; i++) {
        long location = maps->seeds->values[i].destStart;
        location = transform(maps->seed2soil, location, false);
        location = transform(maps->soil2fertilizer, location, false);
        location = transform(maps->fertilizer2water, location, false);
        location = transform(maps->water2light, location, false);
        location = transform(maps->light2temp, location, false);
        location = transform(maps->temp2humidity, location, false);
        location = transform(maps->humidity2location, location, false);
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

long part2(maps* maps) {
    long minLocation = LONG_MAX;
    for (long i = 0; i < 1000000000; i++) {
        long location = transform(maps->humidity2location, i, true);
        location = transform(maps->temp2humidity, location, true);
        location = transform(maps->light2temp, location, true);
        location = transform(maps->water2light, location, true);
        location = transform(maps->fertilizer2water, location, true);
        location = transform(maps->soil2fertilizer, location, true);
        location = transform(maps->seed2soil, location, true);
        if (isValidSeed(maps->seeds, location)) {
            minLocation = i;
            break;
        }
    }
    return minLocation;
}

void readMap(FILE* file, dynArray* map) {
    char *line = NULL;
    size_t len = 0;

    getline(&line, &len, file);  // Skip header
    while (getline(&line, &len, file) != -1) {
        if (strcmp(line,"\n") == 0) break;   // break on blank
        mapping *temp = (mapping*)malloc(sizeof(mapping));
        sscanf(line, "%ld %ld %ld", &temp->destStart, &temp->sourceStart, &temp->length);
        append(map, *temp);
    }
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
    readMap(file, maps->seed2soil);

    // Soil 2 Fertilizer
    getline(&line, &len, file);  // Skip header
    readMap(file, maps->soil2fertilizer);

    // Fertilizer 2 Water
    getline(&line, &len, file);  // Skip header
    readMap(file, maps->fertilizer2water);

    // Water 2 Light
    getline(&line, &len, file);  // Skip header
    readMap(file, maps->water2light);

    // Light 2 Temp
    getline(&line, &len, file);  // Skip header
    readMap(file, maps->light2temp);

    // Temp 2 Humidity
    getline(&line, &len, file);  // Skip header
    readMap(file, maps->temp2humidity);

    // Humidity 2 Location
    getline(&line, &len, file);  // Skip header
    readMap(file, maps->humidity2location);

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