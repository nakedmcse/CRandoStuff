// Multi Dimensional Array 8 bit C
#include<stdio.h>

#define FRAMES 10
#define PLANES 3
#define YRES 180
#define XRES 320

typedef struct row {
    int col[XRES];
} row;

typedef struct plane {
    row rows[YRES];
} plane;

typedef struct frame {
    plane planes[PLANES];
} frame;

typedef struct video {
    frame frames[FRAMES];
} video;

int main(void) {
    int video[FRAMES][PLANES][YRES][XRES] = {0};

    printf("%d\n", video[5][1][100][100]);
    return 0;
}
