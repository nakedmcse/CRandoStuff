// 3d projection to the console
#include <stdio.h>
#include <math.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct point2 {
    int x, y;
} point2;

typedef struct point3 {
    double x, y, z;
} point3;

double normalize(const double v, const double scale) {
    return ((v + 1)/2)*scale;
}

point2 project(point3 p) {
    const point2 r = { floor(normalize(p.x/p.z,100)), floor(normalize(p.y/p.z,LINES)) };
    return r;
}

point3 rotate(const point3 p, const double angle) {
    const point3 r = {
        p.x * cos(angle) - p.z * sin(angle),
            p.y,
        (p.x * sin(angle) + p.z * cos(angle))+0.5,
    };
    return r;
}

void plot(const point3 p) {
    const point2 s = project(p);
    mvaddch(s.y,s.x,'#');
}

void line(const point3 p1, const point3 p2) {
    const point2 s = project(p1);
    const point2 e = project(p2);
    double cx = (double)s.x; double cy = (double)s.y;
    const int dx = e.x - s.x;
    const int dy = e.y - s.y;
    const double len = sqrt(dx*dx + dy*dy);
    for (int i = 0; i < (int)ceil(len); i++) {
        mvaddch((int)lround(cy),(int)lround(cx),'#');
        cx += (double)dx/len; cy += (double)dy/len;
    }
}

int main(void) {
    point3 vertexes[] = {
        {-0.2, -0.2, -0.2},{0.2, -0.2, -0.2},{0.2, 0.2, -0.2}, {-0.2, 0.2, -0.2},
        {-0.2, -0.2, 0.2},{0.2, -0.2, 0.2},{0.2, 0.2, 0.2}, {-0.2, 0.2, 0.2}
    };

    int edges[][5] = {{0,1,2,3,0},{4,5,6,7,4},{0,4,-1,-1,-1},{1,5,-1,-1,-1},{2,6,-1,-1,-1},{3,7,-1,-1,-1}};

    initscr();
    nodelay(stdscr,1);
    curs_set(0);
    const int FPS = 30;
    struct timespec dt = {0, (1000/FPS)*1000000L};
    double angle = 0;
    int ch;

    do {
        ch = getch();
        clear();
        for (int i=0; i < 6; i++) {
            for (int j=1; j < 5; j++) {
                if (edges[i][j] == -1) break;
                const int s = edges[i][j-1];
                const int e = edges[i][j];
                line(rotate(vertexes[s],angle), rotate(vertexes[e],angle));
            }
        }
        angle += M_PI/(double)FPS;
        refresh();
        nanosleep(&dt, NULL);
    } while (ch != 'q');

    curs_set(1);
    endwin();
    return 0;
}