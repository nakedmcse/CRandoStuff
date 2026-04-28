// Game of Life
#define WIDTH 80
#define HEIGHT 40
#define MAXGENERATIONS 400
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

void renderGeneration(char grid[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%c", grid[y][x]);
        }
        printf("\n");
    }
}

void setRandomPatch(char grid[][WIDTH], int x, int y, int w, int h) {
    srand(time(NULL));
    for (int py = y; py < y+h; py++) {
        for (int px = x; px < x+w; px++) {
            if (rand() % 100 < 25) grid[py][px] = '#';
        }
    }
}

int countNeighbours(char grid[][WIDTH], int x, int y) {
    int directions[8][2] = {
        {1,0},{0,1},{-1,0},{0,-1},
        {1,1},{-1,1},{1,-1}, {-1,-1}
    };
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int offsetX = x + directions[i][0];
        int offsetY = y + directions[i][1];
        if (grid[offsetY][offsetX] == '#') count++;
    }
    return count;
}

bool checkAllDead(char grid[][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (grid[y][x] == '#') return false;
        }
    }
    return true;
}

int main(void) {
    char grid[HEIGHT][WIDTH];
    char previousGrid[HEIGHT][WIDTH];
    int i = 0;

    memset(grid, ' ', sizeof(char) * HEIGHT * WIDTH);
    memset(previousGrid, ' ', sizeof(char) * HEIGHT * WIDTH);

    setRandomPatch(grid, 30, 15, 20, 10);
    while (!checkAllDead(grid) && i<MAXGENERATIONS) {
        memcpy(previousGrid, grid, WIDTH * HEIGHT * sizeof(char));
        for (int y = 0; y < HEIGHT; y++) {
            for (int x = 0; x < WIDTH; x++) {
                const int n = countNeighbours(grid, x, y);
                bool flip = (previousGrid[y][x] == '#' && (n < 2 || n > 3))
                    || (previousGrid[y][x] == ' ' && n == 3);
                if (flip) grid[y][x] = previousGrid[y][x] == '#' ? ' ' : '#';
            }
        }
        renderGeneration(grid);
        printf("\n");
        i++;
    }
    return 0;
}